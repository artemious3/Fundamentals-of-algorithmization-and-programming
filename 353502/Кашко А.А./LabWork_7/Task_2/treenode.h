#ifndef TREENODE_H
#define TREENODE_H

#include <string>

class TreeNode { // класс для создания узла в бинарном дереве
public:
    int key;
    std::string data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int key, const std::string& data);
};

#endif // TREENODE_H
