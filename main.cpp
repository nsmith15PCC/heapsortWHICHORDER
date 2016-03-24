#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

#define left(n)  (2*n+1)
#define right(n) (2*n+2)

template<typename T>
void heapSort(vector<T> &list);

template<typename T>
void reheapifyUp(vector<T> &list, vector<size_t> &orderlist, size_t pos);

template<typename T>
void reheapifyDown(vector<T> &list, vector<size_t> &orderlist, size_t pos);

template<typename T>
void print(const vector<T>&list, char* title);

template<typename T>
size_t maxOfList(const vector<T>& list);

template<typename T>
void initialize(vector<T> &list);

int main()
{
    vector<size_t> list;
    srand(time(NULL));
    initialize(list);
    print(list,"unsorted");
    heapSort(list);
    print(list,"sorted by index");
}


template<typename T>
void heapSort(vector<T> &list)
{
    //Put items size_to the heap
    vector<size_t> orderlist;
    for (size_t i = 0; i < list.size(); ++i)
        orderlist.push_back(i);

    for(size_t i = 1; i <list.size(); ++i)
        reheapifyUp(list, orderlist, i);
    //Take items out of the heap
    for(size_t i = list.size()-1; i > 0; --i)
    {
        swap(list[i], list[0]);
        swap(orderlist[i], orderlist[0]);
        reheapifyDown(list,orderlist, i-1);
    }
    list = orderlist;
}


template<typename T>
void initialize(vector<T> &list)
{
    size_t largest, qty;
    cout<<"How many random numbers do you want? ";
    cin>>qty;
    cout<<"What is the largest random number to see? ";
    cin>>largest;
    for(size_t i = 0; i < qty; ++i)
        list.push_back(rand()%largest + 1);
}

template<typename T>
void reheapifyUp(vector<T> &list, vector<size_t> &orderlist, size_t pos)
{
    size_t child = pos,
            parent = (child-1)/2;
    bool notDone = true;
    while(child && notDone)
        if(list[child] > list[parent])
        {
            swap(list[child],list[parent]);
            swap(orderlist[child], orderlist[parent]);
            child = (child-1)/2;
            parent = (child-1)/2;
        }
        else
            notDone = false;
}

template<typename T>
void reheapifyDown(vector<T> &list, vector<size_t> &orderlist, size_t pos)
{
    bool notDone = true;
    size_t parent = 0, toSwap;
    while(notDone && parent < pos)
        //No Children
        if( left(parent) > pos)
            notDone=false;
        else
        {
            //Two kids?????
            if(right(parent) <= pos)
            {
                toSwap = list[right(parent)]>list[left(parent)]
                        ?
                            right(parent) : left(parent);
            }
            else
                toSwap = left(parent); //Only child
            if(list[parent]<list[toSwap])
            {
                swap(list[parent], list[toSwap]);
                swap(orderlist[parent], orderlist[toSwap]);
                parent=toSwap;
            }
            else
                notDone = false;
        }
}

template<typename T>
size_t maxOfList(const vector<T>& list)
{
    size_t maximum = list[0];
    for(size_t i = 1; i < list.size(); ++i)
        maximum = max(maximum, list[i]);
    return maximum;
}

template<typename T>
void print(const vector<T>&list, char* title)
{
    size_t digits = 2 + log10(maxOfList(list))+1,
            col = 65/digits;
    cout<<"Your "<<title<<" list is: "<<endl;
    for(size_t i = 0; i < list.size(); ++i)
    {
        if(!(i%col))
            cout<<endl;
        cout<<setw(digits)<<list[i];
    }
    cout<<endl<<endl;
}
