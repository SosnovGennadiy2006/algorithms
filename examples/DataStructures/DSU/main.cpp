#include <algorithms/DataStructures/DSU/DSU.h>
#include <iostream>

using namespace algorithms::data_structures;

/*
A program that checks whether a given graph is biparite or not.
It creates DSU with 2n elements {1, 2, ..., n, 1', 2', ..., n'} and for every
edge (v, u) merges components for v and u' and u and v'. If for some vertices v and v'
their components are equal, then the graph is biparite, otherwise not.
*/

int main() {
    size_t n, m;
    std::cout << "n = ";
    std::cin >> n;
    std::cout << "m = ";
    std::cin >> m;
    DSU dsu(2 * n);
    std::cout << "Input all edges:\n";
    for (size_t i = 0, u, v; i < m; ++i) {
        std::cin >> u >> v; --u; --v;
        dsu.merge(v, u + n);
        dsu.merge(u, v + n);
    }
    bool is_biparite = true;
    for (size_t i = 0; i < n; ++i) {
        is_biparite &= !dsu.isSame(i, i + n);
    }
    if (is_biparite) {
        std::cout << "This graph is bipartite!" << std::endl;
    } else {
        std::cout << "This graph is not biparite!" << std::endl;
    }
    return 0;
}