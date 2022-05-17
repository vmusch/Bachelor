#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include "nfa_pointer.h"
#include "korotkov_nfa.h"

kState* kstate(const std::string& qGram)
{
  kState* ptr = new kState;

  ptr-> qGram_ = qGram;

  return ptr;
}

keyState* key(const std::string& qGramFrag, State *positionNFA, kState * home)
{
  keyState* ptr = new keyState;

  ptr-> qGramFrag_ = qGramFrag;
  ptr-> positionNFA_ = positionNFA;
  ptr-> home_ = home;

  return ptr;
}



void oneStep(std::stack<keyState *>& stack, State* itptr, kState* kptr, std::string& qGram)
{
  keyState *e1, *e2;
  int c = itptr->c_;
  switch(c)
  {
    default:
        qGram += c;
        e1 = key(qGram, itptr->out1_, kptr);
        stack.push(e1);
        break;
    case Split:
        e1 = key(qGram, itptr->out1_, kptr);
        e2 = key(qGram, itptr->out2_, kptr);
        stack.push(e2);
        stack.push(e1);
        break;
    case Match:
        std::cerr<<"qgram zu lang gewählt!"<<"\n";
        break;
  }
}

void firstPhase(State* it_ptr, std::vector<keyState *>& output, const uint& q)
{
  std::stack<keyState *> stack;
  keyState* k;
  std::string qGram = "";

  oneStep(stack,it_ptr,nullptr,qGram);

  while(!stack.empty())
  {
    k = stack.top();
    stack.pop();
    if(k-> qGramFrag_.size() == q-1 && k->positionNFA_->c_ != Split)
    {
      //std::cout<<k->qGramFrag_<<"\n";
      output.push_back(k);
    }
    else
    {
      oneStep(stack, k->positionNFA_, nullptr, k->qGramFrag_);
    }
  }
}

//später optimieren
int linSearch(const std::vector<keyState *>& liste, keyState* obj)
{
  for(uint i = 0; i<liste.size(); i++)
  {
    if(liste[i]->qGramFrag_ == obj->qGramFrag_ && liste[i]-> positionNFA_ == obj->positionNFA_)
    {
      return i;
    }
  }
  return -1;
}

void nextStep(std::stack<keyState *>& stack, keyState* input)
{
  keyState *e1, *e2;
  State* itptr = input->positionNFA_->out1_;
  int c = itptr->c_;
  switch(c)
  {
    default:
        input->positionNFA_ = itptr;
        stack.push(input);
        break;
    case Split:
        e1 = key(input->qGramFrag_, itptr->out1_, nullptr);
        e2 = key(input->qGramFrag_, itptr->out2_, nullptr);
        stack.push(e2);
        stack.push(e1);
        break;
    case Match:
        input->positionNFA_ = itptr;
        input->qGramFrag_ = "$";
        stack.push(input);
        break;
  }
}


void nextKeys(std::vector<keyState *>& liste, keyState* input, kState* match)
{
  std::stack<keyState *> stack;
  keyState* k;
  kState* e;
  std::string qGramFrag = input->home_->qGram_;
  qGramFrag = qGramFrag.substr(1);
  std::string qGram = qGramFrag;

  k = key(qGramFrag, input->positionNFA_, nullptr);
  nextStep(stack, k);
  while(!stack.empty())
  {
    k = stack.top();
    stack.pop();
    if(k->qGramFrag_ == "$")
    {
      input->home_->outs_.push_back(match);
    }
    else if(k->positionNFA_->c_ == Split)
    {
      nextStep(stack,k);
    }
    else
    {
      int i = linSearch(liste, k);
      if(i == -1)
      {
        qGram += k->positionNFA_->c_;
        e = kstate(qGram);
        input->home_->outs_.push_back(e);
        k->home_ = e;
        liste.push_back(k);
        qGram = qGramFrag;
      }
      else
      {
        k = liste[i];
        input->home_->outs_.push_back(k->home_);
      }
    }
  }


}

std::vector<kState *> nfa2knfa(State* nfa_ptr, const uint& q)
{
  /*
  Phase 1:  Schlange befüllen mit keyStates
            zuerst alle vom start durchgehen, mittels stack;
  */
  std::vector<kState *> output{}; //fungiert als start
  std::vector<keyState *> queue{};
  kState* match = kstate("$");

  kState* e,e1,e2;
  State* l,l1,l2;
  keyState* k,k1,k2;
  std::string keyQgram;
  //---------------------------------------------------
  State *it_ptr = nfa_ptr;

  firstPhase(it_ptr, queue, q);

  //Phase 2
  //erstellen der start states und umschreiben der pointer der keys
  std::string edge;
  output.reserve(queue.size());
  for(auto v : queue)
  {
    edge = v->qGramFrag_;
    edge += v->positionNFA_->c_;
    e = kstate(edge);
    v->home_ = e;
    //  v->positionNFA_ = v->positionNFA_->out1_;
    output.push_back(e);
  }

  //--------------------------------------
  //for(auto v : queue)
  for(uint i = 0; i < queue.size(); i++)
  {
    nextKeys(queue, queue[i], match);
  }




//queue durchgehen, dabei neue q-1 gkeys erstelle und dazugehörigen Knoten oder wenn
// es ihn gibt kante auf diesen
/*
for(auto v : queue)
{
  l = v->positionNFA_;
  e = v->home_;
  if(l->c_ == Split)
  {
    //out1
    l1 = l->out1_;
    keyQgram = e->qGram_.substr(1);
    k1 = key(keyQgram, l1, e);
    std::vector<keyState *>::iterator it;
    it = find(queue.begin(), queue.end(), k1);
    if(it != queue.end())// Schlüssel existiert bereits
    {
      e->outs_.push_back(*it->home_);
    }
    else
    {
      edge = keyQgram;
      edge += l1->c_;
      e1 = kstate(edge);
      e.push_back(e1);
      queue.push_back(k1);
    }
    //out2
    l2 = l->out2_;
    keyQgram = e->qGram_.substr(1);
    k2 = key(keyQgram, l2, e);
    std::vector<keyState *>::iterator it;
    it = find(queue.begin(), queue.end(), k2);
    if(it != queue.end())// Schlüssel existiert bereits
    {
      e->outs_.push_back(*it->home_);
    }
    else
    {
      edge = keyQgram;
      edge += l2->c_;
      e1 = kstate(edge);
      e.push_back(e1);
      queue.push_back(k1);
    }



  }
  else if(l->c_ == Match)
  {
    e->outs_.push_back(match);
  }
  else
  {

  }
}*/
/*
  while(!queue.empty())
  {
    k = queue.front();
    queue.pop();
    qGram = k->qGramFrag_;
    qGram += k->positionNFA_->c_;
    e = kstate(qGram);
    if(k->home_ == nullptr)
    {
      output.push_back(e);
    }
    else
    {
      k->home_->outs_.push_back(e);
    }
    l = k->positionNFA_;
    k = key(qGram.substr(1), l, e);
    queue.push(k);
  }
*/

  return output;
}

void printState(kState *input)
{
  std::cout<<"----------------------"<<"\n";
  std::cout<<"ID: "<<input<<"\n";
  std::cout<<"q-Gram: "<<input->qGram_<<"\n";
  for(auto e : input->outs_)
  {
    std::cout<<e<<"\n";
  }
  std::cout<<"----------------------"<<"\n";
}

void print(const std::vector<kState *>& input)
{
  std::stack<kState *> stack;
  for(uint i = 0; i < input.size(); i++)
  {
    stack.push(input[i]);
  }
  kState* k;
  while(!stack.empty())
  {
    k = stack.top();
    stack.pop();
    if(k->marked_ == 0)
    {
      printState(k);
      k->marked_ = 1;
      for(auto v : k->outs_)
      {
        stack.push(v);
      }
    }
  }
}

int main()
{
  State * startptr;
  std::string a = "ab+c+|.d.";

  startptr = post2nfaE(a);
  std::vector<kState *> m;
  m = nfa2knfa(startptr, 2);
  std::string rndWord;
  /*for(int i = 0; i <= 10; i++)
  {
    rndWord = getRandomWord(startptr);
    std::cout<<rndWord<<"\n";
  }
  for(auto e : m)
  {
    std::cout<< e->qGram_<<"\n";
  }*/
  print(m);
}
