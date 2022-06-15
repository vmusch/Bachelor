#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include "nfa_pointer.h"
#include "korotkov_nfa.h"
#include "korotkov_nfa2.h"


korotkovState* KortkovState(keyState* key)
{
  korotkovState* ptr = = new korotkovState;

  ptr->key_ = key;

  return ptr;
}

void oneStep(std::stack<korotkovState *>& stack, State* itptr,
              korotkovState* kptr, std::string& qGram)
{
  korotkovState k1, k2;
  int c = itptr->c_;
  switch(c)
  {
    default:

  }
}
void makeStart(State* it_ptr, std::vector<korotkovState* >& queue,
                std::vector<korotkovState* >& outs, const uint& q)
{
  std::stack<korotkovState* > stack{};
  korotkovState* k;
  std::qGram = "";
}

std::vector<korotkovState* > nfa2knfa2(State* nfa_ptr, const uint& q, )
{
  std::vector<korotkovState* > outs{};
  std::vector<korotkovState* > queue{};
  korotkovState* match = KortkovState(kstatet("$Match$"));

  State *it_ptr = nfa_ptr;
  try
  {
    // erstellen der start Knoten und verschieben in die SChlange
    makeStart(it_ptr, queue, outs, q);
  }
  catch(const int &Exception)
  {
    std::cerr<<"QGram zu lang gewählt"<<"\n";
  }
}
