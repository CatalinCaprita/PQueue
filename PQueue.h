#ifndef PQUEUE_H
#define PQUEUE_H
#include <iostream>

class PQueue
{
    struct Element
    {
        int Value;
        int Priority;
    };
    Element *store;
    int SIZE;
    int Capacity;
    int MaxVal,MaxPriority;
public:
    PQueue(int);//Constructor cu parametri
    PQueue();//Constructor fara parametri
    PQueue(const PQueue&);//Constructor de copiere
    ~PQueue();//Destructor
    void MinHeapify(int );//Functia care construieste un MinHeap plecand de la un nod dat
    void Insert(Element);//Insereaza o pereche {valoare,prioritate} in Heap, pastrand proprietatea de MinHeap
    void Pop();//Elimina elementul din coada
    int getSize();
    bool isEmpty();
    int getMaxValue();//Intoarce valoarea maxima
    int getMaxPriority();//Intoarce cea mai mare prioritate
    int getCapacity();//Intoarce Spatiul Alocat pentru stocarea elementelor
    PQueue operator+(PQueue const &);
    PQueue& operator=(const PQueue &);
    void operator++(int);
    void operator--(int);
    friend std::ostream& operator<<(std::ostream &,const PQueue &);
    friend std::istream& operator>>(std::istream &,PQueue &);

#endif // PQUEUE_H
};
