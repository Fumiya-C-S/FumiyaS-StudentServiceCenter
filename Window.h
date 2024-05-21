#ifndef WINDOW_H
#define WINDOW_H

#include "ListQueue.h"
#include "Customer.h"
#include <iostream>
using namespace std;

//Window Class
class Window{

    public:
        Window(int registrarCount, int cashierCount, int financialCount); //default constructor
        ~Window(); //default destructor

        //Core Functions
        void registrarWindow(ListNode<Customer*> *student); //adds student to Registrar Window to start appointment
        void cashierWindow(ListNode<Customer*> *student); //adds student to Cashier Window to start appointment
        void financialWindow(ListNode<Customer*> *student); //adds student to Financial Window to start appointment
        bool isOccupied(char type); //returns true or false on if there are any windows open for a requested Window type
        void timePassed(); //runs tick on Window elements
        void removeFromWindow(Customer* student, char window); //removes student from a specific window

        DblList<Customer*> *registrar; //Doubly Linked List of students that are at a Registrar Window
        DblList<Customer*> *cashier; //Doubly Linked List of students that are at a Cashier Window
        DblList<Customer*> *financial; //Doubly Linked List of students that are at a Financial Window

        int registrarNum; //variable keeping track of the number of Registrar Windows to open
        int cashierNum; //variable keeping track of the number of Cashier Windows to open
        int financialNum; //variable keeping track of the number of Financial Windows to open

        int *idleTimesRegistrar; //an array of integers that will keep track of the amount of ticks that Registrar Window was idle 
        int *idleTimesCashier; //an array of integers that will keep track of the amount of ticks that Cashier Window was idle 
        int *idleTimesFinancial; //an array of integers that will keep track of the amount of ticks that Financial Window was idle 
};

#endif