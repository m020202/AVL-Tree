#include "../header/avl_tree.h"

node::node(int key) {
    this->key = key;
    parent = left = right = nullptr;
    height = size = 1;
}

AVLTree::AVLTree() {
    root_ = nullptr;
    size_ = 0;
}

int AVLTree::GetDepth(node* n) {
    int depth = 0;
    while (n->parent != nullptr) {
        n = n->parent;
        depth++;
    }
    return depth;
}

int AVLTree::GetHeightByNode(node* n) {
    return n ? n->height : 0;
}

int AVLTree::GetSubTreeSize(node* n) {
    return n ? n->size : 0;
}

void AVLTree::UpdateSubTreeSize(node* n) {
    n->size = 1 + GetSubTreeSize(n->left) + GetSubTreeSize(n->right);
}

int AVLTree::Finding(int key) {
    node* find_node = Search(root_, key);
    if (find_node == nullptr) return 0;

    int depth = GetDepth(find_node);
    int height = GetHeightByNode(find_node);

    return depth + height;
}

node* AVLTree::Search(node* cur_node, int key) {
    if (cur_node == nullptr) return nullptr;

    if (cur_node->key == key)
        return cur_node;
    else if (cur_node->key < key) {
        return Search(cur_node->right, key);
    } else {
        return Search(cur_node->left, key);
    }
}

void AVLTree::UpdateHeight(node* n) {
    if (n) {
        n->height = 1 + max(GetHeightByNode(n->left), GetHeightByNode(n->right));
    }
}

int AVLTree::GetBalance(node* n) {
    return n ? GetHeightByNode(n->left) - GetHeightByNode(n->right) : 0;
}

node* AVLTree::RotateRight(node* y) {
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    if (T2) T2->parent = y;
    x->parent = y->parent;
    y->parent = x;

    if (x->parent) {
        if (x->parent->left == y) {
            x->parent->left = x;
        } else {
            x->parent->right = x;
        }
    }

    UpdateHeight(y);
    UpdateHeight(x);
    UpdateSubTreeSize(y);
    UpdateSubTreeSize(x);

    return x;
}

node* AVLTree::RotateLeft(node* x) {
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2) T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    if (y->parent) {  // x의 부모가 존재하는 경우
        if (y->parent->left == x) {  // y가 부모의 왼쪽 자식인 경우
            y->parent->left = y;     // 부모의 왼쪽 자식을 x로 갱신
        } else {                     // y가 부모의 오른쪽 자식인 경우
            y->parent->right = y;    // 부모의 오른쪽 자식을 x로 갱신
        }
    }

    UpdateHeight(x);
    UpdateHeight(y);
    UpdateSubTreeSize(x);
    UpdateSubTreeSize(y);

    return y;
}

node* AVLTree::Balance(node* n) {
    UpdateHeight(n);
    UpdateSubTreeSize(n);
    int balance_factor = GetBalance(n);

    if (balance_factor > 1 && GetBalance(n->left) >= 0) {
        return RotateRight(n);
    }

    if (balance_factor > 1 && GetBalance(n->left) < 0) {
        n->left = RotateLeft(n->left);
        return RotateRight(n);
    }

    if (balance_factor < -1 && GetBalance(n->right) <= 0) {
        return RotateLeft(n);
    }

    if (balance_factor < -1 && GetBalance(n->right) > 0) {
        n->right = RotateRight(n->right);
        return RotateLeft(n);
    }

    return n;
}

int AVLTree::Inserting(int x) {
    node* new_node = new node(x);
    size_++;
    if (root_ == nullptr) {
        root_ = new_node;
        return Finding(x);
    }

    node* cur_node = root_;
    node* par_node = nullptr;

    while (cur_node != nullptr) {
        par_node = cur_node;
        if (cur_node->key < x) {
            cur_node = cur_node->right;
        } else {
            cur_node = cur_node->left;
        }
    }

    new_node->parent = par_node;
    if (par_node->key < x) {
        par_node->right = new_node;
    } else {
        par_node->left = new_node;
    }

    node* tmp = new_node;
    while (tmp != nullptr) {
        tmp = Balance(tmp);
        tmp = tmp->parent;
    }

    while (root_->parent != nullptr) {
        root_ = root_->parent;
    }
    return Finding(x);
}

int AVLTree::IsEmpty() {
    return root_ ? 0 : 1;
}

int AVLTree::GetSize() {
    return size_;
}

int AVLTree::GetHeight() {
    return root_ ? root_->height : -1;
}

void AVLTree::GetAncestor(int x) {
    int depth_height_sum = Finding(x);

    int key_sum = 0;
    node* cur_node = Search(root_, x)->parent;
    while (cur_node != nullptr) {
        key_sum += cur_node->key;
        cur_node = cur_node->parent;
    }

    cout << depth_height_sum << " " << key_sum << "\n";
}

void AVLTree::GetAverage(int x) {
    node* cur_node = Search(root_, x);
    node* tmp = cur_node;
    while (tmp->left != nullptr) {
        tmp = tmp->left;
    }
    int min_val = tmp->key;

    tmp = cur_node;
    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    int max_val = tmp->key;

    cout << (min_val + max_val) / 2 << "\n";
}

void AVLTree::GetRank(int x) {
    node* cur_node = Search(root_, x);
    if (cur_node == nullptr) {
        cout << 0 << "\n";
        return;
    }

    int depth_height_sum = Finding(x);

    int rank = GetSubTreeSize(cur_node->left) + 1;
    while (cur_node->parent != nullptr) {
        if (cur_node == cur_node->parent->left) {
            cur_node = cur_node->parent;
            continue;
        }
        rank += (GetSubTreeSize(cur_node->parent->left) + 1);
        cur_node = cur_node->parent;
    }

    cout << depth_height_sum << " " << rank << "\n";
}

void AVLTree::Erasing(int key) {
    node* del_node = Search(root_, key);
    if (del_node == nullptr) {
        cout << 0 << "\n";
        return;
    }
    size_--;
    cout << Finding(key) << "\n";

    node* par_node = del_node->parent;
    node* child_node;

    if (del_node->left == nullptr && del_node->right == nullptr) {
        child_node = nullptr;
    } else if (del_node->left == nullptr && del_node->right != nullptr) {
        child_node = del_node->right;
    } else if (del_node->left != nullptr && del_node->right == nullptr) {
        child_node = del_node->left;
    } else {
        child_node = del_node->right;
        while (child_node->left != nullptr) {
            child_node = child_node->left;
        }
        del_node->key = child_node->key;
        del_node = child_node;
        par_node = del_node->parent;
        child_node = del_node->right;
    }

    if (par_node == nullptr) {
        root_ = child_node;
        if (root_ != nullptr) root_->parent = nullptr;
    } else if (del_node == par_node->left) {
        par_node->left = child_node;
        if (child_node != nullptr) child_node->parent = par_node;
    } else {
        par_node->right = child_node;
        if (child_node != nullptr) child_node->parent = par_node;
    }

    delete del_node;

    // 삭제 후 균형 재조정
    node* cur = par_node;
    while (cur != nullptr) {
        UpdateHeight(cur);
        cur = Balance(cur);
        cur = cur->parent;
    }

    // 루트 갱신
    if (root_ != NULL) {
        while (root_->parent != NULL) {
            root_ = root_->parent;
        }
    }
}