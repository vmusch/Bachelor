#ifndef KOROTKOV_NFA_H
#define KOROTKOV_NFA_H

#include <string>
#include <vector>
#include "nfa_pointer.h"


struct kState
{
  std::string qGram_;
  std::vector<kState *> outs_ = {};
};


struct keyState
{
    std::string qGramFrag_;
    State *positionNFA_= nullptr;
    kState * home_ = nullptr;
};


kState* kstate(const std::string& qGram);

keyState* key(const std::string& qGramFrag, State *positionNFA_, kState * home);

void oneStep(std::stack<keyState *>& stack, State* it_ptr, kState* kptr, std::string& qGram);

void firstPhase(State *it_ptr, std::vector<keyState *>& output, const uint& q);

std::vector<kState *> nfa2knfa(State* nfa_ptr, const uint& q);

#endif
