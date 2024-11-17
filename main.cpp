#include <iostream>
#include "header/avl_tree_adaptee.h"
#include "header/avl_tree.h"
#include "header/avl_tree_adapter.h"
using namespace std;

int main() {
    AVLTreeAdaptee adaptee;
    AVLTree* tree = new AVLTreeAdapter(adaptee);

    // Insert test cases
    cout << "Insert(10): ";
    tree->Insert(10);
    cout << "Insert(20): ";
    tree->Insert(20);
    cout << "Insert(30): ";
    tree->Insert(30);
    cout << "Insert(15): ";
    tree->Insert(15);
    cout << "Insert(5): ";
    tree->Insert(5);

//    // 현재 트리 출력
//    cout << "=========현재 트리=========" << endl;
//    tree->PrintTree();
//    cout << "=========================" << endl;

    // Size
    cout << "Size of tree: ";
    tree->Size();

    // Find depth + height of a node
    cout << "Find 20: ";
    tree->Find(20);

    // Ancestor
    cout << "Ancestor(15): ";
    tree->Ancestor(15);

    // Average test case (min + max value in subtree)
    cout << "Average(10): ";
    tree->Average(10);

    // Tree height
    cout << "Tree Height: ";
    tree->Height();

    // Check if tree is empty
    cout << "Is tree empty? ";
    tree->Empty();

    // Rank
    cout << "Rank(30): ";
    tree->Rank(30);

    // Remove a node
    cout << "Erase 20: ";
    tree->Erase(20);

    cout << "Size after removing 20: ";
    tree->Size();
//
//    cout << "=========현재 트리=========" << endl;
//    tree->PrintTree();
//    cout << "=========================" << endl;

    return 0;
}