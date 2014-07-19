#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include <nodob.h>
#include <QDebug>
#include <climits>
#include <QFile>
#include <cmath>

class BinomialHeap
{

    typedef typename list<NodoB*>::iterator myIterator;

public:

    bool (*funcionComparar)(void*,void*);

    BinomialHeap(bool (*f)(void*,void*),int size); // ingresa una funcion comparar de dos void
    void link(NodoB &a,NodoB &b);
    BinomialHeap *merge(BinomialHeap &b1, BinomialHeap &b2);
    BinomialHeap *junction(BinomialHeap &b1, BinomialHeap &b2);
    void decreaseKey(BinomialHeap &b,void *oldValue,void *newKey);
    NodoB *extractMin(BinomialHeap &b);
    NodoB * findMin(NodoB &aNode);
    void insert(BinomialHeap &bh,NodoB &temp1);
    NodoB *myreverse(NodoB &b);
    NodoB *find(NodoB &b, void *value);
    NodoB *bfs(NodoB &b, void* value);
    BinomialHeap *deleteNode(BinomialHeap &bh,void *target);
    void binomialHeap2file(BinomialHeap &bh);
    void bfsPrint(NodoB &b);

    QFile *file;
    QTextStream *out;
    list<NodoB*> heap;
    int size;
    void *getmin(int size);

private:


    NodoB minPointer;
    NodoB* minDegree(NodoB &a,NodoB &b);
    void deleteObject();
    ~BinomialHeap();
};

#endif // BINOMIALHEAP_H
