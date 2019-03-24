#include <iostream>
#include "PQueue.h"
#include <cassert>
using namespace std;
//struct Element;
void InsertionTest()
{
    PQueue Q(5);
    Q.Insert({123,4});
    Q.Insert({13,1});
    Q.Insert({11,10});
    Q.Insert({2,5});
    assert(Q.getSize()==4);
    assert(Q.getCapacity()==5);
    assert(Q.isEmpty()==false);
    cout<<Q<<endl;
    Q.Insert({444,3});
    Q.Insert({444,2});
    assert(Q.getSize()==6);
    assert(Q.getCapacity()==10);
    assert(Q.getMaxPriority()==1);
    assert(Q.getMaxValue()==444);


}
void Operators_CopyConstructor()
{
    PQueue Q3;
    cin>>Q3;
    cout<<Q3;
    Q3--;
    PQueue Q4;
    Q4=Q3;
    assert(Q4.getSize()==Q3.getSize());
    assert(Q4.getCapacity()==Q3.getCapacity());
    assert(Q4.getMaxPriority()==Q3.getMaxPriority());
    assert(Q4.getMaxValue()==Q3.getMaxValue());
    Q4++;
    PQueue Q2(Q4);
    cout<<Q2;
    assert(Q2.getSize()==Q4.getSize());
    assert(Q2.getCapacity()==Q4.getCapacity());
    assert(Q2.getMaxPriority()==Q4.getMaxPriority());
    assert(Q2.getMaxValue()==Q4.getMaxValue());
}
int main()
{
    InsertionTest();
    Operators_CopyConstructor();
}
