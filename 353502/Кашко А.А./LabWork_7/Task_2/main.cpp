#include "mainwindow.h"
#include <iostream>
#include "treenode.h"
#include "binarysearchtree.h"
#include "leafcounterbinarysearchtree.h"

#include <QApplication>

int main() {
    BinarySearchTree bst;
    bst.insert(15, "Node 15");
    bst.insert(13, "Node 13");
    bst.insert(20, "Node 20");
    bst.insert(10, "Node 10");
    bst.insert(14, "Node 14");
    bst.insert(17, "Node 17");
    bst.insert(3, "Node 3");
    bst.insert(11, "Node 11");
    bst.insert(4, "Node 4");

    std::cout << "Вывод дерева: ";
    bst.printTree(bst.root);

    bst.remove(10);
    std::cout << "Вывод дерева: ";
    bst.printTree(bst.root);

    std::cout << "Вывод дерева в порядке увеличения ключа: ";
    bst.printInOrder();

    std::cout << "Вывод дерева в префиксном порядке: ";
    bst.printPreOrder();

    std::cout << "Вывод дерева в постфиксном порядке: ";
    bst.printPostOrder();

    std::cout << "Вывод дерева после балансировки: ";
    bst.balanceTree(bst.root);
    bst.printTree(bst.root);

    std::cout << "Высота дерева: " << bst.getHeight(bst.root) << std::endl;

    LeafCounterBinarySearchTree lcbst;
    lcbst.insert(50, "Node 50");
    lcbst.insert(30, "Node 30");
    lcbst.insert(20, "Node 20");
    lcbst.insert(40, "Node 40");
    lcbst.insert(70, "Node 70");
    lcbst.insert(60, "Node 60");
    lcbst.insert(80, "Node 80");

    lcbst.countLeavesOnEachLevel();

    return 0;
}
