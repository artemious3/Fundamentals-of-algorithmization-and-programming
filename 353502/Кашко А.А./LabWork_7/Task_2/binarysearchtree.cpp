#include "binarysearchtree.h"
#include <iostream>
#include <algorithm>
#include <queue>

BinarySearchTree::BinarySearchTree() : root(nullptr) {} // конструктор, инициализируем корень дерева

BinarySearchTree::~BinarySearchTree() { // деструктор, передаём корень дерева (основной элемент), чтобы очистить память от всех узлов дерева
    destroyTree(root);
}

// метод для вставки нового узла в дерево
void BinarySearchTree::insert(TreeNode*& node, int key, const std::string& data) { // указатель на узел (короень), ключ key и строка data
    if (node == nullptr) { // проверяем пустой ли узел
        node = new TreeNode(key, data); // создаём новый узел
    } else {
        if (key < node->key) { // проверяем, меньше ли переданный ключ key ключа узла node
            insert(node->left, key, data); // рекурсивно вызываем функцию insert для левого поддерева узла node
        } else if (key > node->key) {
            insert(node->right, key, data); // рекурсивно вызываем функцию insert для правого поддерева узла node
        }
    }
}

void BinarySearchTree::insert(int key, const std::string& data) {
    insert(root, key, data);
}

// метод для получения высоты дерева
/*  1) Сначала вызываем функцию с корневым узлом, который содержит значение 1.
    2) Проверяем, не является ли корневой узел пустым (nullptr). В данном случае, это не так, значит, переходим к следующему шагу.
    3) Вызываем рекурсивно getHeight для левого поддерева, то есть для узла со значением 2.
    4) Теперь getHeight вызывается с узлом, содержащим значение 2.
    5) Проверяем, не является ли он пустым. Он не пуст, значит, переходим дальше.
    6) Для узла со значением 2 вызываем рекурсивно getHeight для его левого и правого поддеревьев.
    7) Левое поддерево у узла 2 — это узел со значением 4. Вызываем getHeight для него, но так как это листовой узел (у него нет детей), высота этого поддерева равна 0.
    8) Правое поддерево у узла 2 — это узел со значением 5. Вызываем getHeight для него, аналогично, его высота также равна 0.
    9) Возвращаем максимальное из этих двух значений (0), к которому добавляем 1, получаем 1. Таким образом, высота поддерева с корнем в узле 2 равна 1.
    10) Возвращаемся обратно к узлу 1, для которого мы вызывали getHeight.
    11) Теперь вызываем getHeight для правого поддерева узла 1, то есть для узла со значением 3.
    12) Процесс повторяется аналогично шагам 3 и 4 для узла 2. Высота правого поддерева у узла 1 также равна 1.
    13) Теперь возвращаем максимальное из высот левого и правого поддеревьев узла 1, к которому добавляем 1. Это будет общая высота дерева.
    14) Максимальное из 1 и 1 — это 1. К нему добавляем 1, получаем 2. */
int BinarySearchTree::getHeight(TreeNode* root) {
    if (root == nullptr) // если корень (самый верхний элемент) равен нулю, то дерево пустое
        return 0;
    else {
        int leftHeight = getHeight(root->left); // вызываем рекурсивно метод для левого поддерева
        int rightHeight = getHeight(root->right); // вызываем рекурсивно метод для правого поддерева
        return std::max(leftHeight, rightHeight) + 1; // наибольшее из поддеревьев + корень (+ 1) - это и будет высота дерева
    }
}

// метод для поиска узла с заданным ключом в дереве
TreeNode* BinarySearchTree::search(TreeNode* node, int key) { // принимаем указатель на корень и ключ, который ищем
    if (node == nullptr || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return search(node->left, key);
    }
    return search(node->right, key);
}

TreeNode* BinarySearchTree::search(int key) {
    return search(root, key);
}

/* Самым минимальным элементом всегда будет самй нижний по левому краю. Следовательно, двигаемся вечно влево. */
// метод для поиска узла с минимальным ключом в поддереве с корнем в указанном узле
TreeNode* BinarySearchTree::minValueNode(TreeNode* node) { // передаём узел
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// метод для удаления узла с заданным ключом из дерева
TreeNode* BinarySearchTree::deleteNode(TreeNode* root, int key) { // принимаем корень дерева и ключ элемента, который хотим удалить
    if (root == nullptr) { // если дерево пустое, то удалять нечего
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else { // нашли элемент с заданным ключом, который нужно удалить
        if (root->left == nullptr) { // проверяем, есть ли левый потомок (нет левого потомка -> правый потомок становится новым корнем поддерева)
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) { // проверяем, есть ли правый потомок (нет правого потомка -> левый потомок становится новым корнем поддерева)
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        /* если у текущего узла есть оба потомка, мы находим наименьший узел в правом поддереве (temp), копируем его ключ и данные в текущий узел (root),
        а затем рекурсивно вызываем функцию deleteNode для удаления узла (temp) из правого поддерева. */
        TreeNode* temp = minValueNode(root->right);
        root->key = temp->key;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->key);
    }
    return root; // возвращает корень поддерева после удаления узла с ключом key
}

void BinarySearchTree::remove(int key) {
    root = deleteNode(root, key);
}

// метод для печати узлов дерева в порядке "возрастания ключа"
void BinarySearchTree::printInOrder(TreeNode* node) {
    if (node != nullptr) {
        printInOrder(node->left);
        std::cout << "(" << node->key << ", " << node->data << ") ";
        printInOrder(node->right);
    }
}

void BinarySearchTree::printInOrder() {
    printInOrder(root);
    std::cout << std::endl;
}

// метод для печати узлов дерева в префиксном порядке (текущий - левый - правый)
void BinarySearchTree::printPreOrder(TreeNode* node) {
    if (node != nullptr) {
        std::cout << "(" << node->key << ", " << node->data << ") ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}

void BinarySearchTree::printPreOrder() {
    printPreOrder(root);
    std::cout << std::endl;
}

// метод для печати узлов дерева в постфиксном порядке (левый - правый - текущий)
void BinarySearchTree::printPostOrder(TreeNode* node) {
    if (node != nullptr) {
        printPostOrder(node->left);
        printPostOrder(node->right);
        std::cout << "(" << node->key << ", " << node->data << ") ";
    }
}

void BinarySearchTree::printPostOrder() {
    printPostOrder(root);
    std::cout << std::endl;
}

// метод для удаления всех узлов дерева
void BinarySearchTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// метод для печати исходного дерева
void BinarySearchTree::printTree(TreeNode* root) {
    if (root == nullptr) {
        std::cout << "Дерево пусто" << std::endl;
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* currentNode = q.front();
            q.pop();

            std::cout << "(" << currentNode->key << ", " << currentNode->data << ") ";

            if (currentNode->left) {
                q.push(currentNode->left);
            }
            if (currentNode->right) {
                q.push(currentNode->right);
            }
        }
    }
    std::cout << std::endl;
}

// поворот влево
void BinarySearchTree::rotateLeft(TreeNode*& node) {
    TreeNode* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node = temp;
}

// поворот вправо
void BinarySearchTree::rotateRight(TreeNode*& node) {
    TreeNode* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node = temp;
}

// балансировка дерева
void BinarySearchTree::balanceTree(TreeNode*& node) {
    if (node == nullptr) {
        return;
    }

    balanceTree(node->left);
    balanceTree(node->right);

    int balanceFactor = getHeight(node->left) - getHeight(node->right);

    if (balanceFactor > 1) {
        // Левое поддерево несбалансировано
        if (getHeight(node->left->left) >= getHeight(node->left->right)) {
            // Простой поворот вправо
            rotateRight(node);
        } else {
            // Двойной поворот влево-вправо
            rotateLeft(node->left);
            rotateRight(node);
        }
    } else if (balanceFactor < -1) {
        // Правое поддерево несбалансировано
        if (getHeight(node->right->right) >= getHeight(node->right->left)) {
            // Простой поворот влево
            rotateLeft(node);
        } else {
            // Двойной поворот вправо-влево
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
}
