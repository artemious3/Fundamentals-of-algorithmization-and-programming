#ifndef MODULEHT_H
#define MODULEHT_H

#include "hashtable.h"

class ModuleHT : public HashTable {
 public:
  explicit ModuleHT(int s) : size(s), HashTable(s) {}

  int hashFunc(int key) override { return key % size; }

 private:
  int size;
};
#endif  // MODULEHT_H
