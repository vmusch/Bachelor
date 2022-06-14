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

korotkovState* nfa2knfa(State* nfa_ptr, const uint& q, )