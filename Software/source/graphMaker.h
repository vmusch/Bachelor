#ifndef GRAPH_MAKER_H
#define GRAPH_MAKER_H

#include <string>
#include <vector>
#include <fstream>
#include "korotkov_nfa.h"

//std::string printNode(kState *input);

void printGraph(const std::vector<kState *>& input, const std::string& filename);

void print(const std::vector<kState *>& input);

void uMatrix(std::vector<std::vector<std::string>>& matrix);

#endif
