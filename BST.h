#include <iostream>
#include <memory>
#include <cmath>

struct node {
    int key;
    node* parent;
    node* left;
    node* right;
    node(int key) {
        this->key = key;
        parent = left = right = NULL;
    }
};

class BST {
public:
    BST() {
        root = NULL;
    }

    node *search(node *curNode, int key) {
        if (curNode == NULL) return NULL;

        if (curNode ->key == key)
            return curNode;
        else if (curNode->key < key) {
            return search(curNode->right, key);
        }
        else
            return search(curNode->left, key);
    }

    void insert(int key) {
        if (search(root, key) != NULL) return;

        node *newNode = new node(key); // 추가할 새로운 노드
        if (root == NULL) {
            root = newNode;
            return;
        }

        node* curNode = root;
        node* parNode = NULL;

        while (curNode != NULL) {
            parNode = curNode;
            if (curNode->key < key) {
                curNode = curNode->right;
            }
            else {
                curNode = curNode->left;
            }
        }

        newNode->parent = parNode;
        if (parNode->key < key) {
            parNode->right = newNode;
        }
        else {
            parNode->left = newNode;
        }
    }

    void remove(int key) {
        node *delNode = search(root, key);
        if (delNode == NULL) return;

        node* parNode = delNode->parent;
        node* childNode;

        if (delNode->left == NULL && delNode->right == NULL) {
            childNode = NULL;
        }
        else if (delNode->left == NULL && delNode->right != NULL) {
            childNode = delNode->right;
        }
        else if (delNode->left != NULL && delNode->right == NULL) {
            childNode = delNode->left;
        }
        else {
            childNode = delNode->right;
            while (childNode->left != NULL) {
                childNode = childNode->left;
            }
            delNode->key = childNode->key;
            delNode = childNode;
            parNode = delNode->parent;
            childNode = delNode->right;
        }

        if (parNode == NULL) {
            root = childNode;
            root->parent = NULL;
        } else if (delNode == parNode->left) {
            parNode->left = childNode;
            if (childNode != NULL) childNode->parent = parNode;
        } else {
            parNode->right = childNode;
            if (childNode != NULL) childNode->parent = parNode;
        }

        delete delNode;
    }

private:
    node* root;
};

