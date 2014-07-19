#include "nodob.h"

NodoB::NodoB()
{
    //this->key=key;
    this->degree=0;
    this->siblingDer=NULL;
    this->siblingIzq=NULL;
    this->parent=NULL;
    *pChild.begin()=NULL;
}

void NodoB::setKey(void *key)
{
    this->key=key;
}

NodoB::~NodoB()
{
    for(list<NodoB*>::const_iterator it = pChild.begin(); it != pChild.end(); it++)
    {
        delete *it;
    }
    pChild.clear();
}
