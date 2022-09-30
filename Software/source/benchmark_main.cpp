#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "nfa_pointer.h"

int main(int argc, char *argv[])
{
    int set = std::stoi(argv[2]);
    std::cout<<set<<"\n";
    std::string regex = argv[1];
    State* nfa = post2nfaE(regex);
    std::fstream file;
    file.open("words.txt", std::ios::out);
    while(set > 0)
    {
        file << getRandomWord(nfa)<<"\n";
        set--;
    }
    file.close();
}