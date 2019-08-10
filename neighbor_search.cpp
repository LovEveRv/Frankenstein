#include "neighbor_search.h"
#include <cassert>
#include <algorithm>
using std::vector;
using std::pair;

template<int range>
NeighborSearcher<range>::NeighborSearcher(int m_dim, int m_d): _dim(m_dim), d(m_d), cnt(0) 
{
    filter = new SparseBitset*[_dim];
    for(int i=0;i<_dim;++i) filter[i] = new SparseBitset[range];
}
template<int range>
NeighborSearcher<range>::~NeighborSearcher()
{
    for(int i=0;i<_dim;++i) delete[] filter[i];
    delete[] filter;
}
template<int range>
void NeighborSearcher<range>::add_point(const Element &x)
{
    int cur=cnt++;
    for(size_t i=0;i<_dim;++i)
    {
        for(int j=std::max(0,x[i]-d);j<=std::min(range-1,x[i]+d);++j) filter[i][j].push_back(cur);
    }
}
template<int range>
vector<int> NeighborSearcher<range>::search_neighbor(const Element &x)
{
    SparseBitset res=filter[0][x[0]];
    for(int i=1;i<_dim;++i) res.take_and(filter[i][x[i]]);
    return res.get_list1();
}

template class NeighborSearcher<256>;
