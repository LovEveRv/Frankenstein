#include <cmath>
#include <algorithm>
#include "point.h"
template<size_t dim>
Element<dim>::Element(int m_v[dim])
{
    for(int i=0;i<dim;++i) value[i]=m_v[i];
}
template<size_t dim>
int& Element<dim>::operator[](int index)
{
    return value[index];
}
template<size_t dim>
const int& Element<dim>::operator[](int index) const
{
    return value[index];
}
template<size_t dim>
int dist(const Element<dim> &A,const Element<dim> &B)
{
    int ret=0;
    for(int i=0;i<dim;++i) ret=std::max(ret,std::abs(A[i]-B[i]));
    return ret;
}

template struct Element<3>;
template struct Element<12>;
template struct Element<48>;

template int dist<3>(const Element<3>&,const Element<3>&);
template int dist<12>(const Element<12>&,const Element<12>&);
template int dist<48>(const Element<48>&,const Element<48>&);


