#include "binarysearchtree.h"
#include "queue"

BinarySearchTree::BinarySearchTree() {}

void BinarySearchTree::insert(int key, QString value) {
  root = insert(root, key, value);
}

void BinarySearchTree::remove(int key) {
  root = remove(root, key);
  balance(root);
}

QString BinarySearchTree::find(int key) {
  Node* res = find(root, key);
  return QString(res ? QString(res->value) : "No element with such key!");
}

QString BinarySearchTree::printPreOrder() {
        stroka.clear(); // Очистка stroka перед началом обхода
        preOrderHelper(root); // Вызов вспомогательной функции
        return stroka;
    }

QString BinarySearchTree::printInOrder() {
  return inOrder(root);
}

QString BinarySearchTree::printPostOrder() {
  return postOrder(root);
}

Node* BinarySearchTree::insert(Node* node, int key, QString value) {
  if (!node) {
    return new Node({key, value});
  } else if (key < node->key) {
    node->left = insert(node->left, key, value);
  } else if (key > node->key) {
    node->right = insert(node->right, key, value);
  }
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  balance(node);
  return node;
}

Node* BinarySearchTree::find(Node* node, int key) {
  if (!node) {
    return nullptr;
  } else if (node->key == key) {
    return node;
  }
  return (key < node->key) ? find(node->left, key) : find(node->right, key);
}

Node* BinarySearchTree::remove(Node* node, int key) {
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

Node* BinarySearchTree::findMin(Node* node) {
  if (!node) {
    return nullptr;
  } else if (!node->left) {
    return node;
  }
  return findMin(node->left);
}

void BinarySearchTree::balance(Node* node) {

  if (node == nullptr)
    return;
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

void BinarySearchTree::swap(Node* node1, Node* node2) {
  node1->swapNodes(node1, node2);
}

void BinarySearchTree::rightRot(Node* node) {
  if (node->left) {
    swap(node, node->left);
    Node* buffer = node->right;
    node->right = node->left;
    node->left = node->right->left;
    node->right->left = node->right->right;
    node->right->right = buffer;
    updateHeight(node);
    updateHeight(node->right);
  }
}

void BinarySearchTree::leftRot(Node* node) {
  if (node->right) {  // Проверяем, что узел имеет правого потомка
    swap(node, node->right);
    Node* buffer = node->left;
    node->left = node->right;
    node->right = node->left->right;
    node->left->right = node->left->left;
    node->left->left = buffer;
    updateHeight(node);
    updateHeight(node->left);
  }
}

int BinarySearchTree::getHeight(Node* node) {
  return (node ? node->height : -1);
}

int BinarySearchTree::getBalance(Node* node) {
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

int BinarySearchTree::leftNodesCounter(Node* node) {
  if (!node) {
    return 0;
  }
  int leftCount = leftNodesCounter(node->left);
  int rightCount = leftNodesCounter(node->right);

  if (node->left) {
    leftCount++;
  }
  return leftCount + rightCount;
}

void BinarySearchTree::balanceTree() {
  balance(root);
}

void BinarySearchTree::updateHeight(Node* node) {
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

void BinarySearchTree::preOrderHelper(Node* node) {
    if (node == nullptr) {
        return;
    }
    stroka += node->value + '\n'; // Добавление значения узла в stroka
    preOrderHelper(node->left); // Рекурсивный вызов для левого поддерева
    preOrderHelper(node->right); // Рекурсивный вызов для правого поддерева
}

QString BinarySearchTree::inOrder(Node* node) {
  if (!node) {
    return "";
  }
  QString result = inOrder(node->left);
  result += QString::number(node->key) + ": " + node->value + "\n";
  result += inOrder(node->right);
  return result;
}

QString BinarySearchTree::postOrder(Node* node) {
  if (!node) {
    return "";
  }
  QString result = postOrder(node->left);
  result += postOrder(node->right);
  result += QString::number(node->key) + ": " + node->value + "\n";
  return result;
}
