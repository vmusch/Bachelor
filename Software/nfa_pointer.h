#ifndef NFA_POINTER_H
#define NFA_POINTER_H

#include <string>
#include <vector>


enum
{
	Match = 256,
	Split = 257
};

struct State
{
  int c_;
  State *out1_ = nullptr;
  State *out2_ = nullptr;
  int lastlist_ = 0;
};

State* state(const int& c, State *out1, State *out2);/*
{
  State *s = new State;
  s->c_ = c;
  s->out1_ = out1;
  s->out2_ = out2;
  s->lastlist_ = 0;

  return s;
}
*/
struct Frag
{
  State *start;
	std::vector<State *> out;
};

Frag frag(State *start, std::vector<State *> out);/*
{
  Frag n = { start, out };
  return n;
}
*/
std::vector<State *> getVec(State *input);

std::vector<State *> appendVec(const	std::vector<State *>& vec1, const std::vector<State *>& vec2);

void patchVec(std::vector<State *>& in, State *s);

State* post2nfaE(const std::string& postfix);

std::string getRandomWord(State* startptr);

#endif
