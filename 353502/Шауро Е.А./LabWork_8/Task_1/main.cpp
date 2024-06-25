#include <iostream>
#include <QString>
#include "BST.h"

int main() {
    BinarySearchTree* tree =  new BinarySearchTree();

    // Вставляем узлы в дерево
    tree->insert(3, "Node 3");
    tree->insert(5, "Node 5");
    tree->insert(10, "Node 10");
    tree->insert(12, "Node 12");
    tree->insert(14, "Node 14");
    tree->insert(20, "Node 20");
    tree->insert(25, "Node 25");

    // Выводим содержимое дерева в различных порядках
    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << tree->printPreOrder().toStdString() << std::endl;

    BinarySearchTree* secondTree =  new BinarySearchTree();

    secondTree->insert(7, "Node 7");
    secondTree->insert(13, "Node 13");
    secondTree->insert(21, "Node 21");

    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << secondTree->printPreOrder().toStdString() << std::endl;

    tree->insertTree(secondTree->root);
    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << tree->printPreOrder().toStdString() << std::endl;

    tree->deleteSubTree(20);
    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << tree->printPreOrder().toStdString() << std::endl;

    tree->insertAtPosition(4, 6, "Node 6", tree->root);
    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << tree->printPreOrder().toStdString() << std::endl;

    return 0;
}
