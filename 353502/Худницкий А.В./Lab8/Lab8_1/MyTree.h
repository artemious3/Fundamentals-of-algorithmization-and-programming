#ifndef MYTREE_H
#define MYTREE_H

#include <QString>

class Node{
public:

    int key = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int key){
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node(){
        this->left = nullptr;
        this->right = nullptr;
    }

};

class BinTree{
public:

    void insert(int key){
        root = insert(root, key);
    }


    QString print(){
        i = -1;
        out = "";
        return Print(root);
    }

    bool search(int key){
        Node* node = Search(root, key);
        if (node!= nullptr && node->key == key){
            return true;
        }
        else {
            return false;
        }
    }

    void deleteNode(int key) {

        root = deleteNode(root, key);
    }

private:

    Node* root = nullptr;

    Node* insert(Node* node, int key){
        if (node == nullptr){
            return new Node(key);
        }

        if (key < node->key){
            node->left = insert(node->left, key);
        }
        else {
            node->right = insert(node->right, key);
        }

        return node;
    }
    int i = -1;
    QString out = "";

    QString Print(Node* node){
        i++;
        if (node != nullptr){
            out += " " + QString::number(node->key) + "-" + QString::number(i);
            Print(node->left);
            i -= 1;
            Print(node->right);
            i -= 1;
            return out;
        }
        else
        {
            return out;
        }

    }


    Node* Search(Node* node, int key){
        if (node == nullptr || node->key == key){
            return node;
        }

        if (key < node->key){
            return Search(node->left, key);
        }
        else
        {
            return Search(node->right, key);
        }
    }


    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current && current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return root;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }

        return root;
    }
};


#endif // MYTREE_H
