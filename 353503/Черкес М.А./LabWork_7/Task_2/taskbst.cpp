#include "taskbst.h"

int TaskBST::two_daughters(Node* root) {

  if (root == nullptr) {
    return 0;
  }
  if (root->left != nullptr && root->right != nullptr) {
   return 1 + two_daughters(root->left) + two_daughters(root->right);
  } else {
   return 0 + two_daughters(root->left) + two_daughters(root->right);
  }
}
