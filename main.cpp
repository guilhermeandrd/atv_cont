#include <iostream>
#include "Tree.hpp"

using namespace std;

int main() {
    Tree avl;

    avl.insert(10);

    avl.insert(8);

    avl.insert(9);

    avl.insert(6);

    avl.show();

    return 0;
}