#include <iostream>
#include "AVLTree.h"
using namespace std;

int main() {
    AVLTree tree;

    // Insert test cases
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(5);

    // Check tree size
    cout << "Size of tree: " << tree.Size() << endl;

    // Find depth + height of a node
    cout << "Find 20: " << tree.Find(20) << endl;

    // Ancestor test case
    tree.Ancestor(15);

    // Average test case (min + max value in subtree)
    tree.Average(10);

    // Tree height
    cout << "Tree Height: " << tree.Height() << endl;

    // Check if tree is empty
    cout << "Is tree empty? " << tree.Empty() << endl;

    tree.Rank(20);

    // Remove a node
//    cout << "Erase 20: ";
//    tree.Erase(20);
//
//    cout << "Size after removing 20: " << tree.Size() << endl;

    tree.PrintTree();
    return 0;
}