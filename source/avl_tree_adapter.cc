#include "../header/avl_tree_adapter.h"

// 생성자
AVLTreeAdapter::AVLTreeAdapter(AVLTreeAdaptee adaptee) :
        adaptee_(adaptee) {}

// Find 함수
void AVLTreeAdapter::Find(int x) {
    cout << adaptee_.Finding(x) << endl;
}

// Insert 함수
void AVLTreeAdapter::Insert(int x) {
    cout << adaptee_.Inserting(x) << endl;
}

// Empty 함수
void AVLTreeAdapter::Empty() {
    cout << adaptee_.IsEmpty() << endl;
}

// Size 함수
void AVLTreeAdapter::Size() {
    cout << adaptee_.GetSize() << endl;
}

// Height 함수
void AVLTreeAdapter::Height() {
    cout << adaptee_.GetHeight() << endl;
}

// Ancestor 함수
void AVLTreeAdapter::Ancestor(int x) {
    adaptee_.GetAncestor(x);
}

// Average 함수
void AVLTreeAdapter::Average(int x) {
    adaptee_.GetAverage(x);
}

// Rank 함수
void AVLTreeAdapter::Rank(int x) {
    adaptee_.GetRank(x);
}

// Erase 함수
void AVLTreeAdapter::Erase(int x) {
    adaptee_.Erasing(x);
}
