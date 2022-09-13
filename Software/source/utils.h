#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <unordered_set>

std::vector<char> getAlphabet(const std::string& regex);

//soll alle nötigen qgramme finden
std::unordered_set<std::string>  getQgramAlphabet(const std::vector<std::vector<std::string>>& matrix);

//bitoperation on vec
int bitOp(std::vector<bool> a, const std::vector<bool> & b);

uint shiftValue(const uint& input);

uint32_t getHash(const std::vector<char>& alphabet, const std::string& input, const uint& sValue);

void matrixTotxt(const std::vector<std::vector<std::string>>& matrix, std::string& filename);

void matrixTXT(const std::vector<std::vector<std::string>>& matrix,
                const std::vector<char>& alphabet);

#endif