//
// Stack of real numbers, implementation
//
#include <assert.h>
#include "RealStack.h"

RealStack& RealStack::operator=(const RealStack& s) {
    if (maxElems < s.maxElems) {
        delete[] elems;
        elems = new double[s.maxElems];
        maxElems = s.maxElems;
    }
    for (int i = 0; i < s.numElems; ++i)
        elems[i] = s.elems[i];
    numElems = s.numElems;
    return *this;
}

void RealStack::push(double x) {
    if (numElems >= maxElems) {
        int extent = maxElems / 4;
        if (extent < 16)
            extent = 16;
        double* p = new double[maxElems + extent];
        for (int i = 0; i < maxElems; ++i)
            p[i] = elems[i];
        elems = p;
        maxElems += extent;
    }
    assert(numElems < maxElems);
    elems[numElems] = x;
    ++numElems;
}

double RealStack::pop()  {
    if (numElems == 0)
        throw StackException("Stack empty");
    double x = elems[numElems - 1];
    --numElems;
    return x;
}

double RealStack::top() const  {
    if (numElems == 0)
        throw StackException("Stack empty");
    return elems[numElems - 1];
}

double& RealStack::top()  {
    if (numElems == 0)
        throw StackException("Stack empty");
    return elems[numElems - 1];
}

double RealStack::elementAt(int i) const  {
    if (i >= numElems)
        throw StackException("Out of bounds");
    return elems[numElems - 1 - i];
}

double& RealStack::elementAt(int i)  {
    if (i >= numElems)
        throw StackException("Out of bounds");
    return elems[numElems - 1 - i];
}
