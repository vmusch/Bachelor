#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <string>
#include <stack>
#include "korotkov_nfa.h"
#include "graphMaker.h"
#include "nfa_pointer.h"
#include "utils.h"
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/search/views/minimiser_hash.hpp>
#include <seqan3/search/dream_index/interleaved_bloom_filter.hpp>

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
    std::vector<char> alphabet = getAlphabet(argv[1]);

    State* nfa = post2nfaE(argv[1]);
    std::vector<kState *> knfa = nfa2knfa(nfa, qlength);

    deleteGraph(nfa);

    std::vector<std::vector<std::string>> matrix{};
    for(auto i : knfa)
    {
      dfs(i,matrix);
    }
    uMatrix(matrix);


    //IBF befüllt
    std::unordered_set<std::string> qGramA = getQgramAlphabet(matrix);
    seqan3::interleaved_bloom_filter ibf{seqan3::bin_count{qGramA.size()}, seqan3::bin_size{8192u}};
    uint i = 0;
    for(auto qGramE : qGramA)
    {
      uint32_t hash = getHash(alphabet, qGramE, 2);
      ibf.emplace(hash, seqan3::bin_index{i});
      auto agent = ibf.membership_agent();
      auto & result = agent.bulk_contains(hash);
      seqan3::debug_stream<< qGramE <<" "<<hash<<" "<<result<<"\n";
      i++;
    } 

    //bitvec erstellen
    std::vector<std::vector<bool>> bitMatrix{};
    std::vector<int> bitMatrixFinal{};
    auto agent = ibf.membership_agent();
    
    for(auto setQ : matrix)
    {
      std::vector<bool> bitVecQgram(qGramA.size(),0);
      for(auto qgramM : setQ)
      {
        auto & bitvec = agent.bulk_contains(getHash(alphabet, qgramM, 2));
        for(int i = 0; i < bitvec.size(); i++)
        {
          bitVecQgram[i] = bitVecQgram[i] | bitvec[i];
        }
      }
      bitMatrix.push_back(bitVecQgram);
    }
    //std::cout<<bitOp(bitMatrix[0], bitMatrix[1])<<"\n";
    //interessante sets filtern
    for(uint i = 0; i < bitMatrix.size()-1; i++)
    {
      if(bitOp(bitMatrix[i], bitMatrix[i+1]) == 1)
      {
        bitMatrixFinal.push_back(i);
      }
    }
    bitMatrixFinal.push_back(bitMatrix.size()-1);

    for(auto elem : bitMatrixFinal)
    {
      std::cout<<elem<<" ";
    }
    std::cout<<"\n";
    if(argc >= 4)
    {
      std::string matrixfile = argv[3];
      matrixTotxt(matrix, matrixfile);
    }
    else
    {
      for(auto elem : alphabet)
      {
        std::cout<<elem<<" ";
      }
      std::cout<<"\n";
      for(uint i  = 0; i < matrix.size(); i++)
      {
        for(auto j : matrix[i])
        {
          std::cout<<j<<" ";
        }
        for(auto j : bitMatrix[i])
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
