#include <iostream>
#include <string>
#include <vector>

template <typename T>
class matrix{
private:
    std::vector<T> m_;
    int32_t h_;
    int32_t v_;
public:
    matrix(const int32_t& h, const int32_t& v, T& basicValue);

    void setValue(const int32_t& zeile, const int32_t& spalte, const T& value);

    T getValue(const int32_t& zeile, const int32_t& spalte);
    
    //void maxValue(int32_t& k, int32_t& l);
    
    void print();

};

/*
class NFA{
public:
    
    struct State{
        bool initial;
        bool accept;
    };
    
protected:
    std::vector<State> stateSet;
    std::vector<char> alphabet;
    matrix>
    
};*/
