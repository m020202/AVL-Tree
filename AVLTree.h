#include <iostream>
#include <memory>
#include <cmath>
using namespace std;

struct node {
    int key;
    node* parent;
    node* left;
    node* right;
    int height;

    node(int key) {
        this->key = key;
        parent = left = right = NULL;
        height = 1;
    }
};

class AVLTree {
public:
    AVLTree() {
        root = NULL;
    }

    int GetDepth(node* n) {
        int depth = 0;
        while (n->parent != NULL) {
            n = n->parent;
            depth++;
        }

        return depth;
    }

    int GetHeight(node* n) {
        return n ? n->height : 0;
    }

    int Find(int key) {
        node *findNode = search(root, key);
        if (findNode == NULL) return 0;

        int depth = GetDepth(findNode);
        int height = GetHeight(findNode);

        return depth + height;
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

    void UpdateHeight(node* n) {
        if (n) {
            n->height = 1 + max(GetHeight(n->left), GetHeight(n->right));
        }
    }

    int GetBalance(node* n) {
        return n ? GetHeight(n->left) - GetHeight(n->right) : 0;
    }

    node* RotateRight(node* y) {
        node* x = y->left;
        node* T2 = x->right;

        x->right = y;
        y->left = T2;

        if (T2) T2->parent = y;
        x->parent = y->parent;
        y->parent = x;

        UpdateHeight(y);
        UpdateHeight(x);
    }

    node* RotateLeft(node* x) {
        node* y = x->right;
        node* T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2) T2->parent = x;
        y->parent = x->parent;
        x->parent = y;

        UpdateHeight(x);
        UpdateHeight(y);

        return y;
    }

    node* balance(node* n) {
        UpdateHeight(n);
        int balance_factor = GetBalance(n);

        // LL Case
        if (balance_factor > 1 && GetBalance(n->left) >= 0)
            return RotateRight(n);

        // LR Case
        if (balance_factor > 1 && GetBalance(n->left) < 0)
            return RotateRight(n);

        // RR Case
        if (balance_factor < -1 && GetBalance(n->right) <= 0) {
            return RotateLeft(n);
        }

        // RL Case
        if (balance_factor < -1 && GetBalance(n->right) > 0) {
            n->right = RotateRight(n->right);
            return RotateLeft(n);
        }

        return n;
    }

    int insert(int x) {
        node *newNode = new node(x); // 추가할 새로운 노드

        if (root == NULL) {
            root = newNode;
            return 0;
        }

        node* curNode = root;
        node* parNode = NULL;

        while (curNode != NULL) {
            parNode = curNode;
            if (curNode->key < x) {
                curNode = curNode->right;
            }
            else {
                curNode = curNode->left;
            }
        }

        newNode->parent = parNode;
        if (parNode->key < x) {
            parNode->right = newNode;
        }
        else {
            parNode->left = newNode;
        }

        // 균형 유지
        while (parNode != NULL) {
            UpdateHeight(parNode);
            parNode = balance(parNode);
            parNode = parNode->parent;
        }

        // 루트 갱신
        while (root->parent != NULL) {
            root = root->parent;
        }

        return Find(x);
    }

    int Empty() {
        return root ? 1 : 0;
    }

    int Size(node* n) {
        if (n == NULL) return 0;
        return 1 + Size(n->left) + Size(n->right);
    }

    int Height() {
        return root ? GetHeight(root) : -1;
    }

    void Ancestor(int x) {
        int depth_height_sum = Find(x);

        int key_sum = 0;
        node *curNode = search(root, x)->parent;
        while (curNode != NULL) {
            key_sum += curNode->key;
            curNode = curNode->parent;
        }

        cout << depth_height_sum << " " << key_sum << endl;
    }

    void Average(int x) {
        node *curNode = search(root, x);

        int minVal = curNode->key;
        int maxVal = curNode->key;

        // 내부 함수: DFS 로 부분 트리 순회 구현
        function<void(node*)> dfs = [&] (node* cur) {
            if (cur == NULL) return;

            minVal = min(minVal, cur->key);
            maxVal = max(maxVal, cur->key);

            dfs(cur->left);
            dfs(cur->right);
        };
        // 현재 노드부터 DFS 시작
        dfs(curNode);

        cout << (minVal + maxVal) / 2.0 << endl;
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

//class AVLTree {
//public:
//    AVLTree() : root_(nullptr) {}
//
//    void Insert(int key) {
//        root_ = insert(move(root_), key);
//    }
//
//    bool Find(int key, int& depth, int& height_sum) {
//        return find(root_.get(), key, depth, height_sum);
//    }
//
//    bool IsEmpty() {
//        return is_empty();
//    }
//
//    int get_size() {
//        return size(root_.get());
//    }
//
//    int get_height() {
//        return is_empty() ? -1 : get_tree_height();
//    }
//
//    int get_ancestor(int key) {
//        int ancestor_sum = 0;
//        int depth = ancestor(root_.get(), key, ancestor_sum);
//        return depth >= 0 ? ancestor_sum : -1;
//    }
//
//    double get_average(int key) {
//        int min, max;
//        min_max(root_.get(), min, max);
//        return (min + max) / 2.0;
//    }
//
//private:
//    struct Node {
//        int key_;
//        int height_;
//        int size_;
//        unique_ptr<Node> left_, right_;
//
//        Node(int key) : key_(key), height_(1), size_(1), left_(nullptr), right_(nullptr) {}
//    };
//
//    unique_ptr<Node> root_;
//
//    int height(Node* node) {
//        return node ? node -> height_ : 0;
//    }
//
//    int size(Node* node) {
//        return node ? node->size_ : 0;
//    }
//
//    void UpdateNode(Node* node) {
//        if (node) {
//            node->height_ = 1 + max(height(node->left_.get()), height(node->right_.get()));
//            node->size_ = 1 + size(node->left_.get()) + size(node->right_.get());
//        }
//    }
//
//    unique_ptr<Node> RotateRight(unique_ptr<Node> y) {
//        auto x = move(y->left_);
//        y->left_ = move(x->right_);
//        x->right_ = move(y);
//        UpdateNode(x->right_.get());
//        UpdateNode(x.get());
//        return x;
//    }
//
//    unique_ptr<Node> RotateLeft(unique_ptr<Node> x) {
//        auto y = move(x->right_);
//        x->right_ = move(y->left_);
//        y->left_ = move(x);
//        UpdateNode(y->left_.get());
//        UpdateNode(y.get());
//        return y;
//    }
//
//    int balance(Node* node) {
//        return node ? height(node->left_.get()) - height(node->right_.get()) : 0;
//    }
//
//    unique_ptr<Node> balancing(unique_ptr<Node> node) {
//        if (!node) return nullptr;
//
//        UpdateNode(node.get());
//        int tmp_balance = balance(node.get());
//
//        if (tmp_balance > 1) {
//            if (balance(node->left_.get()) < 0)
//                node->left_ = RotateLeft(move(node->left_));
//            return RotateRight(move(node));
//        }
//
//        if (tmp_balance < -1) {
//            if (balance(node->right_.get()) > 0)
//                node->right_ = RotateRight(move(node->right_));
//            return RotateLeft(move(node));
//        }
//
//        return node;
//    }
//
//    unique_ptr<Node> insert(unique_ptr<Node> node, int key) {
//        if (!node) return make_unique<Node>(key);
//
//        if (key < node->key_)
//            node->left_ = insert(move(node->left_), key);
//        else if (key > node->key_)
//            node->right_ = insert(move(node->right_), key);
//        else
//            return node;
//
//        return balancing(move(node));
//    }
//
//    bool find(Node* node, int key, int& depth, int& height_sum) {
//        depth = 0;
//        height_sum = 0;
//        Node* current = node;
//        while (current) {
//            if (key == current->key_) {
//                height_sum = height(current) + depth;
//                return true;
//            }
//            depth++;
//            if (key < current->key_)
//                current = current->left_.get();
//            else
//                current = current->right_.get();
//        }
//        return false;
//    }
//
//    bool is_empty() const {
//        return root_ == nullptr;
//    }
//
//    // Calculate tree height
//    int get_tree_height() {
//        return height(root_.get());
//    }
//
//    int ancestor(Node* node, int key, int& ancestor_sum, int depth = 0) {
//        if (!node) return -1;
//
//        if (node->key_ == key) {
//            ancestor_sum += node->key_;
//            return depth;
//        }
//        else if (key < node->key_) {
//            ancestor_sum += node->key_;
//            return ancestor(node->left_.get(), key, ancestor_sum, depth + 1);
//        }
//        else {
//            ancestor_sum += node->key_;
//            return ancestor(node->right_.get(), key, ancestor_sum, depth + 1);
//        }
//    }
//
//    void min_max(Node* node, int& min, int& max) {
//        if (!node) return;
//        Node* tmp = node;
//        while (tmp -> left_)
//            tmp = tmp->left_.get();
//        min = tmp->key_;
//        tmp = node;
//        while (tmp -> right_)
//            tmp = tmp->right_.get();
//        max = tmp->key_;
//    }
//};
