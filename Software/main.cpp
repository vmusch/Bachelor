#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "korotkov_nfa.h"
#include "graphMaker.h"
#include "nfa_pointer.h"

int main()
{
  std::string regex;
  int qlength = 0;
  std::cout<<"Enter Regex in RPN:"<<"\n";
  std::cin>>regex;
  std::cout<<"Enter qGram length:"<<"\n";
  std::cin>>qlength;
  State* nfa = post2nfaE(regex);
  std::vector<kState *> knfa = nfa2knfa(nfa, qlength);
  print(knfa);//Graph(knfa,"test.dot");
  return 0;
}
