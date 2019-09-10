#pragma once
class Element
{
private:
    int _dim;
    int *value;
public:
    Element(int m_dim): _dim(m_dim), value(new int[m_dim]) {}
    Element(const Element &x) {*this = x;}
    Element(Element &&x);
    Element& operator=(const Element &);
    ~Element() {delete[] value;}
    int dim() const {return _dim;}
    int& operator[](int index) {return value[index];}
    const int& operator[](int index) const {return value[index];}
};

int dist(const Element&,const Element&);

/* Developed by lkmcfj & LovEveRv, 2019. All rights reserved. */
