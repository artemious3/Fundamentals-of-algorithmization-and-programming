#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <vector>

template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair() : first(T1()), second(T2()) {}
    Pair(const T1& a, const T2& b) : first(a), second(b) {}
};

#endif // PAIR_H
