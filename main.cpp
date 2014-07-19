#include <QtCore/QCoreApplication>
#include <binomialheap.h>
#include <QDebug>

bool comparaEnteros(void * a,void *b);



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BinomialHeap *bh = new BinomialHeap(comparaEnteros,sizeof(int));
    void *minimovalor = bh->getmin(sizeof(int));

    qDebug()<<"retorno "<<*((int *) minimovalor);
    
    return a.exec();
}

bool comparaEnteros(void * a,void *b)
{
    return *((int *) a) > *((int *)b);
}

bool comparaChars(void *a,void *b){
    return *((char *) a) > *((char *)b);
}
