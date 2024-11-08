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

    // 왼쪽 자식과 오른쪽 자식 height 차이 확인 (height balance property 만족하는지)
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

        return x;
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

    // restructuring
    node* balance(node* n) {
        UpdateHeight(n);
        int balance_factor = GetBalance(n);

        // LL Case
        if (balance_factor > 1 && GetBalance(n->left) >= 0)
            return RotateRight(n);

        // LR Case
        if (balance_factor > 1 && GetBalance(n->left) < 0) {
            n->left = RotateLeft(n->left);
            return RotateRight(n);
        }

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
        node* tmp = newNode;
        while (tmp != NULL) {
            tmp = balance(tmp);
            tmp = tmp->parent;
        }

        // 루트 갱신
        while (root->parent != NULL) {
            root = root->parent;
        }

        return Find(x);
    }

    int Empty() {
        return root ? 0 : 1;
    }

    int Size() {
        // 재귀로 사이즈 구하는 내부 함수 구현
        function<int(node*)> GetSize = [&] (node* n) {
            if (n == NULL) return 0;
            return 1 + GetSize(n->left) + GetSize(n->right);
        };

        return GetSize(root);
    }

    int Height() {
        return root ? root->height : -1;
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

    void Rank(int x) {
        node *curNode = search(root, x);
        if (curNode == nullptr) {
            cout << 0 << endl;
            return;
        }

        int depth_height_sum = Find(x);
        function<int(node*)> GetSize = [&] (node* n) {
            if (n == NULL) return 0;
            return 1 + GetSize(n->left) + GetSize(n->right);
        };

        int rank = GetSize(curNode->left) + 1;
        while (curNode->parent != nullptr) {
            if (curNode == curNode->parent->left) {
                curNode = curNode->parent;
                continue;
            }
            rank += (GetSize(curNode->parent->left) + 1);
            curNode = curNode->parent;
        }

        cout << depth_height_sum << " " << rank << endl;
    }

    void Erase(int key) {
        node* delNode = search(root, key);
        if (delNode == nullptr) {
            cout << 0 << endl;
            return;
        }

        cout << Find(key) << endl;

        node* parNode = delNode->parent;
        node* childNode;

        if (delNode->left == nullptr && delNode->right == nullptr) {
            childNode = nullptr;
        }
        else if (delNode->left == nullptr && delNode->right != nullptr) {
            childNode = delNode->right;
        }
        else if (delNode->left != nullptr && delNode->right == nullptr) {
            childNode = delNode->left;
        }
        else {
            childNode = delNode->right;
            while (childNode->left != nullptr) {
                childNode = childNode->left;
            }
            delNode->key = childNode->key;
            delNode = childNode;
            parNode = delNode->parent;
            childNode = delNode->right;
        }

        if (parNode == nullptr) {
            root = childNode;
            if (root != nullptr) root->parent = nullptr;
        } else if (delNode == parNode->left) {
            parNode->left = childNode;
            if (childNode != nullptr) childNode->parent = parNode;
        } else {
            parNode->right = childNode;
            if (childNode != nullptr) childNode->parent = parNode;
        }

        delete delNode;

        // 삭제 후 균형 재조정
        node* cur = parNode;
        while (cur != nullptr) {
            UpdateHeight(cur);
            cur = balance(cur);
            cur = cur->parent;
        }
    }

    // 트리를 트리 형태로 출력 하는 함수 (임시로 구현 해놓음)
    void PrintTree() {
        if (root == NULL) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        // printTreeHelper를 PrintTree의 내부 함수로 구현
        function<void(node*, int)>printTreeHelper = [&] (node* n, int space) {
            if (n == NULL) return;

            // 오른쪽 자식부터 출력 (역순으로 출력하므로 오른쪽부터 출력)
            space += 10;  // 각 레벨을 띄울 만큼 공백 증가

            // 오른쪽 자식 출력
            printTreeHelper(n->right, space);

            // 현재 노드 출력 (높이와 공백에 맞게 출력)
            std::cout << std::endl;
            for (int i = 10; i < space; i++) {
                std::cout << " ";
            }
            std::cout << n->key << std::endl;

            // 왼쪽 자식 출력
            printTreeHelper(n->left, space);
        };

        // 루트 노드부터 시작
        printTreeHelper(root, 0);
    }

private:
    node* root;
};