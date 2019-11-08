//
// Stack of real numbers
//
#ifndef REAL_STACK_H
#define REAL_STACK_H

const int STACK_DEFAULT_SIZE = 256;

class StackException {
public:
    const char *reason;
    StackException():
        reason("")
    {}

    StackException(const char *cause):
        reason(cause)
    {}
};

class RealStack {
private:
    int maxElems;
    int numElems;
    double* elems;
public:
    RealStack():
        maxElems(STACK_DEFAULT_SIZE),
        numElems(0),
        elems(new double[maxElems])
    {}

    RealStack(int maxSize):
        maxElems(maxSize),
        numElems(0),
        elems(new double[maxElems])
    {}

    RealStack(const RealStack& s):
        maxElems(s.maxElems),
        numElems(s.numElems),
        elems(new double[maxElems])
    {
        for (int i = 0; i < s.numElems; ++i)
            elems[i] = s.elems[i];
    }

    ~RealStack() {
        delete[] elems;
    }

    RealStack& operator=(const RealStack& s);

    void push(double);
    double pop() ;
    double top() const ;
    double& top() ;
    int size() const { return numElems; }
    int depth() const { return size(); }

    void clear() { numElems = 0; }
    void init() { clear(); }
    bool empty() const {
        return (numElems == 0);
    }

    // Element at depth i.
    // elementAt(0) == top of stack
    double elementAt(int i) const ;
    double& elementAt(int i) ;
};

#endif
