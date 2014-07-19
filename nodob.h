#ifndef NODOB_H
#define NODOB_H

#include <list>
#include <stddef.h>

using namespace std;


class NodoB
{
public:
    NodoB();
    void *key; // direccion de memoria de cualquier cosa
    NodoB *parent; //
    list<NodoB *> pChild;
    int degree;
    NodoB *siblingDer;
    NodoB *siblingIzq;
    int point2me;

    void setKey(void *);
    NodoB *crearNodo(NodoB &p,int size);
    ~NodoB();
};

#endif // NODOB_H
