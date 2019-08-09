#include "neighbor_search.h"
#include <cassert>
#define bid(x) ((x)/S)
#define R(x) (bid(x)*S+S-1)
#define L(x) (bid(x)*S)
using std::vector;
using std::pair;
template<size_t dim, int range>
void NeighborSearcher<dim,range>::add_point(const Element<dim> &x)
{
    pts.push_back(x);
    int cur=pts.size()-1;
    for(size_t i=0;i<dim;++i)
    {
        filter[i][x[i]].push_back(cur);
        block[i][x[i]/S].push_back(cur);
    }
}
template<size_t dim, int range>
SparseBitset NeighborSearcher<dim,range>::query_dim(size_t d,int l,int r)
{
    SparseBitset res;
    if(bid(l)==bid(r))
    {
        for(int i=l;i<=r;++i) res.take_or(filter[d][i]);
    } else
    {
        if(l!=L(l)) for(int i=l;i<=R(l);++i) res.take_or(filter[d][i]);
            else res.take_or(block[d][bid(l)]);
        if(r!=R(r)) for(int i=L(r);i<=r;++i) res.take_or(filter[d][i]);
            else res.take_or(block[d][bid(r)]);
        for(int i=bid(l)+1;i<bid(r);++i) res.take_or(block[d][i]);
    }
    return res;
}
template<size_t dim, int range>
vector<int> NeighborSearcher<dim,range>::query(const vector<pair<int,int>> &qrange)
{
    assert(qrange.size()==dim);
    SparseBitset res=query_dim(0,qrange[0].first,qrange[0].second);
    for(size_t i=1;i<dim;++i)
        res.take_and(query_dim(i,qrange[i].first,qrange[i].second));
    return res.get_list1();
}
template<size_t dim, int range>
vector<int> NeighborSearcher<dim,range>::search_neighbor(const Element<dim> &x,int d)
{
    vector<pair<int,int>> qrange;
    for(int i=0;i<dim;++i) qrange.emplace_back(std::max(x[i]-d,0),std::min(x[i]+d,range-1));
    return query(qrange);
}

template class NeighborSearcher<3,256>;
template class NeighborSearcher<12,256>;
template class NeighborSearcher<48,256>;