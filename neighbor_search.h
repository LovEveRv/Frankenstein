#pragma once
#include <vector>
#include <utility>
#include "point.h"
#include "sparse_bitset.h"
template<int range>//space: [0,range)^dim
class NeighborSearcher
{
    int d, cnt;
    int _dim;
    SparseBitset **filter;
public:
    NeighborSearcher(int m_dim, int m_d);
    ~NeighborSearcher();
    NeighborSearcher(const NeighborSearcher&) = delete;
    NeighborSearcher(NeighborSearcher&&) = delete;
    NeighborSearcher& operator=(const NeighborSearcher&) = delete;
    NeighborSearcher& operator=(NeighborSearcher&&) = delete;
    void add_point(const Element &x);
    std::vector<int> search_neighbor(const Element &center);
};

/* Developed by lkmcfj, 2019. All rights reserved. */