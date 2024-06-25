#include "leafcounterbinarysearchtree.h"
#include <queue>
#include <iostream>

// функция считает кол-во листьев, на каждом уровне дерева (лист - узел, у которого отсутствует левый и правый потомок)
void LeafCounterBinarySearchTree::countLeavesOnEachLevel() {
    std::queue<TreeNode*> q;
    q.push(root);

    int level = 1; // Начальный уровень дерева

    while (!q.empty()) {
        int levelSize = q.size(); // Размер уровня текущей итерации
        int leafCount = 0;

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* currentNode = q.front();
            q.pop();

            // Проверяем, является ли текущий узел листом
            if (currentNode->left == nullptr && currentNode->right == nullptr) {
                ++leafCount;
            }

            // Добавляем левого потомка в очередь, если он существует
            if (currentNode->left) {
                q.push(currentNode->left);
            }

            // Добавляем правого потомка в очередь, если он существует
            if (currentNode->right) {
                q.push(currentNode->right);
            }
        }

        // Выводим количество листьев на текущем уровне
        std::cout << "Level " << level << ": " << leafCount << " leaves" << std::endl;

        // Переходим к следующему уровню дерева
        ++level;
    }
}
