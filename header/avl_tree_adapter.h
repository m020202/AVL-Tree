#ifndef OSAP_HEADER_AVLTREE_ADAPTER_H_
#define OSAP_HEADER_AVLTREE_ADAPTER_H_

#include <iostream>
#include <memory>
#include <cmath>
#include <queue>
#include <iomanip>
#include "avl_tree.h"
#include "avl_tree_adaptee.h"
using namespace std;

class AVLTreeAdapter : public AVLTree {
public:
    // 생성자
    AVLTreeAdapter(AVLTreeAdaptee adaptee);

    // 멤버 함수들
    void Find(int x) override;
    void Insert(int x) override;
    void Empty() override;
    void Size() override;
    void Height() override;
    void Ancestor(int x) override;
    void Average(int x) override;
    void Rank(int x) override;
    void Erase(int x) override;

private:
    AVLTreeAdaptee adaptee_;  // 내부적으로 사용할 avl_tree_adaptee 객체
};

#endif  // OSAP_HEADER_AVLTREE_ADAPTER_H_
