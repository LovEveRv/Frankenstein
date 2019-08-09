#pragma once
#include <vector>
#include <utility>
#include "point.h"
#include "sparse_bitset.h"
constexpr int S=5;
template<size_t dim,int range>//space: [0,range)^dim
class NeighborSearcher
{
    std::vector<Element<dim>> pts;
    SparseBitset filter[dim][range];
    SparseBitset block[dim][range/S+1];
    SparseBitset query_dim(size_t d,int l,int r);
public:
    void add_point(const Element<dim> &x);
    std::vector<int> query(const std::vector<std::pair<int,int>> &qrange);
    std::vector<int> search_neighbor(const Element<dim> &center, int d);
};

/* Developed by lkmcfj, 2019. All rights reserved. */