#include "sparse_bitset.h"
#define DIGITOF(x,w) (((x)>>(w))&1)
#define GETDIGIT(w) ((static_cast<bitset_t>(1))<<(w))
#define lowbit(x) ((x)&-(x))
using std::vector;
const int width=64;
const bitset_t full=GETDIGIT(width-1)|(GETDIGIT(width-1)-1);
Segment::Segment(int _id,bitset_t _v): id(_id), value(_v) {}

SparseBitset::SparseBitset(vector<int> list1)
{
    for(int i:list1)
    {
        if(seq.size()==0 || seq[seq.size()-1].id<i/width)
        {
            seq.emplace_back(i/width,GETDIGIT(i%width));
        } else seq[seq.size()-1].value|=GETDIGIT(i%width);
    }
}

void SparseBitset::take_or(const SparseBitset &y)
{
    vector<Segment> res;
    int p1=0,p2=0;
    const vector<Segment> &s1=seq, &s2=y.seq;
    while(p1<s1.size() && p2<s2.size())
    {
        if(s1[p1].id == s2[p2].id)
        {
            res.emplace_back(s1[p1].id, s1[p1].value | s2[p2].value);
            ++p1;
            ++p2;
        } else if(s1[p1].id < s2[p2].id)
        {
            res.push_back(s1[p1]);
            ++p1;
        } else
        {
            res.push_back(s2[p2]);
            ++p2;
        }
    }
    while(p1<s1.size())
    {
        res.push_back(s1[p1]);
        ++p1;
    }
    while(p2<s2.size())
    {
        res.push_back(s2[p2]);
        ++p2;
    }
    seq.swap(res);
}
void SparseBitset::take_and(const SparseBitset &y)
{
    vector<Segment> res;
    int p1=0,p2=0;
    const vector<Segment> &s1=seq, &s2=y.seq;
    while(p1<s1.size() && p2<s2.size())
    {
        if(s1[p1].id == s2[p2].id)
        {
            res.emplace_back(s1[p1].id, s1[p1].value & s2[p2].value);
            ++p1;
            ++p2;
        } else if(s1[p1].id < s2[p2].id) ++p1;
        else ++p2;
    }
    seq.swap(res);
}

SparseBitset SparseBitset::all1(int size)
{
    SparseBitset res;
    for(int i=0;i<(size-1)/width;++i) res.seq.emplace_back(i,full);
    bitset_t last=0;
    for(int i=0;i<=(size-1)%width;++i) last|=GETDIGIT(i);
    res.seq.emplace_back((size-1)/width,last);
    return res;
}

void SparseBitset::push_back(int x)
{
    if(seq.size()==0 || seq[seq.size()-1].id<x/width)
    {
        seq.emplace_back(x/width,GETDIGIT(x%width));
    } else seq[seq.size()-1].value|=GETDIGIT(x%width);
}

constexpr int P=10007;
class Bitmap
{
public:
    int hashmap[P];
    Bitmap()
    {
        for(int i=0,pow=1;i<64;++i,pow=(pow*2)%P) hashmap[pow]=i;
    }
} tmp;

vector<int> SparseBitset::get_list1()
{
    vector<int> ret;
    for(Segment &i:seq)
    {
        bitset_t t=i.value;
        while(t)
        {
            ret.push_back(tmp.hashmap[lowbit(t)%P]+i.id*width);
            t^=lowbit(t);
        }
    }
    return ret;
}