#ifndef TASKBST_H
#define TASKBST_H
#include "bst.h"

class TaskBST : public BST {
 public:
  int two_daughters(Node* root);
};

#endif  // TASKBST_H
