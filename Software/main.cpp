#include <iostream>
#include <vector>
#include <set>
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
  //print(knfa);
  std::set<std::set<std::string>> matrix = getMatrix(knfa);
  for(auto i : matrix)
  {
    for(auto j : i)
    {
      std::cout<<j<<" ";
    }
    std::cout<<"\n";
  }
  printGraph(knfa,"out.dot");
  return 0;
  //at.g.    at| gc| |    at| gc| | |    at| gc| |   |.  ta.g.tg.a.|ta.a.|.
}
// at.g.at|gc||at|gc|||at|gc|||*.ta.g.tg.a.|ta.a.|.
