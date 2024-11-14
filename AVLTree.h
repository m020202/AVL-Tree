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
        node *find_node = Search(root, key);
        if (find_node == NULL) return 0;

        int depth = GetDepth(find_node);
        int height = GetHeight(find_node);

        return depth + height;
    }

    node *Search(node *cur_node, int key) {
        if (cur_node == NULL) return NULL;

        if (cur_node ->key == key)
            return cur_node;
        else if (cur_node->key < key) {
            return Search(cur_node->right, key);
        }
        else
            return Search(cur_node->left, key);
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
    node* Balance(node* n) {
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

    int Insert(int x) {
        node *new_node = new node(x); // 추가할 새로운 노드
        size++;
        if (root == NULL) {
            root = new_node;
            return 0;
        }

        node* cur_node = root;
        node* par_node = NULL;

        while (cur_node != NULL) {
            par_node = cur_node;
            if (cur_node->key < x) {
                cur_node = cur_node->right;
            }
            else {
                cur_node = cur_node->left;
            }
        }

        new_node->parent = par_node;
        if (par_node->key < x) {
            par_node->right = new_node;
        }
        else {
            par_node->left = new_node;
        }

        // 균형 유지
        node* tmp = new_node;
        while (tmp != NULL) {
            tmp = Balance(tmp);
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
        return size;
    }

    int Height() {
        // Balancing 시 편의상 leaf의 height을 1로 설정했기 때문에 -1 해주기
        return root ? root->height-1 : -1;
    }

    void Ancestor(int x) {
        int depth_height_sum = Find(x);

        int key_sum = 0;
        node *cur_node = Search(root, x)->parent;
        while (cur_node != NULL) {
            key_sum += cur_node->key;
            cur_node = cur_node->parent;
        }

        cout << depth_height_sum << " " << key_sum << endl;
    }

    void Average(int x) {
        node *cur_node = Search(root, x);

        int min_val = cur_node->key;
        int max_val = cur_node->key;

        // 내부 함수: DFS 로 부분 트리 순회 구현
        function<void(node*)> dfs = [&] (node* cur) {
            if (cur == NULL) return;

            min_val = min(min_val, cur->key);
            max_val = max(max_val, cur->key);

            dfs(cur->left);
            dfs(cur->right);
        };
        // 현재 노드부터 DFS 시작
        dfs(cur_node);
        cout << (min_val + max_val) / 2.0 << endl;
    }

    void Rank(int x) {
        node *cur_node = Search(root, x);
        if (cur_node == nullptr) {
            cout << 0 << endl;
            return;
        }

        int depth_height_sum = Find(x);
        function<int(node*)> GetSize = [&] (node* n) {
            if (n == NULL) return 0;
            return 1 + GetSize(n->left) + GetSize(n->right);
        };

        int rank = GetSize(cur_node->left) + 1;
        while (cur_node->parent != nullptr) {
            if (cur_node == cur_node->parent->left) {
                cur_node = cur_node->parent;
                continue;
            }
            rank += (GetSize(cur_node->parent->left) + 1);
            cur_node = cur_node->parent;
        }

        cout << depth_height_sum << " " << rank << endl;
    }

    void Erase(int key) {
        node* del_node = Search(root, key);
        if (del_node == nullptr) {
            cout << 0 << endl;
            return;
        }
        size--;
        cout << Find(key) << endl;

        node* par_node = del_node->parent;
        node* child_node;

        if (del_node->left == nullptr && del_node->right == nullptr) {
            child_node = nullptr;
        }
        else if (del_node->left == nullptr && del_node->right != nullptr) {
            child_node = del_node->right;
        }
        else if (del_node->left != nullptr && del_node->right == nullptr) {
            child_node = del_node->left;
        }
        else {
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
            root = child_node;
            if (root != nullptr) root->parent = nullptr;
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
        while (root->parent != NULL) {
            root = root->parent;
        }
    }

    // 값들을 트리 형태로 출력 하는 함수 (임시로 구현 해놓음)
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
    int size;
};