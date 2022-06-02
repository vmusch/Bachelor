#ifndef KOROTKOV_NFA_H
#define KOROTKOV_NFA_H

#include <string>
#include <vector>
#include "nfa_pointer.h"


struct kState
{
  std::string qGram_;
  std::vector<kState *> outs_ = {};
  int marked_ = 0;
  bool start_ = 0;
};

struct keyState
{
    std::string qGramFrag_;
    State *positionNFA_= nullptr;
    kState * home_ = nullptr;
};

struct Path
{
  std::vector<kState* > qPath_;
  kState* position_;
};

kState* kstate(const std::string& qGram);

keyState* key(const std::string& qGramFrag, State *positionNFA_, kState * home);

Path path(std::vector<kState* > qPath,  kState* position);

void oneStep(std::stack<keyState *>& stack, State* it_ptr, kState* kptr, std::string& qGram);

void firstPhase(State *it_ptr, std::vector<keyState *>& output, const uint& q);

int linSearch(const std::vector<keyState *>& liste, keyState* obj);

void nextStep(std::stack<keyState *>& stack, keyState* input);

void nextKeys(std::vector<keyState *>& liste, keyState* input, kState* match);

std::vector<kState *> nfa2knfa(State* nfa_ptr, const uint& q);

std::vector<std::vector<std::string>> getMatrix(std::vector<kState* > input);

#endif
