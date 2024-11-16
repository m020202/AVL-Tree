#include <iostream>
#include "AVLTree.h"
using namespace std;

int main() {
    AVLTree tree;

    // Insert test cases
    tree.Inserting(10);
    tree.Inserting(20);
    tree.Inserting(30);
    tree.Inserting(15);
    tree.Inserting(5);

    // 현재 트리 출력
    cout << "=========현재 트리=========" << endl;
    tree.PrintTree();
    cout << "=========================" << endl;

    // Size
    cout << "Size of tree: " << tree.GetSize() << endl;

    // Find depth + height of a node
    cout << "Find 20: " << tree.Finding(20) << endl;

    // Ancestor
    cout << "Ancestor(15): ";
    tree.GetAncestor(15);

    // Average test case (min + max value in subtree)
    cout << "Average(10): ";
    tree.GetAverage(10);

    // Tree height
    cout << "Tree Height: " << tree.GetHeight() << endl;

    // Check if tree is empty
    cout << "Is tree empty? " << tree.IsEmpty() << endl;

    // Rank
    cout << "Rank(20): ";
    tree.GetRank(20);

    // Remove a node
    cout << "Erase 20: ";
    tree.Erasing(20);

    cout << "Size after removing 20: " << tree.GetSize() << endl;

    cout << "=========현재 트리=========" << endl;
    tree.PrintTree();
    cout << "=========================" << endl;

    return 0;
}