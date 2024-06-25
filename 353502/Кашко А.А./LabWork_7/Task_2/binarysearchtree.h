#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "treenode.h"

class BinarySearchTree {
private:
    /* Метод принимает указатель на узел node, ключ key и данные data. Он используется для вставки нового узла в дерево с корнем в указанном узле node.
    Этот метод является приватным и используется внутри класса для рекурсивной вставки узла. */

    void insert(TreeNode*& node, int key, const std::string& data); // метод для вставки нового узла в дерево

    /* Метод принимает указатель на узел node и ключ key. Он выполняет рекурсивный поиск узла с указанным ключом в поддереве с корнем в
    узле node. Если узел с ключом key найден, он возвращает указатель на этот узел. Если узел node пуст или ключ текущего узла равен ключу key, то
    возвращается указатель на текущий узел. Иначе метод рекурсивно вызывает себя для левого или правого поддерева, в зависимости от значения ключа key. */

    TreeNode* search(TreeNode* node, int key); // метод для поиска узла с заданным ключом в дереве

    TreeNode* minValueNode(TreeNode* node); // метод для поиска узла с минимальным ключом в поддереве с корнем в указанном узле
    TreeNode* deleteNode(TreeNode* root, int key); // метод для удаления узла с заданным ключом из дерева
    void printInOrder(TreeNode* node); // метод для печати узлов дерева в порядке "возрастания ключа"
    void printPreOrder(TreeNode* node); // метод для печати узлов дерева в префиксном порядке (текущий - левый - правый)
    void printPostOrder(TreeNode* node); // метод для печати узлов дерева в постфиксном порядке (левый - правый - текущий)
    void destroyTree(TreeNode* node); // метод для удаления всех узлов дерева

public:
    TreeNode* root;

    BinarySearchTree();
    ~BinarySearchTree();

    /* Метод принимает только ключ key и данные data. Он вызывает приватный метод insert с корнем дерева root. Этот метод является публичным и
    предоставляет интерфейс для вставки нового узла извне класса. */

    void insert(int key, const std::string& data);

    /* Метод принимает только ключ key. Он вызывает приватный метод search с корнем дерева root. Этот метод обеспечивает доступ пользователя к
    операции поиска узла по ключу без необходимости передавать корень дерева вручную. */

    TreeNode* search(int key);
    void remove(int key);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void balanceTree(TreeNode*& node); // метод для балансировки дерева
    int getHeight(TreeNode* root); // метод для получения высоты дерева
    void printTree(TreeNode* root); // метод для печати исходного дерева
    void rotateLeft(TreeNode*& node);
    void rotateRight(TreeNode*& node);
};

#endif // BINARYSEARCHTREE_H
