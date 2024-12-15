#ifndef OSAP_HEADER_AVLTREE_ADAPTER_H_
#define OSAP_HEADER_AVLTREE_ADAPTER_H_

#include <iostream>
#include <memory>
#include <cmath>
#include <queue>
#include <iomanip>
#include "set.h"
#include "avl_tree.h"
using namespace std;

class SetAdapter : public Set {
public:
    // 생성자
    SetAdapter(AVLTree avlTree);

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
    AVLTree avlTree_;  // 내부적으로 사용할 AVLTreeAdaptee 객체
};

#endif  // OSAP_HEADER_AVLTREE_ADAPTER_H_
