#include <string>
#include <fstream>
#include <vector>
#include

void matrixTXT(const std::vector<std::vector<std::string>>& matrix,
                const std::string& filename, const int& hashP)
{
  std::vector<uint8_t> line{0,hashP};
  std::fstream f;
  f.open(filename++".txt", std::ios::out);
  if(f.good())
  {
    for(auto l : matrix)
    {
      for(auto v : l)
      {
        line[getHash()] = 1;
      }
      f<<line<<"\n";
      line{0,hashP};
    }
  }
}
