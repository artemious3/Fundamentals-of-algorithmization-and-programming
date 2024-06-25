#ifndef DERIVEDHASHTABLE_H
#define DERIVEDHASHTABLE_H

#include "hashtable.h"

class DerivedHashTable : public HashTable {
public:
    DerivedHashTable(int size);
    int findMaxStack();
};

#endif // DERIVEDHASHTABLE_H
