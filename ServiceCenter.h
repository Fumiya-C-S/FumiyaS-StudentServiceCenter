#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <iostream>
#include <exception>
#include <fstream>
#include "ListQueue.h"
#include "Customer.h"
#include "Office.h"
using namespace std;

//ServiceCenter class
class ServiceCenter{

    public:
        ServiceCenter(); //default constructor
        ~ServiceCenter(); //default destructor

        //Core Functions
        void processFile(string inputFile); //processes the inputted File
        void startTime(); //starts the program and tick system
        void printStats(); //prints the statistics at end
 
    private:
        int time; //variable keeping track of current time
        int temp; //temp int variable
        int offices[3]; //array of ints that hold the number of windows to open for corresponding window type
        int numCustomers; //variable keeping track of the number of customers that arrived at a certain times

        bool allCustomersFinished; //bool of if all customers are finished with all appointments

        ListQueue<Customer*> *myCustomerList; //ListQueue of Customer pointers of customers that came to ServiceCenter
        DblList<Customer*> *finishedCustomers; //DblList of Customer pointers that holds all the students that finished all appointments
        Office *myOffice; //Office class

        double meanCashierWait = 0; //variable keeping track of mean Cashier wait time
        double meanRegistrarWait = 0; //variable keeping track of mean Registrar wait time
        double meanFinancialWait = 0; //variable keeping track of mean Financial wait time

        int longestCashierWait = 0; //variable keeping track of longest Cashier wait time
        int longestRegistrarWait = 0; //variable keeping track of longest Registrar wait time
        int longestFinancialWait = 0; //variable keeping track of longest Financial wait time

        int numWaitOverTen = 0; //variable keeping track of number of times students had to wait over 10 mins for a window
        int numIdleOverFive = 0; //variable keeping track of number of times a window was idle for over 5 mins

        double meanCashierIdle = 0; //variable keeping track of mean Cashier window idle time
        double meanRegistrarIdle = 0; //variable keeping track of mean Registrar window idle time
        double meanFinancialIdle = 0; //variable keeping track of mean Financial window idle time

        int longestCashierIdle = 0; //variable keeping track of longest Cashier window idle time
        int longestRegistrarIdle = 0; //variable keeping track of longest Registrar window idle time
        int longestFinancialIdle = 0; //variable keeping track of longest Financial window idle time

};

#endif