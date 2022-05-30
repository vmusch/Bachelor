#include <stack>
#include <fstream>
#include <vector>
#include "korotkov_nfa.h"
#include "graphMaker.h"


std::string printNode(kState *input)
{
  std::string line = "\"";
  line += input->qGram_;
  line += "\"->{";
  if(input->qGram_ != "$")
  {
    for(auto e : input->outs_)
    {
      line += "\"";
      line += e->qGram_;
      line += "\" ";
    }
  }
  line += "}";
  if(input->start_) line += " ";
  return line;
}

void printGraph(const std::vector<kState *>& input, const std::string& filename)
{
  std::fstream f;
  f.open(filename, std::ios::out);
  f << "digraph graphname"<<"\n";
  f << "{"<<"\n";
  f << "{"<<"\n";
  f << "\"$\" [shape=doublecircle]"<<"\n";

  std::string newline;
  std::stack<kState *> stack;
  for(uint i = 0; i < input.size(); i++)
  {
    //std::cout<<input[i]<<"\n";
    stack.push(input[i]);
    newline = "\"";
    newline += input[i]->qGram_;
    newline += "\" [style=filled fillcolor = red]";
    f << newline << "\n";
  }
    f << "}"<<"\n";
  //std::cout<<"#################"<<"\n";
  kState* k;
  while(!stack.empty())
  {
    k = stack.top();
    stack.pop();
    if(k->marked_ == 0)
    {
      newline = printNode(k);
      f << newline <<"\n";
      k->marked_ = 1;
      for(auto v : k->outs_)
      {
        stack.push(v);
      }
    }
  }
  f << "}";
  f.close();
}
