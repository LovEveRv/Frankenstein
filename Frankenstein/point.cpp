#include <cmath>
#include <algorithm>
#include "point.h"

Element& Element::operator=(const Element &x)
{
    _dim = x._dim;
    value = new int[_dim];
    for(int i=0;i<_dim;i++) value[i] = x.value[i];
    return *this;
}
Element::Element(Element &&x)
{
    _dim = x._dim;
    value = x.value;
    x.value = nullptr;
}

int dist(const Element &A,const Element &B)
{
    assert(A.dim() == B.dim());
    int ret=0;
    for(int i=0;i<A.dim();++i) ret=std::max(ret,std::abs(A[i]-B[i]));
    return ret;
}