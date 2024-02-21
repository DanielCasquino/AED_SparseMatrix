#include <iostream>
#include "sparse_matrix.h"

int main()
{
    auto sm = new listlist_sparse_matrix();
    sm->insert(0, 0, 5);
    sm->insert(1, 0, 2);
    sm->insert(1, 1, 3);
    sm->insert(2, 0, 8);
    sm->insert(3, 0, 5);
    sm->insert(2, 1, 2);
    sm->insert(6, 5, 3);
    sm->traverse();
    sm->remove(3, 0);
    sm->remove(0, 0);
    std::cout << std::endl
              << std::endl;
    sm->traverse();
    return 0;
}
