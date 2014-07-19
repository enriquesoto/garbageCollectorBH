#include "binomialheap.h"

BinomialHeap::BinomialHeap(bool (*f)(void*,void*),int size)
{
    this->funcionComparar=f;
    this->size = size;
    //heap

}

void BinomialHeap::link(NodoB &a, NodoB &b)
{
    a.parent = &b;
    a.siblingDer = *b.pChild.begin();
    a.siblingIzq=NULL;
    //b.siblingIzq=NULL;

    if(!b.pChild.empty()){
        NodoB *nodob = *b.pChild.begin();
        nodob->siblingIzq = &a;
    }

//    if(b.pChild.empty())
//        b.pChild.push_back(&a);
//    else
//        *b.pChild.begin() = &a;


    b.pChild.push_front(&a);
    b.degree ++;
}

BinomialHeap *BinomialHeap::merge(BinomialHeap& b1,BinomialHeap& b2)
{
    NodoB* a;
    NodoB* b;
    NodoB* c;
     // punteros al nodo mas izquierdo del heap
    if(b1.heap.empty())
        a=NULL;
    else
        a = *b1.heap.begin();
    if (b2.heap.empty())
        b = NULL;
    else
        b = *b2.heap.begin();

    if(b1.heap.empty())
        b1.heap.push_back(minDegree(*a,*b));
    else
        *b1.heap.begin()=minDegree(*a,*b);

    if (*b1.heap.begin() == NULL) return &b1;
    if (*b1.heap.begin() == b ) b=a;

    a = *b1.heap.begin();

    while (b != NULL){

        if(a->siblingDer == NULL){

            a->siblingDer = b;
            b->siblingIzq=a;
            *b2.heap.begin()=NULL; // liberando el primero de la lista de heaps de b2
            delete &b2;
            //b1.heap.push_back(b);

            return &b1;

        }
        else
            if(a->siblingDer->degree < b->degree){
                a = a->siblingDer; //recorre a
            } else{
                c = b->siblingDer;
                b->siblingDer = a->siblingDer;
                a->siblingDer->siblingIzq = b; //el hermano izq del hermano derecho de a es b;
                a->siblingDer = b; //b apunta al hermano de a
                b->siblingIzq = a;
                a=a->siblingDer;
                b=c;
            }
    }
    return &b1;
}

BinomialHeap* BinomialHeap::junction(BinomialHeap& b1, BinomialHeap& b2)
{
    NodoB* x;
    NodoB* prevX;
    NodoB* nextX;

    BinomialHeap* b=merge(b1,b2);

    if(b==NULL){ //warning
        return b;
    }
    prevX = NULL;
    x=*b->heap.begin() ;
    nextX = x->siblingDer;

    while(nextX != NULL){

        if( (x->degree != nextX->degree) || (nextX->siblingDer != NULL && nextX->siblingDer->degree == x->degree) ){
            prevX = x;
            x=nextX;
        }else{

//            if((int *)x->key <= (int *)nextX->key){
            if(funcionComparar(nextX->key,x->key)){
                x->siblingDer = nextX->siblingDer;
                if(nextX->siblingDer)
                    nextX->siblingDer->siblingIzq = x; // el hermano derecho de next-x sera el hermano derecho de x
                link(*nextX,*x); //(y,z) menor z
            }else{
                if(prevX == NULL){
                    *b->heap.begin() = nextX;
                }else
                    prevX->siblingDer = nextX;


                nextX->siblingIzq=x->siblingIzq;
                if(x->siblingIzq != NULL)
                    x->siblingIzq->siblingDer=nextX;
                link(*x,*nextX);
                x=nextX;

            }

        }
        nextX = x->siblingDer;
        //return b;
    }
    return b;
}

void BinomialHeap::decreaseKey(BinomialHeap &b, void *oldValue, void *newKey)
{
    NodoB *y;
    NodoB *z;
    NodoB *foundNode;

    if( funcionComparar(newKey,oldValue))
        qDebug()<<"error la nuva llave es mas grande que la actual llave";
    NodoB *headB=*b.heap.begin();
    foundNode = find(*headB,oldValue);
    foundNode->key=newKey;
    y = foundNode;
    z = foundNode->parent;



    //while(z != NULL && y->key < z->key){

    while(z != NULL && funcionComparar(z->key,y->key)){

        void *tempKey; //intercambio de llaves
        tempKey = y->key;
        y->key=z->key;
        z->key = tempKey;

        //cambiar satelites si los hay

        y = z;
        z = y->parent; //:D

    }

}

NodoB *BinomialHeap::extractMin(BinomialHeap &b)
{

    NodoB *headNode = *b.heap.begin();
    NodoB *minTemp= findMin(*headNode);
    BinomialHeap *btempExtractMin = new BinomialHeap(this->funcionComparar,this->size);

    NodoB *nodoHead = myreverse(*minTemp);

    btempExtractMin->heap.push_front(nodoHead);

    if(minTemp->siblingIzq && minTemp->siblingDer){

        minTemp->siblingDer->siblingIzq = minTemp->siblingIzq;
        minTemp->siblingIzq->siblingDer = minTemp->siblingDer;

    }else
        if(!minTemp->siblingDer){ // si hermano derecho es nulo
            minTemp->siblingIzq->siblingDer = NULL;
        }else
            if(!minTemp->siblingIzq){
                minTemp->siblingDer->siblingIzq=NULL;
            }

    b.junction(b,*btempExtractMin);
    qDebug()<<"kike";

    return minTemp;

    //btemp->heap.begin() = minTemp->pChild.reverse();
    //*minTemp = NULL; //borrado
    //b=junction(b,btemp);
}

NodoB *BinomialHeap::findMin(NodoB &aNode)
{
    //myIterator it= heap.begin();
    NodoB *ith = &aNode;
    NodoB *itNexth;
    NodoB *minTemp;
    void *min= aNode.key;


    while(ith){
        if(funcionComparar(min,ith->key)){
            //min = ith->key;
            minTemp = ith;
        }
        ith = ith->siblingDer;
    }

//    for(;heap.end();it++){
//        if(*it.key<min){
//            min = *it.key;
//            minTemp = &(*it);
//        }
//    }
    return minTemp;
}

void BinomialHeap::insert(BinomialHeap &bh, NodoB &nodo)
{

    BinomialHeap *bTemp=new BinomialHeap(funcionComparar,this->size);
    nodo.parent = NULL;
//    list<NodoB*> *listTemp;
//    *listTemp = a.pChild;
//    listTemp=NULL;

    nodo.siblingDer = NULL;
    nodo.degree = 0;
    nodo.siblingIzq=NULL;
    bTemp->heap.push_back(&nodo);
    BinomialHeap *bhTemp;
    bhTemp=junction(bh,*bTemp);

}

NodoB *BinomialHeap::myreverse(NodoB &b)
{
    NodoB* x;
    NodoB* prevX=NULL;

    x=*b.pChild.begin();
    NodoB* nextX = x->siblingDer;
    while(x){ // costo n
        NodoB * tempNode;
        tempNode = x->siblingDer;
        x->siblingDer = prevX;
        x->siblingIzq = tempNode;
        prevX= x;
        x=tempNode;
//        prevX = x; //actualizar
//        if(x->siblingIzq == NULL)
//            nextX=NULL;
//        else
//            nextX=nextX->siblingDer;

    }

    b.pChild.reverse(); //costo n

    return prevX;

}

NodoB *BinomialHeap::find(NodoB &b,void *value)
{
    //if(b.key==value)
    if(!funcionComparar(b.key,value) && !funcionComparar(value,b.key)) //inviritiendo argumentos si los dos son falsos son iguales
        return &b;
    NodoB *x = &b;
    while(x){
        if(!funcionComparar(b.key,value) && !funcionComparar(value,b.key))
            return x;
        NodoB *result = bfs(*x,value); //almaceno nodo encontrado
        if(result) //si existe
            return result;
        x=x->siblingDer;
    }
    return NULL;

}

NodoB *BinomialHeap::bfs(NodoB &b,void* value)
{


    //NodoB *x=b.pChild.begin();
    if(!funcionComparar(b.key,value) && !funcionComparar(value,b.key)) //preorder operation
        return &b;
    for(list<NodoB*>::const_iterator it = b.pChild.begin(); it != b.pChild.end(); it++)
    {
        NodoB *temoNode = *it;
        NodoB *result=bfs(*temoNode,value);
        if(result)
            return result;
        qDebug()<<"xD";
    }
    return NULL;
}

BinomialHeap *BinomialHeap::deleteNode(BinomialHeap &bh, void* target)
{
    void *minValue=getmin(this->size);
    int b = INT_MIN;
    void *p = &b;
    decreaseKey(bh,target,p); //conseguir el valor minimo de acuerdo al size
    extractMin(bh);
}

void BinomialHeap::binomialHeap2file(BinomialHeap &bh)
{

    file = new QFile("out.dot");
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    out = new QTextStream(file);

    *out<<"digraph G { "<<endl;

    NodoB *x = *bh.heap.begin();

    while(x){

        if(x->siblingDer){
            *out<<"\"\\"<<x<<"\" [label = \""<<x->key<<"\"] "<<endl;
            *out<<"\"\\"<<x->siblingDer<< "\" [ label=\""<<x->siblingDer->key<<"\"] ;" <<endl ;
            *out<<"\"\\"<<x<<"\""<<" -> \"\\"<<x->siblingDer<< "\" [constraint=false] "<<endl ;
        }


        if(x->siblingIzq){
            *out<<"\"\\"<<x<<"\" [label = \""<<x->key<<"\"] "<<endl;
            *out<<"\"\\"<<x->siblingIzq<< "\" [ label=\""<<x->siblingIzq->key<<"\"] ;"<<endl;
            *out<<"\"\\"<<x<<"\""<<" -> \"\\"<<x->siblingIzq<< "\" [constraint=false] "<<endl ;
        }
        for(list<NodoB*>::const_iterator it = x->pChild.begin(); it != x->pChild.end(); it++)
        {
            NodoB *aNode = *it;
            *out<<"\"\\"<<x<<"\" [label = \""<<x->key<<"\"] "<<endl;
            *out<<"\"\\"<<aNode<<"\" [label=\""<<aNode->key<<"\" ]"<<endl;
            *out<<"\"\\"<<x<<"\" -> \"\\"<<aNode<<"\""<<endl;
            bfsPrint(*aNode);
        }

//        NodoB *result = bfs(*x,value); //almaceno nodo encontrado
//        if(result) //si existe
//            return result;



        x=x->siblingDer;
    }
    *out<<"} "<<endl;
    file->close();
}

void BinomialHeap::bfsPrint(NodoB &b)
{

    if(b.siblingDer){
        *out<<"\"\\"<<&b<<"\" [label = \""<<b.key<<"\"] "<<endl;
        *out<<"\"\\"<<b.siblingDer<< "\" [label=\""<<b.siblingDer->key<<"\"] ;" <<endl ;
        *out<<"\"\\"<<&b<<"\" -> \"\\"<<b.siblingDer<< "\" [constraint=false]"<<endl ;
    }
    if(b.siblingIzq){
        *out<<"\"\\"<<&b<<"\" [label = \""<<b.key<<"\"] "<<endl;
        *out<<"\"\\"<<b.siblingIzq<< "\" [label=\""<<b.siblingIzq->key<<"\"] ;"<<endl;
        *out<<"\"\\"<<&b<<"\" -> \"\\"<<b.siblingIzq<< "\" [constraint=false]"<<endl;
     }
    //out<<b.key<<" -> "<<b.siblingDer->key<<endl ;

    for(list<NodoB*>::const_iterator it = b.pChild.begin(); it != b.pChild.end(); it++)
    {
        NodoB *temoNode = *it;
        *out<<"\"\\"<<&b<<"\" [label = \""<<b.key<<"\"] "<<endl;
        *out<<"\"\\"<<temoNode<<"\" [label = \""<<temoNode->key<<"\"] "<< endl ;
        *out<<"\"\\"<<&b<<"\" -> \"\\"<<temoNode<<"\""<< endl ;
        bfsPrint(*temoNode);

        qDebug()<<"xD";
    }
    //return NULL;

}

void *BinomialHeap::getmin(int size)
{
    char *p = new char[size];
    int minimo = pow(2,size*8-1);
    *p=minimo;
}

NodoB *BinomialHeap::minDegree(NodoB &a, NodoB &b)
{
    if(&a == NULL) return &b;
    if(&b == NULL) return &a;
    if(a.degree<=b.degree)
        return &a;
    return &b;

}

void BinomialHeap::deleteObject()
{
    delete this;
}

BinomialHeap::~BinomialHeap()
{
    for(list<NodoB*>::const_iterator it = heap.begin(); it != heap.end(); it++)
    {
        delete *it;
    }
    heap.clear();
}



