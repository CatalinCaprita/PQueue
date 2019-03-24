#include "PQueue.h"
#include <iostream>
using namespace std;
//Constructorii initializeaza campul store ca un array de perechi de tipul {valoare,prioritate}
PQueue::PQueue(int C):Capacity(C),SIZE(0),MaxVal(-1)
{
    store=new PQueue::Element[Capacity];
    std::cout<<"\nPriority Queue Created!";
}
PQueue::PQueue():Capacity(0),SIZE(0),MaxVal(-1)
{
    store=new PQueue::Element[Capacity];
    std::cout<<"\nPriority Queue Created Defeault constructor!";
}
PQueue::PQueue(const PQueue &Q):Capacity(Q.Capacity),SIZE(Q.SIZE),MaxVal(Q.MaxVal)
{
    store=new PQueue::Element[Q.Capacity];
    for(int i=0;i<Q.Capacity;i++)
        store[i]=Q.store[i];
    std::cout<<"\nPriority Queue Created Copy constructor!";
}

PQueue::~PQueue(){
    delete []store;
    SIZE=Capacity=0;
}
int PQueue::getCapacity()
{
    return Capacity;
}
void PQueue::MinHeapify(int StartNode)
{
    //Aleg Fiul stang si Fiul drept in Heap
    int Left=2*StartNode+1;
    int Right=2*StartNode+2;
    do
    {
        //Alege indexul minim dintre Left,Right si nodul insusi
        int minimum=StartNode;
        if(store[minimum].Priority>store[Left].Priority)
            minimum=Left;
        if(store[minimum].Priority>store[Right].Priority)
            minimum=Right;
        //Daca elementul nu are valorile minime, trebuie sa "coboare" in Heap
        if(minimum!=StartNode)
        {
            swap(store[minimum].Priority,store[StartNode].Priority);
            swap(store[minimum].Value,store[StartNode].Value);
            StartNode=minimum;
        }
        Left=2*StartNode+1;
        Right=2*StartNode+2;
    }while(Left<SIZE && Right<SIZE);// Executa cat timp nu am depasit Dimensiunea Heap-ului
}
void PQueue::Insert(PQueue::Element X)
{

    if(SIZE==Capacity)
    {
        //Daca am coada plina, Spatiul de stocare se mareste cu 5
        std::cout<<"\nQueue is Full!Resizing";
        PQueue::Element *aux=new PQueue::Element[Capacity+5];
        for(int i=0;i<SIZE;i++)
            aux[i]=store[i];
        delete []store;
        store=aux;
        Capacity+=5;
    }
    //Pentru orice elment inserat, verific daca valoarea retinuta in Value este cea maxima
    if(X.Value>MaxVal)
        MaxVal=X.Value;
    if(SIZE==0)
    {
        SIZE++;
        store[SIZE-1]=X;
        return;
    }
    //Elementul se insereaza pe ultima pozitie,iar apoi, in functie de prioritate, urca in Heap
    SIZE++;
    store[SIZE-1]=X;
    int Position=SIZE-1;
    while(store[Position].Priority<store[(Position-1)/2].Priority)
    {
        swap(store[Position].Priority,store[(Position-1)/2].Priority);
        swap(store[Position].Value,store[(Position-1)/2].Value);
        Position=(Position-1)/2;
    }
    //Daca am elemente cu aceeasi prioritate, le inserez crescator dupa valoare
    while(store[Position].Value<store[(Position-1)/2].Value)
    {
        swap(store[Position].Value,store[(Position-1)/2].Value);
        Position=(Position-1)/2;
    }
}
void PQueue::Pop()
{
    if(SIZE==0)
    {
        cout<<"\nQueue is empty!";
        return;
    }
    //Ultimul element devine primul
    store[0]=store[SIZE-1];
    SIZE--;
    //Refac Arborele respectand proprietatea de MinHeap, "coborand" elementul de pe prima pozitie
    MinHeapify(0);
}
int PQueue::getSize()
{
    return SIZE;
}
std::ostream& operator<<(std::ostream &out, const PQueue&Q)
{
    if(Q.SIZE!=0)
    {std::cout<<"\nOverlaod print operator called.Printed Queue: ";
    for(int i=0;i<Q.SIZE;i++)
        out<<"("<<Q.store[i].Value<<";"<<Q.store[i].Priority<<")";
    return out;}
    else
        std::cout<<"\nQueue is Empty!";

}
std::istream& operator>>(std::istream &in,PQueue &Q)
{
    delete []Q.store;
    std::cout<<"\nNumber of elements:";
    in>>Q.Capacity;
    Q.SIZE=0;
    Q.store=new PQueue::Element[Q.Capacity];
    PQueue::Element X;
    for(int i=0;i<Q.Capacity;i++)
        {
            std::cout<<"\nInsert Value and Priority:";
            in>>X.Value>>X.Priority;
            Q.Insert(X);
        }
        return in;
}
PQueue & PQueue::operator=(const PQueue &Q2)
{
    this->SIZE=Q2.SIZE;
    this->Capacity=Q2.Capacity;
    for(int i=0;i<this->SIZE;i++)
        this->store[i]=Q2.store[i];
    this->MaxPriority=Q2.MaxPriority;
    this->MaxVal=Q2.MaxVal;
    return *this;
}
PQueue PQueue::operator+(PQueue const &Q)
{
    PQueue Qr(Capacity+Q.Capacity);
    int i=0,j=0;
    /*Fuziunea a doua cozi,parcurgand simultan elementele
        i=indexul pentru prima coada
        j=indexul pentru a doua coada
    Algoritmul interclaseaza cele doua cozi in coada Qr rezultat
    Se utilizeaza operatia Insert definita pe clasa
    */
    while(i<SIZE && j<Q.SIZE)
    {
        if(store[i].Priority<Q.store[j].Priority)
        {
            Qr.Insert(store[i]);
            i++;
        }
        else
           if(store[i].Priority>Q.store[j].Priority)
        {
            Qr.Insert(Q.store[j]);
            j++;

        }
        else
        {
            if(store[i].Value<Q.store[j].Value)
        {
            Qr.Insert(store[i]);
            i++;
        }
        else
           if(store[i].Value>Q.store[j].Value)
        {
            Qr.Insert(Q.store[j]);
            j++;
        }
        else
        {
            Qr.Insert(store[i]);
            Qr.Insert(Q.store[j]);
            j++;
            i++;
        }
        }
    }
    while(i<SIZE){Qr.Insert(store[i]);i++;}
    while(j<Q.SIZE){Qr.Insert(Q.store[j]);j++;}

        return Qr;
}
bool PQueue::isEmpty()
{
    return (SIZE==0);
}
void PQueue::operator++(int Dummy)
{
    for(int i=0;i<SIZE;i++)
        store[i].Priority++;
    MaxPriority++;
}
void PQueue::operator--(int Dummy)
{
    for(int i=0;i<SIZE;i++)
        store[i].Priority--;
    //Elementele cu prioritate 0 vor fi la inceputul cozii, motiv pentru care pot face Pop();
    while(store[0].Priority==0)
        Pop();
}
int PQueue::getMaxValue()
{
    return MaxVal;
}
int PQueue::getMaxPriority()
{
    return store[0].Priority;
}


