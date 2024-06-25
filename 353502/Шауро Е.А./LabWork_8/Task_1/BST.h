#ifndef BST_H
#define BST_H
#include <QDebug>
#include <cmath>
#include "Node.h"

class BinarySearchTree {
 public:
  ~BinarySearchTree() { clear(root); }

  Node* root;
  QString str;

  void remove(int key) {
    root = remove(root, key);
    balance(root);
  }

  void insert(int key, QString value) {
    root = insert(key, value, root);
    balance(root);
  }

  QString find(int key) {
    Node* res = find(key, root);
    return QString(res ? QString(res->value) : "No element with such key!");
  }

  QString printPreOrder() {
    str.clear();
    preOrderHelper(root);
    return str;
  }

  QString findLCA(int key1, int key2) {
    Node* first = find(key1, root);
    Node* second = find(key2, root);
    Node* res = findLowestCommonAncestor(root, first, second);
    return QString(res ? QString("Общий предок: &1").arg(QString(res->value))
                       : "В дереве нет даже корня!");
  }

  void insertTree(Node* secondRoot) {
    root = insertTree(secondRoot, root);
    balance(root);
  }

  void deleteSubTree(int key) {
    Node* treeRoot = find(key, root);
    clearSubtree(treeRoot, root);
    balance(root);
  }

  void insertAtPosition(int position, int key, QString value, Node*& node) {
    if (position < 1) {
      qDebug() << "Неверная позиция для вставки!";
      return;
    }

    if (position == 1) {
      Node* newNode = new Node(key, value);
      newNode->left = node;
      node = newNode;
      return;
    }

    if (node == nullptr) {
      qDebug() << "Достигнут конец дерева перед достижением позиции вставки!";
      return;
    }

    if (position <= countNodes(node->left) + 1) {
      insertAtPosition(position - 1, key, value, node->left);
    } else {
      insertAtPosition(position - countNodes(node->left) - 1, key, value,
                       node->right);
    }
  }

  int countNodes(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
  }

 private:
  Node* findLowestCommonAncestor(Node* root, Node* p, Node* q) {
    if (!root) {
      return nullptr;
    }

    if (p->key < root->key && q->key < root->key) {
      return findLowestCommonAncestor(root->left, p, q);
    }

    if (p->key > root->key && q->key > root->key) {
      return findLowestCommonAncestor(root->right, p, q);
    }

    return root;
  }

  Node* insertTree(Node* subtreeRoot, Node* root) {
    if (!subtreeRoot) {
      return root;  // Поддерево пустое, ничего не вставляем
    }

    root = insert(subtreeRoot->key, subtreeRoot->value, root);
    qDebug() << subtreeRoot->key
             << "root";  // Вставляем корень поддерева в AVL-дерево
    root = insertTree(subtreeRoot->left,
                      root);  // Рекурсивно вставляем левое поддерево
    root = insertTree(subtreeRoot->right,
                      root);  // Рекурсивно вставляем правое поддерево

    return root;
  }

  Node* insert(int key, QString value, Node* node) {
    if (!node) {
      return new Node(key, value);
    } else if (key > node->key) {
      node->right = insert(key, value, node->right);
    } else if (key < node->key) {
      node->left = insert(key, value, node->left);
    }
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    balance(node);
    return node;
  }

  int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
  }

  int getHeight(Node* node) { return (node ? node->height : -1); }

  void updateHeight(Node* node) {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  }

  Node* find(int key, Node* node) {
    if (!node) {
      return nullptr;
    } else if (node->key == key) {
      return node;
    }
    return (key < node->key) ? find(key, node->left) : find(key, node->right);
  }

  Node* findMin(Node* node) {
    if (!node) {
      return nullptr;
    } else if (!node->left) {
      return node;
    }
    return findMin(node->left);
  }

  Node* remove(Node* node, int key) {
    if (!node) {
      return nullptr;
    } else if (key < node->key) {
      node->left = remove(node->left, key);
    } else if (key > node->key) {
      node->right = remove(node->right, key);
    } else {
      if (!node->left || !node->right) {
        Node* temp = node;
        node = node->left ? node->left : node->right;
        delete temp;
      } else {
        Node* successor = findMin(node->right);
        node->key = successor->key;
        node->value = successor->value;
        node->right = remove(node->right, successor->key);
      }
      if (node) {
        updateHeight(node);
        balance(node);
      }
    }
    return node;
  }

  void rightRot(Node* node) {
    if (node->left) {
      node->swapNodes(node, node->left);
      Node* buffer = node->right;
      node->right = node->left;
      node->left = node->right->left;
      node->right->left = node->right->right;
      node->right->right = buffer;
      updateHeight(node);
      updateHeight(node->right);
    }
  }

  void leftRot(Node* node) {
    if (node->right) {  // Проверяем, что узел имеет правого потомка
      node->swapNodes(node, node->right);
      Node* buffer = node->left;
      node->left = node->right;
      node->right = node->left->right;
      node->left->right = node->left->left;
      node->left->left = buffer;
      updateHeight(node);
      updateHeight(node->left);
    }
  }

  void balance(Node* node) {

    if (node == nullptr) {
      return;
    }
    int blnc = getBalance(node);
    if (blnc < -1) {
      if (getHeight(node->right->right) >= getHeight(node->right->left)) {
        leftRot(node);
      } else {
        rightRot(node->right);
        leftRot(node);
      }
    }
    if (blnc > 1) {
      if (getHeight(node->left->left) >= getHeight(node->left->right)) {
        rightRot(node);
      } else {
        leftRot(node->left);
        rightRot(node);
      }
      balance(node->left);
      balance(node->right);
    }
  }

  void preOrderHelper(Node* node) {
    if (node == nullptr) {
      return;
    }
    str += node->value + '\n';
    preOrderHelper(node->left);
    preOrderHelper(node->right);
  }

  void clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  void clearSubtree(Node* treeRoot, Node* root) {
    if (treeRoot == nullptr) {
      return;
    }
    clearSubtree(treeRoot->left, treeRoot);
    clearSubtree(treeRoot->right, treeRoot);

    if (root != nullptr) {
      if (root->left == treeRoot) {
        root->left = nullptr;
      } else if (root->right == treeRoot) {
        root->right = nullptr;
      }
    }

    delete treeRoot;
  }
};

#endif  // BST_H
