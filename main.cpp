#include <iostream>
#include "AVLTree.h"
using namespace std;

int main() {
    AVLTree tree;

    // Insert test cases
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(30);
    tree.Insert(15);
    tree.Insert(5);

    // 현재 트리 출력
    cout << "=========현재 트리=========" << endl;
    tree.PrintTree();
    cout << "=========================" << endl;

    // Size
    cout << "Size of tree: " << tree.Size() << endl;

    // Find depth + height of a node
    cout << "Find 20: " << tree.Find(20) << endl;

    // Ancestor
    cout << "Ancestor(15): ";
    tree.Ancestor(15);

    // Average test case (min + max value in subtree)
    cout << "Average(10): ";
    tree.Average(10);

    // Tree height
    cout << "Tree Height: " << tree.Height() << endl;

    // Check if tree is empty
    cout << "Is tree empty? " << tree.Empty() << endl;

    // Rank
    cout << "Rank(20): ";
    tree.Rank(20);

    // Remove a node
    cout << "Erase 20: ";
    tree.Erase(20);

    cout << "Size after removing 20: " << tree.Size() << endl;

    cout << "=========현재 트리=========" << endl;
    tree.PrintTree();
    cout << "=========================" << endl;

    return 0;
}