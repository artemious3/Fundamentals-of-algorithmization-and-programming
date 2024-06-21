#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <QDebug>
#include <cmath>
#include <memory>
#include "ListIterator.h"
#include "Node.h"

template <class Key, class Value>

class RedBlackTree {

 public:
  ~RedBlackTree() = default;
  RedBlackTree() : root(nullptr), str(""){};

  Node<Key, Value>* root;
  QString str;

  void remove(Key key) {
    Node<Key, Value>* node = find(key, root);
    remove(node);
  }

  ListIterator<Key, Value> begin() {
    Node<Key, Value>* minNode = findMin(root);
    return ListIterator<Key, Value>(minNode);
  }

  ListIterator<Key, Value> end() {
    Node<Key, Value>* maxNode = findMax(root);
    return ListIterator<Key, Value>(maxNode);
  }

  void insert(Key key, Value value) {
    if (find(key, root) != nullptr) {
      throw std::runtime_error("Ключ должен быть уникальным!");
    }
    Node<Key, Value>* parent = nullptr;
    Node<Key, Value>* currentNode = root;

    while (currentNode) {
      parent = currentNode;

      if (key < currentNode->data.first) {
        currentNode = currentNode->left;
      } else {
        currentNode = currentNode->right;
      }
    }

    Node<Key, Value>* newNode = new Node<Key, Value>(key, value);
    newNode->parent = parent;

    if (parent == nullptr) {
      root = newNode;
    } else if (key < parent->data.first) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    balance(newNode);
  }

  QString find(Key key) {
    Node<Key, Value>* res = find(key, root);
    return QString(res ? QString(res->value) : "Нет элемента с таким ключом!");
  }

  QString printPreOrder() {
    str.clear();
    preOrderHelper(root);
    return str;
  }

  QString printInOrder() {
    str.clear();
    inOrderHelper(root);
    return str;
  }

 private:
  bool exists(Node<Key, Value>* node) { return node != nullptr; }

  int getBalance(Node<Key, Value>* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
  }

  int getHeight(Node<Key, Value>* node) { return (node ? node->height : -1); }

  void updateHeight(Node<Key, Value>* node) {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  }

  Node<Key, Value>* getParent(Node<Key, Value>* node) {
    if (node && exists(node->parent)) {
      return node->parent;
    }
    return nullptr;
  }

  Node<Key, Value>* getGrandad(Node<Key, Value>* node) {
    if (node && exists(node->parent) && exists(node->parent->parent)) {
      return node->parent->parent;
    }
    return nullptr;
  }

  Node<Key, Value>* getUncle(Node<Key, Value>* node) {
    Node<Key, Value>* gran = getGrandad(node);
    if (node && gran != nullptr) {
      if (node->parent == gran->right) {
        return gran->left;
      } else {
        return gran->right;
      }
    }
    return nullptr;
  }

  Node<Key, Value>* getBro(Node<Key, Value>* node) {
    Node<Key, Value>* dad = getParent(node);
    if (node && dad != nullptr) {
      if (node == dad->right) {
        return dad->left;
      } else {
        return dad->right;
      }
    }
    return nullptr;
  }

  Node<Key, Value>* find(Key key, Node<Key, Value>* node) {
    if (!node) {
      return nullptr;
    } else if (node->data.first == key) {
      return node;
    }
    return (key < node->data.first) ? find(key, node->left)
                                    : find(key, node->right);
  }

  Node<Key, Value>* findMin(Node<Key, Value>* node) {
    if (!node) {
      return nullptr;
    } else if (!node->left) {
      return node;
    }
    return findMin(node->left);
  }

  Node<Key, Value>* findMax(Node<Key, Value>* node) {
    if (!node) {
      return nullptr;
    } else if (!node->right) {
      return node;
    }
    return findMax(node->right);
  }

  void makeConnection(Node<Key, Value>* node, Node<Key, Value>* child) {
    if (node == root) {
      root = child;
    } else if (node == node->parent->left) {
      node->parent->left = child;
    } else {
      node->parent->right = child;
    }
    if (child != nullptr) {
      child->parent = node->parent;
    }
  }

  void remove(Node<Key, Value>* node) {
    if (!node) {
      return;
    }

    colors originalColor = node->getColor();
    Node<Key, Value>* child = nullptr;

    if (getChildrenCount(node) == 0) {
      // Нет детей
      if (node == root) {
        root = nullptr;
      } else {
        if (originalColor == BLACK) {
          fixRulesAfterRemoval(node);
        }
        makeConnection(node, nullptr);
      }
    } else if (getChildrenCount(node) == 1) {
      // Один ребенок
      child = getOneChild(node);
      makeConnection(node, child);
      if (originalColor == BLACK) {
        if (child) {
          fixRulesAfterRemoval(child);
        }
      }
    } else {
      // Два ребенка
      Node<Key, Value>* minNode = findMin(node->right);
      originalColor = minNode->getColor();
      child = getOneChild(minNode);
      if (minNode->parent == node) {
        if (child) {
          child->parent = minNode;
        }
      } else {
        makeConnection(minNode, child);
        minNode->right = node->right;
        if (minNode->right) {
          minNode->right->parent = minNode;
        }
      }
      makeConnection(node, minNode);
      minNode->left = node->left;
      if (minNode->left) {
        minNode->left->parent = minNode;
      }
      minNode->setColor(node->getColor());
    }

    delete node;  // Удаляем старый узел

    if (originalColor == BLACK) {
      if (child) {
        fixRulesAfterRemoval(child);
      }
    }
  }

  bool isBlack(Node<Key, Value>* node) {
    return node == nullptr || node->getColor() == BLACK;
  }

  void fixRulesAfterRemoval(Node<Key, Value>* node) {
    while (node != root && isBlack(node)) {
      if (node == node->parent->left) {
        Node<Key, Value>* brother = getBro(node);
        if (brother->getColor() == RED) {
          brother->setColor(BLACK);
          node->parent->setColor(RED);
          leftRot(node->parent);
          brother = node->parent->right;
        } else {
          if (isBlack(brother->left) && isBlack(brother->right)) {
            if (isBlack(brother->parent) && brother->parent == root) {
              brother->setColor(RED);
            } else if (brother->parent->getColor() == RED) {
              brother->setColor(RED);
              brother->parent->setColor(BLACK);
            } else {
              brother->parent->setColor(RED);
              leftRot(brother->parent);
            }
          } else {
            if (isBlack(brother->right)) {
              brother->left->setColor(BLACK);
              brother->setColor(RED);
              rightRot(brother);
              brother = node->parent->right;
            }
            brother->setColor(node->parent->getColor());
            node->parent->setColor(BLACK);
            if (brother->right) {
              brother->right->setColor(BLACK);
            }
            leftRot(node->parent);
            node = root;
          }
        }
      } else {
        Node<Key, Value>* brother = node->parent->left;
        if (brother->getColor() == RED) {
          brother->setColor(BLACK);
          node->parent->setColor(RED);
          rightRot(node->parent);
          brother = node->parent->left;
        } else {
          if (isBlack(brother->left) && isBlack(brother->right)) {
            if (isBlack(brother->parent) && brother->parent == root) {
              brother->setColor(RED);
            } else if (brother->parent->getColor() == RED) {
              brother->setColor(RED);
              brother->parent->setColor(BLACK);
            } else {
              brother->parent->setColor(RED);
              rightRot(brother->parent);
            }
          } else {
            if (isBlack(brother->left)) {
              brother->right->setColor(BLACK);
              brother->setColor(RED);
              leftRot(brother);
              brother = node->parent->left;
            }
            brother->setColor(node->parent->getColor());
            node->parent->setColor(BLACK);
            if (brother->left) {
              brother->left->setColor(BLACK);
            }
            rightRot(node->parent);
            node = root;
          }
        }
      }
    }
    if (node) {
      node->setColor(BLACK);
    }
  }

  int getChildrenCount(Node<Key, Value>* node) {
    int count = 0;
    if (exists(node->left)) {
      count += 1;
    }
    if (exists(node->right)) {
      count += 1;
    }
    return count;
  }

  Node<Key, Value>* getOneChild(Node<Key, Value>* node) {
    return exists(node->left) ? node->left : node->right;
  }

  void rightRot(Node<Key, Value>* node) {
    if (node->left) {
      node->swapNodes(node, node->left);
      Node<Key, Value>* buffer = node->right;
      node->right = node->left;
      node->left = node->right->left;
      node->right->left = node->right->right;
      node->right->right = buffer;

      if (exists(buffer)) {
        buffer->parent = node->right;
      }
      if (exists(node->left)) {
        node->left->parent = node;
      }
      if (exists(node->right->left)) {
        node->right->left->parent = node->right;
      }
      node->right->parent = node;
    }
  }

  void leftRot(Node<Key, Value>* node) {
    if (node->right) {
      node->swapNodes(node, node->right);
      Node<Key, Value>* buffer = node->left;
      node->left = node->right;
      node->right = node->left->right;
      node->left->right = node->left->left;
      node->left->left = buffer;

      if (exists(buffer)) {
        buffer->parent = node->left;
      }
      if (exists(node->right)) {
        node->right->parent = node;
      }
      if (exists(node->left->right)) {
        node->left->right->parent = node->left;
      }
      node->left->parent = node;
    }
  }

  void balance(Node<Key, Value>* node) {
    node->setColor(RED);

    while (node != root && node->parent->getColor() == RED) {
      if (node->parent == node->parent->parent->left) {
        Node<Key, Value>* uncle = node->parent->parent->right;

        if (uncle && uncle->getColor() == RED) {
          node->parent->setColor(BLACK);
          uncle->setColor(BLACK);
          node->parent->parent->setColor(RED);
          node = node->parent->parent;
        } else {
          if (node == node->parent->right) {
            node = node->parent;
            leftRot(node);
          }
          node->parent->setColor(BLACK);
          node->parent->parent->setColor(RED);
          rightRot(node->parent->parent);
        }
      } else {
        Node<Key, Value>* uncle = node->parent->parent->left;

        if (uncle && uncle->getColor() == RED) {
          node->parent->setColor(BLACK);
          uncle->setColor(BLACK);
          node->parent->parent->setColor(RED);
          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            rightRot(node);
          }
          node->parent->setColor(BLACK);
          node->parent->parent->setColor(RED);
          leftRot(node->parent->parent);
        }
      }
    }
    root->setColor(BLACK);
  }

  void preOrderHelper(Node<Key, Value>* node) {
    if (node == nullptr) {
      return;
    }
    str +=
        node->data.second + QString(node->getColor() == RED ? "R" : "B") + '\n';
    preOrderHelper(node->left);
    preOrderHelper(node->right);
  }

  void inOrderHelper(Node<Key, Value>* node) {
    if (node == nullptr) {
      return;
    }
    inOrderHelper(node->left);
    str += "(" + QString(node->data.first) + ", " + QString(node->data.second) + ") ";
    inOrderHelper(node->right);
  }
};

#endif  // REDBLACKTREE_H
