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

std::vector<kState *> nfa2knfa(State* nfa_ptr, const uint& q)
{
  /*
  Phase 1:  Schlange befüllen mit keyStates
            zuerst alle vom start durchgehen, mittels stack;
  */
  std::vector<kState *> output{}; //fungiert als start
  std::queue<keyState *> queue{};
  std::stack<keyState *> stack;
  keyState* k;
  kState* e;
  State* l;
  //---------------------------------------------------
  State *it_ptr = nfa_ptr;
  //kStade *it_ptr_k = kstade("",nullptr);

  std::string qGram = "";
  oneStep(stack,it_ptr,nullptr,qGram);

  while(!stack.empty())
  {
    k = stack.top();
    stack.pop();
    if(k-> qGramFrag_.size() == q-1 && k->positionNFA_->c_ != Split)
    {
      std::cout<<k->qGramFrag_<<"\n";
      queue.push(k);
    }
    else
    {
      oneStep(stack, k->positionNFA_, nullptr, k->qGramFrag_);
    }
  }
  //--------------------------------------
  //Phase 2
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

  return output;
}

int main()
{
  State * startptr;
  std::string a = "ab+c+|.d.";

  startptr = post2nfaE(a);
  std::vector<kState *> m;
  m = nfa2knfa(startptr, 3);
  std::string rndWord;
  /*for(int i = 0; i <= 10; i++)
  {
    rndWord = getRandomWord(startptr);
    std::cout<<rndWord<<"\n";
  }*/

}
