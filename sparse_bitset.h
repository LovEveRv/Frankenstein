#pragma once
#include <vector>
#include <queue>
#include <cstdint>
#include <cstddef>
typedef uint64_t bitset_t;
extern const int width;
extern const bitset_t full;
struct Segment
{
    int id;
    bitset_t value;
    Segment(int _id,bitset_t _v);
};
struct SparseBitset
{
    std::vector<Segment> seq;
    SparseBitset() = default;
    SparseBitset(std::vector<int> list1);//must be in increasing order
    void take_or(const SparseBitset &y);
    void take_and(const SparseBitset &y);
    void push_back(int x);
    std::vector<int> get_list1();
    static SparseBitset all1(int size);
};

/* Developed by lkmcfj, 2019. All rights reserved. */
