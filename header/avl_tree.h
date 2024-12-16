#ifndef OSAP_HEADER_AVLTREE_ADAPTEE_H_
#define OSAP_HEADER_AVLTREE_ADAPTEE_H_

#include <iostream>
#include <memory>
#include <cmath>
#include <queue>
#include <iomanip>
using namespace std;

struct node {
    int key;
    node* parent;
    node* left;
    node* right;
    int height;
    int size;
    node(int key);
};

class AVLTree {
public:
    AVLTree();

    int GetDepth(node* n); //
    int GetHeightByNode(node* n); //
    int GetSubTreeSize(node* n);
    void UpdateSubTreeSize(node* n);
    int Finding(int key); //
    node* Search(node* cur_node, int key); //
    void UpdateHeight(node* n);
    int GetBalance(node* n);
    node* RotateRight(node* y);
    node* RotateLeft(node* x);
    node* Balance(node* n);
    int Inserting(int x);
    int IsEmpty(); //
    int GetSize(); //
    int GetHeight(); //
    void GetAncestor(int x);
    void GetAverage(int x);
    void GetRank(int x);
    void Erasing(int key);

private:
    node* root_;
    int size_;
};

#endif
