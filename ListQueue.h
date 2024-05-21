#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "DblList.h"
#include <iostream>
using namespace std;

//template class of ListQueue
template <class T>
class ListQueue{

    public:
        ListQueue(); //default constructor
        ~ListQueue(); //destructor

        //core functions
        void insert(T d); //enqueue
        T dequeue(); //dequeue

        //aux/helper functions
        bool isEmpty(); //returns true or false if linkedlist is empty
        unsigned int getSize(); //returns number of size
        void print(); //prints contents of queue
        ListNode<T>* front(); //returns front of 

        DblList<T> *myList;

};

//default constructor
template <class T>
ListQueue<T>::ListQueue(){
    myList = new DblList<T>;
}

//default destructor
template <class T>
ListQueue<T>::~ListQueue(){
    delete myList;
}

//insert() function
template <class T>
void ListQueue<T>::insert(T d){
    myList->insertBack(d); //inserts a node to the back of queue
}

//dequeue() function
template <class T>
T ListQueue<T>::dequeue(){
    return myList->removeFront(); //removes front of node FIFO
}

//isEmpty() function
template <class T> 
bool ListQueue<T>::isEmpty(){
    return (myList->size == 0); //returns if Queue is empty or not (true/false)
}

//getSize() function
template <class T>
unsigned int ListQueue<T>::getSize(){
    return myList->getSize(); //returns size
}

//print() function
template <class T>
void ListQueue<T>::print(){
    ListNode<T>* node = myList->front;
    int i = 1;
    while (node != NULL){ //iterate through queue
        cout << "Student in line: " << i << ", Student Arrival Time: " << node->key->timeArrival << endl; //print the contents of Node
        ++i;
        node = node->next;
    }
}

//front() function
template <class T>
ListNode<T>* ListQueue<T>::front(){
    return myList->front; //returns the front node 
}

#endif