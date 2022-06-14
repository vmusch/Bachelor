#ifndef KOROTKOV_NFA2_H
#define KOROTKOV_NFA2_H

#include <string>
#include <vector>
#include "nfa_pointer.h"
#include "korotkov_nfa.h"

struct korotkovState
{
    keyState* key_;
    std::vector<korotkovState* > out1_{};
    std::vector<std::string> out2_{};
    bool start_ = 0;
    bool marked_ = 0;
}

korotkovState KortkovState(keyState* key);

#endif
