#ifndef OSAP_HEADER_AVLTREE_ADAPTER_H_
#define OSAP_HEADER_AVLTREE_ADAPTER_H_

#include <iostream>
#include <memory>
#include <cmath>
#include <queue>
#include <iomanip>
#include "AVLTree.h"
#include "AVLTreeAdaptee.h"
using namespace std;

class AVLTreeAdapter : public AVLTree{
public:
    AVLTreeAdapter(AVLTreeAdaptee adaptee) :
        adaptee_(adaptee) {}

    void Find(int x) override {
        cout << adaptee_.Finding(x) << endl;
    }
    void Insert(int x) override {
        cout << adaptee_.Inserting(x) << endl;
    }
    void Empty() override {
        cout << adaptee_.IsEmpty() << endl;
    }
    void Size() override {
        cout << adaptee_.GetSize() << endl;
    }
    void Height() override {
        cout << adaptee_.GetHeight() << endl;
    }
    void Ancestor(int x) override {
        adaptee_.GetAncestor(x);
    }
    void Average(int x) override {
        adaptee_.GetAverage(x);
    }
    void Rank(int x) override {
        adaptee_.GetRank(x);
    }
    void Erase(int x) override {
        adaptee_.Erasing(x);
    }

    void PrintTree() override {
        adaptee_.PrintTree();
    }

private:
    AVLTreeAdaptee adaptee_;
};

#endif