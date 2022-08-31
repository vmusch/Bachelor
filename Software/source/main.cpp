#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <stack>
#include "korotkov_nfa.h"
#include "graphMaker.h"
#include "nfa_pointer.h"
#include "utils.h"

int main(int argc, char *argv[])
{

  if(argc > 5 || argc < 3)
  {
    
    std::cerr<<"error";
    return -1;
  }
  else
  {
    int qlength = std::stoi(argv[2]);
    std::vector<char> a = getAlphabet(argv[1]);

    State* nfa = post2nfaE(argv[1]);
    std::vector<kState *> knfa = nfa2knfa(nfa, qlength);

    deleteGraph(nfa);

    std::vector<std::vector<std::string>> matrix{};
    for(auto i : knfa)
    {
      dfs(i,matrix);
    }
    uMatrix(matrix);
    if(argc >= 4)
    {
      std::string matrixfile = argv[3];
      matrixTotxt(matrix, matrixfile);
    }
    else
    {
      std::vector<char> a = getAlphabet(argv[1]);
      for(auto e : a)
      {
        std::cout<<e<<" ";
      }
      for(auto i : matrix)
      {
        for(auto j : i)
        {
          std::cout<<j<<" ";
        }
        std::cout<<"\n";
      }
    }
    if(argc == 5)
    {
      std::string dotfile = argv[4];
      dotfile += ".dot";
      printGraph(knfa, dotfile);
    }
  }
  return 0;
}






//   std::string regex;
//   int qlength = 0;
//   std::cout<<"Enter Regex in RPN:"<<"\n";
//   std::cin>>regex;
//   std::cout<<"Enter qGram length:"<<"\n";
//   std::cin>>qlength;
//   State* nfa = post2nfaE(regex);

//   std::vector<kState *> knfa = nfa2knfa(nfa, qlength);

//   std::vector<char> a = getAlphabet(regex);
//   for(auto e : a)
//   {
//     std::cout<<e<<" ";
//   }

//   std::cout<<"\n";
//   std::vector<std::vector<std::string>> matrix{};

//   for(auto i : knfa)
//   {
//     dfs(i,matrix);
//   }
//   uMatrix(matrix);
//   for(auto i : matrix)
//   {
//     for(auto j : i)
//     {
//       std::cout<<j<<" ";
//     }
//     std::cout<<"\n";
//   }
//   std::string h = "out";
//   matrixTotxt(matrix, h);
//   printGraph(knfa,"out.dot");
//   return 0;
//   //at.g.    at| gc| |    at| gc| | |    at| gc| |   |.  ta.g.tg.a.|ta.a.|.
// }
// at.g.at|gc||at|gc|||at|gc|||*.ta.g.tg.a.|ta.a.|.
