#include "heaplist.h"

void HeapList::insert(int key) {
  std::shared_ptr<Node> newNode = std::make_shared<Node>(key); // Создание нового узла
  if (!root) {
    root = newNode;
    return;
  }
  // Находим последнее место для вставки
  std::shared_ptr<Node> lastNode = getLastNode();
  if (!lastNode->left) {
    lastNode->left = newNode;
  } else {
    lastNode->right = newNode;
  }
  newNode->parent = lastNode;
  heapifyUp(newNode);
}

void HeapList::remove(int key) {
  std::shared_ptr<Node> node = findNode(root, key);
  if (!node) {
    return;
  }
  std::shared_ptr<Node> lastNode = getLastNode();
  swapValues(node, lastNode);
  removeLastNode();
  heapifyDown(node);
}

bool HeapList::isEmpty() const {
  return !root;
}

int HeapList::getMax() const {
  if (!root) {
    throw std::runtime_error("Heap is empty!");
  }
  return root->key;
}

void HeapList::clear() {
  root.reset();
}

std::shared_ptr<Node> HeapList::findNode(std::shared_ptr<Node> node, int key) {
  if (!node || node->key == key) {
    return node;
  }
  std::shared_ptr<Node> foundNode = findNode(node->left, key);
  if (!foundNode) {
    foundNode = findNode(node->right, key);
  }
  return foundNode;
}

void HeapList::heapifyDown(std::shared_ptr<Node> node) {
  while (node) {
    std::shared_ptr<Node> largest = node;
    if (node->left && node->left->key > largest->key) {
      largest = node->left;
    }
    if (node->right && node->right->key > largest->key) {
      largest = node->right;
    }
    if (largest == node) {
      break;
    }
    swapValues(node, largest);
    node = largest;
  }
}

void HeapList::heapifyUp(std::shared_ptr<Node> node) {
  while (node->parent.lock() && node->key > node->parent.lock()->key) {
    swapValues(node, node->parent.lock());
    node = node->parent.lock();
  }
}

std::shared_ptr<Node> HeapList::getLastNode() {
  if (!root) {
    return nullptr;
  }

  // Level order traversal to find the last node
  std::queue<std::shared_ptr<Node>> q;
  q.push(root);
  std::shared_ptr<Node> lastNode = nullptr;
  while (!q.empty()) {
    lastNode = q.front();
    q.pop();
    if (lastNode->left){
      q.push(lastNode->left);
    }
    if (lastNode->right){
      q.push(lastNode->right);
    }
  }
  return lastNode;
}

void HeapList::removeLastNode() {
  if (!root){
    return;
  }

  std::queue<std::shared_ptr<Node>> q;
  q.push(root);
  std::shared_ptr<Node> lastNode = getLastNode();
  std::shared_ptr<Node> parentNode = lastNode->parent.lock();

  if (parentNode && parentNode->right == lastNode) {
    parentNode->right.reset();
  } else if (parentNode && parentNode->left == lastNode) {
    parentNode->left.reset();
  } else {
    root.reset();
  }
}

void HeapList::swapValues(std::shared_ptr<Node> node1,
                          std::shared_ptr<Node> node2) {
  std::swap(node1->key, node2->key);
}

void HeapList::preOrderPrint(std::shared_ptr<Node> node) const {
  if (!node){
    return;
  }
  std::cout << node->key << " ";
  preOrderPrint(node->left);
  preOrderPrint(node->right);
}

std::shared_ptr<Node> HeapList::getRoot() const
{
    return root;
}
