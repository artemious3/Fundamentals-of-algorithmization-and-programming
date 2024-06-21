#include <iostream>
#include <QString>
#include "binarysearchtree.h"

int main() {
    BinarySearchTree tree;

    // Вставляем узлы в дерево
    tree.insert(10, "Node 10");
    tree.insert(20, "Node 20");
    tree.insert(30, "Node 30");
    tree.insert(40, "Node 40");
    tree.insert(50, "Node 50");
    tree.insert(60, "Node 60");
    tree.insert(70, "Node 70");
    tree.insert(80, "Node 80");
    tree.insert(100, "Node 100");

    tree.balanceTree();

    // Выводим содержимое дерева в различных порядках
    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << tree.printPreOrder().toStdString() << std::endl;

    std::cout << "In-order traversal:" << std::endl;
    std::cout << tree.printInOrder().toStdString() << std::endl;

    std::cout << "Post-order traversal:" << std::endl;
    std::cout << tree.printPostOrder().toStdString() << std::endl;

    // Поиск элемента по ключу
    int keyToFind = 40;
    std::cout << "Searching for key " << keyToFind << ": " << tree.find(keyToFind).toStdString() << std::endl;

    // Удаляем узел из дерева
    int keyToRemove = 80;
    tree.remove(keyToRemove);
    tree.remove(100);
    tree.remove(70);
    std::cout << "Removed node with key " << keyToRemove << std::endl;

    // Выводим обновленное содержимое дерева
    std::cout << "printPostOrderr traversal after removing node:" << std::endl;
    std::cout << tree.printPreOrder().toStdString() << std::endl;

    // Подсчитываем количество узлов в левой ветви дерева
    std::cout << "Number of nodes in the left branch: " << tree.leftNodesCounter(tree.root->left) << std::endl;

    return 0;
}
