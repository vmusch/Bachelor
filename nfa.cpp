#include <iostream>
#include <string>
#include <vector>
#include "nfa.hpp"

matrix::matrix(const int32_t& h, const int32_t& v,const  T& basicValue)
{
    std::vector<T> a(h*v, basicValue);
    h_ = h;
    v_ = v;
    m_ = a;
}
    
void matrix::setValue(const int32_t& zeile, const int32_t& spalte, const T& value)
{
    int32_t k = zeile*h_ + spalte;
    m_[k] = value;
}

T matrix::getValue(const int32_t& zeile, const int32_t& spalte);
{
    return m_[zeile*h_+spalte];
}
/*
void matrix::maxValue(int32_t& k, int32_t& l)
{
    int32_t max = 0;
    for(int32_t i = 0; i < v_; ++i)
    {
        for(int32_t j = 0; j < h_; ++j)
        {
            if(getValue(i,j) > max)
            {
                max = getValue(i,j);
                k = i;
                l = j;
            }
        }
    }
}*/

void matrix::print()
{
    for(auto x : m_)
    {
        std::cout<<x<<" ";
    }
    std::cout<<"\n";
    std::cout<<"\n";

        for(int32_t i = 0; i < v_; ++i)
        {
            for(int32_t j = 0; j < h_; ++j)
            {
                std::cout<<getValue(i,j)<<"     ";
            }
            std::cout<<"\n";
        }
}
/*
class NFA{
private:
    std::vector<states> zustaende;
    std::vect
};*/

int main(){
    
    matrix<char> a(5,4, "-");
    a.print();
    
}
