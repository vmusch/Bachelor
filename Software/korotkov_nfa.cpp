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
        throw int();
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
    if(k->positionNFA_->c_ == Match)
    {
      throw int();
      //std::cerr<<"Q-Gram zu lang gewählt"<<"\n";
    }
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

//void nextStep(std::stack<keyState *>& stack, keyState* input, State* itptr)
void nextStep(std::stack<keyState *>& stack, keyState* input)//, State* itptr)
{
  keyState *e1, *e2;
  State* itptr = input->positionNFA_;
  int c = itptr->c_;
  switch(c)
  {
    default:
        //input->positionNFA_ = itptr->out1_;
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

  k = key(qGramFrag, input->positionNFA_->out1_, nullptr);
  nextStep(stack, k);
  //nextStep(stack, k, input->positionNFA_->out1_);
  while(!stack.empty())
  {
    k = stack.top();
    stack.pop();
    if(k->positionNFA_->c_== Match)
    {
      input->home_->outs_.push_back(match);
    }
    else if(k->qGramFrag_ == "$")
    {
      std::cout<<"HI"<<"\n";
      input->home_->outs_.push_back(match);
    }
    else if(k->positionNFA_->c_ == Split)
    {
      nextStep(stack, k);
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

  kState* e;

  //---------------------------------------------------
  State *it_ptr = nfa_ptr;
  try
  {
    firstPhase(it_ptr, queue, q);
  }
  catch(const int &Exception)
  {
    std::cerr<<"QGram zu lang gewählt"<<"\n";
  }
  for(auto v : queue)
  {
    std::cout<<v->qGramFrag_<<"   "<<v->positionNFA_<<"   "<<v->home_<<"\n";
  }
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
    output.push_back(e);
  }

  //--------------------------------------

  for(uint i = 0; i < queue.size(); i++)
  {
    nextKeys(queue, queue[i], match);
  }

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
  std::cout<<"Start: "<<"\n";
  for(uint i = 0; i < input.size(); i++)
  {
    std::cout<<input[i]<<"\n";
    stack.push(input[i]);
  }
  std::cout<<"#################"<<"\n";
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
  //b+c?(a|b)*b+
  //std::string a = "ab.e+.c.d.f.";
  //std::string a = "bb.ab|*.b+.";
  std::string a = "ab.c.d.e.f.g+.";
  //std::string a = "ab+c+|.d.";
  //abc(cba)*abc
	//std::string a = "ab.c.d?.";
  startptr = post2nfaE(a);
  std::vector<kState *> m;
  m = nfa2knfa(startptr, 7);
  //std::string rndWord;
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
