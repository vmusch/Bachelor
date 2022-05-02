#include <iostream>

using namespace std;
template<typename T>
class matrix
{
private:    
    T* arr_;  
    
    int capacity_;
    
    int current_;
    
    int row_;
    
    int column_;
  
public:
      
    matrix(int r, int c, T data);
    
    void setValue(int rowIndex, int columnIndex, T data);
    
    T getValue(int rowIndex, int columnIndex);
    
    int size();
    
    int getcapacity();
    
    void print();
};
