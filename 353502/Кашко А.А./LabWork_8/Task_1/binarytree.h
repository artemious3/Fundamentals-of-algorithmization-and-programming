#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QString>

template<typename T>
struct Node
{
    T data;
    Node<T> *left;
    Node<T> *right;
};

template<typename T>
class BinaryTree
{
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(root); }

    // метод для доступа к корневому узлу
    Node<T>* getRoot() const { return root; }

    void add(const T& value)
    {
        add(root, value);
    }

    void remove(const T& value)
    {
        remove(root, value);
    }

    bool find(const T& value)
    {
        return find(root, value);
    }

    QString traverse() const
    {
        return traverse(root);
    }

    // метод для вставки поддерева/ветки
    void insertSubtree(BinaryTree<T>& subtree)
    {
        if (subtree.root == nullptr)
            return;

        if (root == nullptr) {
            root = subtree.root;
            subtree.root = nullptr;
            return;
        }

        insertSubtreeRecursive(root, subtree.root);

        subtree.root = nullptr;
    }

    void insertSubtreeRecursive(Node<T>*& currentRoot, Node<T>*& subtreeRoot)
    {
        if (subtreeRoot == nullptr)
            return;

        if (subtreeRoot->left != nullptr)
            insertSubtreeRecursive(currentRoot, subtreeRoot->left);

        if (subtreeRoot->right != nullptr)
            insertSubtreeRecursive(currentRoot, subtreeRoot->right);

        if (subtreeRoot->data < currentRoot->data) {
            if (currentRoot->left == nullptr)
                currentRoot->left = subtreeRoot;
            else
                insertSubtreeRecursive(currentRoot->left, subtreeRoot);
        } else {
            if (currentRoot->right == nullptr)
                currentRoot->right = subtreeRoot;
            else
                insertSubtreeRecursive(currentRoot->right, subtreeRoot);
        }

        subtreeRoot = nullptr;
    }

    // метод для удаления поддерева/ветки
    void removeSubtree(Node<T>* subtreeRoot)
    {
        if (subtreeRoot == nullptr)
            return;

        Node<T>* parentNode = findParentNode(root, subtreeRoot);
        if (parentNode != nullptr) {
            if (parentNode->left == subtreeRoot) {
                clear(parentNode->left);
                parentNode->left = nullptr;
            } else if (parentNode->right == subtreeRoot) {
                clear(parentNode->right);
                parentNode->right = nullptr;
            }
        } else if (root == subtreeRoot) {
            clear(root);
            root = nullptr;
        }
    }

    void insertAtPosition(const T& parentValue, const T& value, bool left)
    {
        Node<T> *parentNode = findNode(root, parentValue);
        if (parentNode != nullptr) {
            Node<T> *newNode = new Node<T>;
            newNode->data = value;
            newNode->left = nullptr;
            newNode->right = nullptr;

            if ((left && value <= parentNode->data) || (!left && value > parentNode->data)) {
                if (left)
                    parentNode->left = newNode;
                else
                    parentNode->right = newNode;
            } else {
                delete newNode;
                // MassengBox::display("Ошибка: Вставка нарушает свойство бинарного дерева поиска!");
            }
        }
    }

    T findLowestCommonAncestor(const T& value1, const T& value2)
    {
        Node<T>* resultNode = findLowestCommonAncestor(root, value1, value2);
        if (resultNode != nullptr)
            return resultNode->data;
        else
            return T();
    }

private:
    Node<T> *root;
    Node<T> *help;

    void add(Node<T> *&node, const T& value)
    {
        if (node == nullptr) {
            node = new Node<T>;
            node->data = value;
            node->left = nullptr;
            node->right = nullptr;
        } else {
            if (value < node->data)
                add(node->left, value);
            else if (value > node->data)
                add(node->right, value);
        }
    }

    void remove(Node<T> *&node, const T& value)
    {
        if (node == nullptr)
            return;
        if (value < node->data)
            remove(node->left, value);
        else if (value > node->data)
            remove(node->right, value);
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                Node<T> *temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                Node<T> *temp = node->left;
                while (temp->right != nullptr)
                    temp = temp->right;
                node->data = temp->data;
                remove(node->left, temp->data);
            } else {
                Node<T> *temp = node->right;
                while (temp->left != nullptr)
                    temp = temp->left;
                node->data = temp->data;
                remove(node->right, temp->data);
            }
        }
    }

    // метод для поиска узла, который возвращает булевское значение (true или false)
    bool find(Node<T> *node
              , const T& value)
    {
        if (node == nullptr)
            return false;
        if (value < node->data)
            return find(node->left, value);
        else if (value > node->data)
            return find(node->right, value);
        else
            return true;
    }

    // метод для обходки дерева
    QString traverse(Node<T> *node) const
    {
        QString result;
        if (node != nullptr) {
            result += traverse(node->left);
            result += QString::number(node->data) + " ";
            result += traverse(node->right);
        }
        return result;
    }

    // метод для поиска узла, который возвращает значение искомого элемента
    Node<T>* findNode(Node<T> *node, const T& value)
    {
        if (node == nullptr)
            return nullptr;
        if (node->data == value)
            return node;
        Node<T> *left = findNode(node->left, value);
        Node<T> *right = findNode(node->right, value);
        return left != nullptr ? left : right;
    }

    // метод для поиска родительского узла для заданного узла
    Node<T>* findParentNode(Node<T> *node, const T& value)
    {
        if (node == nullptr)
            return nullptr;
        if ((node->left != nullptr && node->left->data == value) ||
            (node->right != nullptr && node->right->data == value))
            return node;
        Node<T> *left = findParentNode(node->left, value);
        Node<T> *right = findParentNode(node->right, value);
        return left != nullptr ? left : right;
    }

    // метод для поиска наименьшего общего предка двух узлов
    // метод для поиска наименьшего общего предка двух узлов
    Node<T>* findLowestCommonAncestor(Node<T>* node, const T& value1, const T& value2)
    {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->data > value1 && node->data > value2) {
            help = node;
            return findLowestCommonAncestor(node->left, value1, value2);
        }
        if (node->data < value1 && node->data < value2) {
            return node;
        }
        if ((node->data > value1 && node->data < value2) || (node->data > value1 && node->data < value2)) {
            return node;
        }
        if (node->data == value1 || node->data == value2) {
            return help;
        }
    }

    void clear(Node<T> *node)
    {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

#endif // BINARYTREE_H
