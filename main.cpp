#include <iostream>
#include "avl_tree.h"
#include "set.h"
#include "set_adapter.h"
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t,q, num;
    cin >> t;
    while(t--) {
        AVLTree avlTree;
        Set* set = new SetAdapter(avlTree);

        cin >> q;
        for (int i = 0; i < q; ++i) {
            string input;
            cin >> input;

            if (input == "Find") {
                cin >> num;
                set->Find(num);
            }
            else if (input == "Insert") {
                cin >> num;
                set->Insert(num);
              //  set->PrintTree();
            }
            else if (input == "Empty") {
                set->Empty();
            }
            else if (input == "Size") {
                set->Size();
            }
            else if (input == "Height") {
                set->Height();
            }
            else if (input == "Ancestor") {
                cin >> num;
                set->Ancestor(num);
            }
            else if (input == "Average") {
                cin >> num;
                set->Average(num);
            }
            else if (input == "Rank") {
                cin >> num;
                set->Rank(num);
            }
            else if (input == "Erase") {
                cin >> num;
                set->Erase(num);
            }
        }
    }
    return 0;
}