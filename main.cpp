#include <iostream>
#include "AVLTree.h"
using namespace std;

int main() {
    AVLTree tree;
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(5);

    int depth, height_sum;
    if (tree.Find(20, depth, height_sum)) {
        cout << "Find 20: depth + height = " << depth + height_sum << endl;
    }
    else {
        cout << "20 not found." << endl;
    }

    cout << "Tree Height: " << tree.get_height() << "\n";
    cout << "Tree Size: " << tree.get_size() << "\n";
    cout << "Is Tree Empty: " << tree.IsEmpty() << "\n";
    cout << "Ancestor Sum for 20: " << tree.get_ancestor(20) << "\n";
    cout << "Average Min/Max: " << tree.get_average(20) << "\n";

    return 0;
}