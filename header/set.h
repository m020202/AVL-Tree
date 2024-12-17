#ifndef OSAP_HEADER_AVLTREE_H_
#define OSAP_HEADER_AVLTREE_H_

class Set {
public:
    virtual void Find(int x) = 0;
    virtual void Insert(int x) = 0;
    virtual void Empty() = 0;
    virtual void Size() = 0;
    virtual void Height() = 0;
    virtual void Ancestor(int x) = 0;
    virtual void Average(int x) = 0;
    virtual void Rank(int x) = 0;
    virtual void Erase(int x) = 0;
    virtual void PrintTree() = 0;
};

#endif