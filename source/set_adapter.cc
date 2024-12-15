#include "../header/set_adapter.h"

// 생성자
SetAdapter::SetAdapter(AVLTree avlTree) :
        avlTree_(avlTree) {}

// Find 함수
void SetAdapter::Find(int x) {
    cout << avlTree_.Finding(x) << endl;
}

// Insert 함수
void SetAdapter::Insert(int x) {
    cout << avlTree_.Inserting(x) << endl;
}

// Empty 함수
void SetAdapter::Empty() {
    cout << avlTree_.IsEmpty() << endl;
}

// Size 함수
void SetAdapter::Size() {
    cout << avlTree_.GetSize() << endl;
}

// Height 함수
void SetAdapter::Height() {
    cout << avlTree_.GetHeight() << endl;
}

// Ancestor 함수
void SetAdapter::Ancestor(int x) {
    avlTree_.GetAncestor(x);
}

// Average 함수
void SetAdapter::Average(int x) {
    avlTree_.GetAverage(x);
}

// Rank 함수
void SetAdapter::Rank(int x) {
    avlTree_.GetRank(x);
}

// Erase 함수
void SetAdapter::Erase(int x) {
    avlTree_.Erasing(x);
}
