#include <iostream>
#include <stack>
#include <stdlib.h>
#include <string>
//#include <vector>
#include <list>
/*
 * Represents an NFA state plus zero or one or two arrows exiting.
 * if c == Match, no arrows out; matching state.
 * If c == Split, unlabeled arrows to out and out1 (if != NULL).
 * If c < 256, labeled arrow with character c to out.
 */


enum
{
	Match = 256,
	Split = 257
};

struct State
{
	int number_;
  int c_;
  State *out1_;
  State *out2_;
  int lastlist_;
};

State matchstate = {0, Match, nullptr, nullptr, 0}; // Zielzustand
int nstate{0}; //Anzahl aller States;

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

struct Ptrlist
{
  Ptrlist *next;
  State *s;
};

/* Create singleton list containing just outp. */
Ptrlist* list1(State **outp)
{
  Ptrlist *l;

  l =  (Ptrlist*) outp; // outp als ptrlist casten
  l->next = nullptr;
  return l;
}

/* Patch the list of states at out to point to start. */
void patch(Ptrlist *l, State *s)
{
	Ptrlist *next;

	for(; l != nullptr; l = l->next){
		next = l->next;
		l->s = s;
	}
}

/* Join the two lists l1 and l2, returning the combination. */
Ptrlist* append(Ptrlist *l1, Ptrlist *l2)
{
	Ptrlist *oldl1;

	oldl1 = l1;
	while(l1->next)
		l1 = l1->next;
	l1->next = l2;
	return oldl1;
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
  Ptrlist *out;
};

Frag frag(State *start, Ptrlist *out)
{
  Frag n = { start, out };
  return n;
}

/*
 * Convert postfix regular expression to NFA.
 * Return start state.
 */

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
              stack.push(frag(s, list1(&s->out1_)));
              break;
      case '.':  //concat
              e2 = stack.top();
              stack.pop();
              e1 = stack.top();
              stack.top();
              patch(e1.out, e2.start);
              stack.push(frag(e1.start, e2.out));
              break;
      case '|':   //or
              e2 = stack.top();
              stack.pop();
              e1 = stack.top();
              stack.top();
              s = state(Split, e1.start, e2.start);
              stack.push(frag(s, append(e1.out, e2.out)));
              break;
      case '?': //0 oder 1 mal
              e = stack.top();
              stack.pop();
              s = state(Split, e.start, nullptr);
              stack.push(frag(s, append(e.out, list1(&s->out2_))));
              break;
      case '*': //kleene
              e = stack.top();
              stack.pop();
              s = state(Split, e.start, nullptr);
              patch(e.out, s);
              stack.push(frag(s, append(e.out, list1(&s->out2_))));
              break;
      case '+':
              e = stack.top();
              stack.pop();
              s = state(Split, e.start, nullptr);
              patch(e.out, s);
              stack.push(frag(e.start, append(e.out, list1(&s->out2_))));
    }
  }
  e = stack.top();
	if(e.start == nullptr) std::cout<<"Fuck"<<"\n";
	else std::cout<<"ok"<<"\n";
  stack.pop();
	std::cout<<stack.size()<<"\n";
  if(!stack.empty()) return nullptr;
  patch(e.out, & matchstate);
  return e.start;
}

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
				e = *s.out1_;
				std::cout<<(char)c<<"\n";
				std::cout<<"Erster: "<<e.number_<<"\n";
				queue.push_back(e);
				break;
			}
			default:
			{
				std::cout<<"Match"<<"\n";
				break;
			}
		}
	}

}

int main()
{
	std::string postfix = "ab.";
	State * startptr;
	startptr = post2nfaE(postfix);
	//int c = (*startptr).c_;
	if(startptr == nullptr) std::cout<<"F"<<"\n";
	else std::cout<<"ok"<<"n";

	//State start = *stateptr;
	//printNFA(*stateptr);

  return 0;
}
