#ifndef DBLLIST_H
#define DBLLIST_H

#include <iostream>
using namespace std;

//Template Class of ListNode
template <class T>
class ListNode{

    public:
        ListNode(); //default constructor
        ListNode(T k); //overloaded constructor
        virtual ~ListNode(); //default destructor

        T key; //Template of key
        ListNode<T> *prev; //pointer to previous node
        ListNode<T> *next; //pointer to next node
};

//default constructor
template <class T>
ListNode<T>::ListNode(){
    //set all pointers and key to NULL
    prev = NULL;
    next = NULL;
    key = NULL;
}

//overloaded constuctor
template <class T>
ListNode<T>::ListNode(T k){
    //set key to passed in value k
    key = k;
    //set all pointers to NULL
    prev = NULL;
    next = NULL;
}

//overloaded destructor
template <class T>
ListNode<T>::~ListNode(){
    //set pointers to NULL
    prev = NULL;
    next = NULL;
}

//template class of Doubly Linked List
template <class T>
class DblList{

    public:
        DblList(); //default constructor
        virtual ~DblList(); //default destructor

        //Core Functions
        void insertFront(T d); //Inserts new node in front of list
        void insertBack(T d); //Inserts new node in back of list
        T removeFront(); //Removes front node
        T removeBack(); //Removes back node
        T removeNode(T v); //Removes the node with the passed in key
        int find(T v); //returns position of element of node with key that was passed in
        bool isEmpty(); //returns true or false if LinkedList is empty
        unsigned int getSize(); //returns number of size of LinkedList

        void print(); //prints the contents of LinkedList

        ListNode<T> *front; //Node of first node
        ListNode<T> *back; //Node of last node
        unsigned int size; //Variable keeping track of size

    private:
};

//default constructor
template <class T>
DblList<T>::DblList(){
    //set front and back to NULL and size to 0
    front = NULL;
    back = NULL;
    size = 0;
}

//default destructor
template <class T>
DblList<T>::~DblList(){
    ListNode<T> *node = front; //set node to front
    while (node != nullptr) { //deletes all nodes within LinkedList
        ListNode<T> *temp = node; 
        node = node->next; 
        delete temp; 
    }
    front = nullptr;
}

//insertFront() Function
template <class T>
void DblList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d); //create a new node with key d
    if(isEmpty()){ //if list is empty set back to new node
        back = node;
    } else{ //if not
        node->next = front; //set front to new node
        front->prev = node; //set previous front's prev to new front
    }
    
    front = node; //front is new node
    ++size; //increment size
}

//insertBack() function
template <class T>
void DblList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d); //create new node
    if(isEmpty()){ //if empty set to front
        front = node;
    } else { //if not
        node->prev = back; //set new node's prev to previous last node
        back->next =node; //set previous back node's next to new node
    }

    back = node; //set back to new node
    ++size; //increment size
}

//removeFront() function
template <class T>
T DblList<T>::removeFront(){
    if(isEmpty()){ //if empty throw error
        throw runtime_error("Linked List is Empty");
    }

    ListNode<T> *temp = front; //set temp node to front

    if(front->next == NULL){ //only one node in the list
        back = NULL;
    } else { //more than one node in the list
        front->next->prev = NULL;
    }

    //change pointers appropriately
    front = front->next;
    temp->next = NULL;
    T key = temp->key;
    --size; //decrement size
    delete temp;
    return key; //return the deleted Node's key
} 

//removeBack() function
template <class T>
T DblList<T>::removeBack(){
    if(isEmpty()){ //if empty throw error
        throw runtime_error("Linked List is Empty");
    }

    ListNode<T> *temp = back;

    if(back->prev == NULL){ //only one node in the list
        front = NULL;
    } else { //more than one node in the list
        back->prev->next = NULL;
    }

    //change pointers appropriately 
    back = back->prev;
    temp->prev = NULL;
    T key = temp->key;
    --size; //decrement size
    delete temp; 
    return key; //return deleted node's key
}

//removeNode() function
template <class T>
T DblList<T>::removeNode(T v){
    if(isEmpty()){ //if empty throw error
        throw runtime_error("List Is Empty");
    }

    ListNode<T> *curr = front; //set curr to front node
    while(curr != NULL){ //while node is not NULL
        if(curr->key == v){ //if the curr Node's key matches iterated node's key
            if(curr == front){ //and that node is front
                front = curr->next; 
                if(front != NULL) {//if front is not null
                    front->prev = NULL;
                } else {
                    back = NULL; // If the list becomes empty after removal
                }
            } else if(curr == back){ //if node being looked for is back node
                back = curr->prev;
                back->next = NULL;
            } else { //if its in the middle
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            T temp = curr->key;
            delete curr;
            --size; //decrement size
            return temp;
        }
        curr = curr->next; //iterate
    }
}

//find() function
template <class T>
int DblList<T>::find(T v){
    int pos = -1;

    ListNode<T> *curr = front;

    while(curr != NULL){ //iterate through linkedlist
        ++pos;
        if(curr->key == v){ //if found
            break;
        }
        curr = curr->next; //else iterate
    }

    if(curr == NULL){ //if not found return -1
        pos = -1;
    }

    return pos; //return position of node
}

//getSize() function
template <class T>
unsigned int DblList<T>::getSize(){
    return size; //returns size
} 

//isEmpty() function
template <class T>
bool DblList<T>::isEmpty(){
    return (size == 0); //returns if linkedlist is empty or not
}

#endif