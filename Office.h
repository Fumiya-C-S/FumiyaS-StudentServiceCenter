#ifndef OFFICE_H
#define OFFICE_H

#include "ListQueue.h"
#include "Customer.h"
#include "Window.h"
#include <iostream>
using namespace std;

//Office class
class Office{

    public:
        Office(); //default constructor
        Office(int numOffices[]); //overloaded constructor
        ~Office(); //default destructor

        //core functions
        void waitingRoom(ListNode<Customer*> *student); //imitates waiting room
        void timePassed();

        int registrarNum; //variable keeping track of number of Registrar Windows
        int cashierNum; //variable keeping track of number of Cashier Windows
        int financialNum; //variable keeping track of number of Financial Windows

        Window *myWindow; //create window class
        ListQueue<Customer*> *myWaitRegistrar; //ListQueue of students waiting for a Registrar window to open
        ListQueue<Customer*> *myWaitCashier; //ListQueue of students waiting for a Cashier window to open
        ListQueue<Customer*> *myWaitFinancial; //ListQueue of students waiting for a Financial window to open



};

#endif