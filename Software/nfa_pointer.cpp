#include <iostream>
#include <stack>
#include <stdlib.h>
#include <string>
#include <vector>
#include <list>
/*
 * Represents an NFA state plus zero or one or two arrows exiting.
 * if c == Match, no arrows out; matching state.
 * If c == Split, unlabeled arrows to out and out1 (if != NULL).
 * If c < 256, labeled arrow with character c to out.
 */

int nstate{0}; //Anzahl aller States;

enum
{
	Match = 256,
	Split = 257
};

struct State
{
	int number_;
  int c_;
  State *out1_ = nullptr;
  State *out2_ = nullptr;
  int lastlist_ = 0;
};

/* Allocate and initialize State */
State* state(int c, State *out1, State *out2)
{
  nstate++;

  State *s = new State; //statt  s = malloc(sizeof *s)
	s->number_ = nstate;
  s->c_ = c;
  s->out1_ = out1;
  s->out2_ = out2;
  s->lastlist_ = 0;

  return s;
}


/*
 * A partially built NFA without the matching state filled in.
 * Frag.start points at the start state.
 * Frag.out is a list of places that need to be set to the
 * next state for this fragment.
 */
struct Frag
{
  State *start;
  //Ptrlist *out;
	std::vector<State *> out;
};

Frag frag(State *start, 	std::vector<State *> out)
{
  Frag n = { start, out };
  return n;
}

std::vector<State *> getVec(State *input)
{
	std::vector<State *> out{input};

	return out;
}

std::vector<State *> appendVec(const	std::vector<State *>& vec1, const std::vector<State *>& vec2)
{
	std::vector<State *> out = vec1;
	for(auto e : vec2)
	{
		out.push_back(e);
	}
	return out;
}

void patchVec(std::vector<State *>& in, State *s)
{
	for(auto e : in)
	{
		e->out1_ == nullptr ? e->out1_ = s : e->out2_ = s;
		//e->out1_ = s;
	}
}
/*
Frag frag(State *start, Ptrlist *out)
{
  Frag n = { start, out };
  return n;
}
*/
/*
 * Convert postfix regular expression to NFA.
 * Return start state.
 */

State *matchstate = state(Match, nullptr, nullptr); // Zielzustand

State* post2nfaE(const std::string& postfix)
{
  std::stack<Frag> stack;
  Frag e,e1,e2;
  State *s;
  if(postfix.empty()) return nullptr;
  for(uint i = 0; i < postfix.size(); i++)
  {
    char p = postfix[i];
    switch(p){
      default:
              s = state(p, nullptr, nullptr);
              //stack.push(frag(s, list1(&s->out1_)));
							stack.push(frag(s, getVec(s)));
              break;
      case '.':  //concat
              e2 = stack.top();
              stack.pop();
              e1 = stack.top();
              stack.pop();
							patchVec(e1.out, e2.start);
              //patch(e1.out, e2.start);
              stack.push(frag(e1.start, e2.out));
              break;
      case '|':   //or
              e2 = stack.top();
              stack.pop();
              e1 = stack.top();
              stack.pop();
              s = state(Split, e1.start, e2.start);
              //stack.push(frag(s, append(e1.out, e2.out)));
							stack.push(frag(s, appendVec(e1.out, e2.out)));
              break;
      case '?': //0 oder 1 mal
              e = stack.top();
              stack.pop();
              s = state(Split, e.start, nullptr);
							stack.push(frag(s, appendVec(e.out, getVec(s))));
              //stack.push(frag(s, append(e.out, list1(&s->out2_))));
              break;
      case '*': //kleene
              e = stack.top();
              stack.pop();
              s = state(Split, e.start, nullptr);
              //patch(e.out, s);
							patchVec(e.out, s);
							stack.push(frag(s, getVec(s)));
              //stack.push(frag(s, append(e.out, list1(&s->out2_))));
              break;
      case '+':
              e = stack.top();
              stack.pop();
              s = state(Split, e.start, nullptr);
							patchVec(e.out, s);
							stack.push(frag(e.start, getVec(s)));
              //patch(e.out, s);
              //stack.push(frag(e.start, append(e.out, list1(&s->out2_))));
							break;
    }
  }
  e = stack.top();
	if(e.start == nullptr) std::cout<<"Fuck"<<"\n";
	else std::cout<<"ok"<<"\n";
  stack.pop();

  if(!stack.empty()) return nullptr;
  patchVec(e.out, /*&*/ matchstate);
  return e.start;
}
/*
void printNFA(State zeiger)
{
	//State zeiger = input;
	State e,e1,e2;
	std::list<State> queue;
	queue.push_back(zeiger);
	State s;
	while(!queue.empty())
	{
		s = queue.front();
		queue.pop_front();
		if(s.lastlist_ == 1) continue;
		else s.lastlist_ = 1;
		std::cout<<"==========================="<<"\n";
		std::cout<<"ID: "<< s.number_ <<"\n";
		int c = s.c_;
		switch(c)
		{
			case Split:
			{
				e1 = *s.out1_;
				e2 = *s.out2_;
				std::cout<<"Split"<<"\n";
				std::cout<<"Erster: "<<e1.number_<<"\n";
				std::cout<<"Zweiter"<<e2.number_<<"\n";
				queue.push_back(e1);
				queue.push_back(e2);
				break;
			}
			case Match:
			{
				std::cout<<"Match"<<"\n";
				break;
			}
			default:
			{
				std::cout<<s.c_<<"\n";
				if(s.out1_ == nullptr) std::cout<<"uff"<<"\n";
				if(s.out2_ != nullptr) std::cout<<"???: "<<s.out2_->c_<<"\n";
				e = *s.out2_;// Seg fault
				std::cout<<(char)c<<"\n";
				std::cout<<"Erster: "<<e.number_<<"\n";
				//queue.push_back(e);
				break;
			}
		}
		std::cout<<"==========================="<<"\n";
	}

}
*/
int main()
{

	std::vector<std::string> a ={"a","ab.","ab|","a*","a+","a?"};
	State * startptr;
	for(auto e : a)
	{
		startptr = post2nfaE(e);
	}


  return 0;
}
