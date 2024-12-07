#ifndef ALGORITHMS_DATA_STRUCTURES_DSU_H
#define ALGORITHMS_DATA_STRUCTURES_DSU_H

#include "../../algorithms_shared.h"

#include <cassert>
#include <numeric>
#include <vector>

namespace algorithms::data_structures {

/*
Disjoint set union data structure.

It stores a partition of a set into disjoint subsets.
It provides operations for adding new sets, merging sets (replacing them by their union),
and finding a representative member of a set. It search for a representative member in O(alpha(n)), 
insert a new element in O(1) and has space complexity O(n) where n is a total number of elements 
in set and alpha(n) is the extremely slow-growing inverse Ackermann function.

For more inforamtion see: https://en.wikipedia.org/wiki/Disjoint-set_data_structure.
*/
ALGORITHMS_EXPORT class DSU {
private:
    std::vector<size_t> p_, sz_;
    size_t comp_cnt_, n_;

public:
    DSU(size_t n = 0);
    DSU(const DSU& other);
    DSU& operator=(const DSU& other);

    // Insert new element in set
    void insert();

    // Find a representative member of a set that contains element v
    size_t representative(size_t v);

    // Checks whether the components for vertices v and u match
    bool isSame(size_t v, size_t u);

    // Return size of set that contains element v
    size_t subsetSize(size_t v);

    // Return number of subsets in partition
    size_t components();

    // Return whole set size
    size_t size();

    // Merge two sets containing v and u.
    // Return false if u and v are in the same set, true othervise
    bool merge(size_t v, size_t u);
};

} // algorithms::data_structures

#endif // ALGORITHMS_DATA_STRUCTURES_DSU_H