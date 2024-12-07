#include <algorithms/DataStructures/DSU/DSU.h>

namespace algorithms::data_structures {

DSU::DSU(size_t n) : p_(n), sz_(n, 1), comp_cnt_(n), n_(n) {
    std::iota(p_.begin(), p_.end(), 0);
}

DSU::DSU(const DSU& other) : p_(other.p_), sz_(other.sz_), comp_cnt_(other.comp_cnt_), n_(other.n_) {}

DSU& DSU::operator=(const DSU& other) {
    p_ = other.p_;
    sz_ = other.sz_;
    comp_cnt_ = other.comp_cnt_;
    n_ = other.comp_cnt_;
    return *this;
}

void DSU::insert() {
    p_.push_back(n_++);
    sz_.push_back(1);
    comp_cnt_++;
}

size_t DSU::representative(size_t v) {
    assert(v < n_);
    return (v == p_[v] ? v : p_[v] = representative(p_[v]));
}

bool DSU::isSame(size_t v, size_t u) {
    assert(v < n_ && u < n_);
    return representative(v) == representative(u);
}

size_t DSU::subsetSize(size_t v) {
    return sz_[representative(v)];
}

size_t DSU::components() {
    return comp_cnt_;
}

size_t DSU::size() {
    return n_;
}

bool DSU::merge(size_t v, size_t u) {
    if ((v = representative(v)) == (u = representative(u))) {
        return false;
    }
    if (sz_[v] < sz_[u]) {
        std::swap(v, u);
    }
    p_[u] = p_[v];
    sz_[v] += sz_[u];
    comp_cnt_--;
    return true;
}

} // namespace algorithms::data_structures