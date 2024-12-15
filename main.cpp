#include <iostream>
#include "header/avl_tree.h"
#include "header/set.h"
#include "header/set_adapter.h"
using namespace std;

int main() {
    AVLTree adaptee;
    Set* set = new SetAdapter(adaptee);

    // Insert test cases
    cout << "Insert(10): ";
    set->Insert(10);
    cout << "Insert(20): ";
    set->Insert(20);
    cout << "Insert(30): ";
    set->Insert(30);
    cout << "Insert(15): ";
    set->Insert(15);
    cout << "Insert(5): ";
    set->Insert(5);

//    // 현재 트리 출력
//    cout << "=========현재 트리=========" << endl;
//    tree->PrintTree();
//    cout << "=========================" << endl;

    // Size
    cout << "Size of tree: ";
    set->Size();

    // Find depth + height of a node
    cout << "Find 20: ";
    set->Find(20);

    // Ancestor
    cout << "Ancestor(15): ";
    set->Ancestor(15);

    // Average test case (min + max value in subtree)
    cout << "Average(10): ";
    set->Average(10);

    // Tree height
    cout << "Tree Height: ";
    set->Height();

    // Check if tree is empty
    cout << "Is tree empty? ";
    set->Empty();

    // Rank
    cout << "Rank(30): ";
    set->Rank(30);

    // Remove a node
    cout << "Erase 20: ";
    set->Erase(20);

    cout << "Size after removing 20: ";
    set->Size();
//
//    cout << "=========현재 트리=========" << endl;
//    tree->PrintTree();
//    cout << "=========================" << endl;

    return 0;
}