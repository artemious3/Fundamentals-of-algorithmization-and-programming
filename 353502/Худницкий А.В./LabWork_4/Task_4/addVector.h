#ifndef ADDVECTOR_H
#define ADDVECTOR_H

#include "pair.h"

template<typename T1, typename T2>
class Vector {
public:
    void push_back(const Pair<T1, T2>& pair) {
        data.push_back(pair);
    }

    std::vector<Pair<T1, T2>> data;
};

#endif // ADDVECTOR_H
