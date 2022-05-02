//#include "matrix.hpp"
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
    
    T basicData_;
  
public:
    
matrix(int r, int c, T data)
{
    arr_ = new T[r*c];
    capacity_ = r*c;
    current_ = r*c;
    row_ = r;
    column_ = c;
    basicData_ = data;
    for(int i = 0; i < current_; ++i)
    {
        arr_[i] = data;
    }
}

~matrix()
{
    delete arr_;
    cout<< "deleted";
}
void setValue(int rowIndex, int columnIndex, T data)
{
    int k =  column_ * columnIndex + rowIndex;
    arr_[k] = data;
}

T getValue(int rowIndex, int columnIndex)
{
    int k = column_ * columnIndex + rowIndex;
    return arr_[k];
}

int size()
{
    return current_;
}

int getcapacity()
{
    return capacity_;
}

void addRow()
{
    row_++;
    T* tmp = new T[row_*column_];
    for(int i = 0; i < current_; ++i)
    {
        tmp[i] = arr_[i];
    }
    for(int i = current_; i < row_*column_; ++i)
    {
        tmp[i] = basicData_;
    }
    current_ = row_*column_;
    capacity_ = row_*column_;
    delete[] arr_;
    arr_ = tmp;
}

void print()
{
    for(int i = 0; i < current_; ++i)
    {
        std::cout<<arr_[i]<<" ";
    }
    std::cout<<"\n";
    std::cout<<"\n";

    for(int i = 0; i < row_; ++i)
    {
        for(int32_t j = 0; j < column_; ++j)
        {
            std::cout<<getValue(i,j)<<"     ";
        }
        std::cout<<"\n";
    }
}
};


int main(){
    matrix<int>a (5, 4, 1);
    a.print();
    a.setValue(2,3,5);
    a.print();
    a.addRow();
    a.print();
    a.setValue(5,4,5);
    a.print();
    
    
    
}
