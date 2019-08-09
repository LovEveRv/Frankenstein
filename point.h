#pragma once
template<size_t dim>
struct Element
{
    int value[dim];
    Element() = default;
    Element(int m_v[dim]);
    int& operator[](int index);
    const int& operator[](int index) const;
};

template<size_t dim>
int dist(const Element<dim>&,const Element<dim>&);

/* Developed by lkmcfj, 2019. All rights reserved. */