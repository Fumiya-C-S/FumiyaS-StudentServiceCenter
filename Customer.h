#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Customer class
class Customer{

    public:
        Customer(); //default constructor
        Customer(string info, int time); //overloaded constructor
        ~Customer(); //default destructor

        //core functions
        void incrementIdleTime(char window); //increments idle time waiting for window
        void decrementTime(char window); //decrements amount of time student needs at specific window
        void incrementWindowComp(); //increments customer windowcompleted 

        //accessors
        int getWindowComp(); //gets windowCompleted
        int getFinancialTime(); //gets timeFinancial
        int getRegistrarTime(); //gets timeRegistrar
        int getCashierTime(); //gets timeCashier
        int getTotalWaitTime(); //gets totalWait
        void ifStudentFinished(); //gets finished



        //Time Counters
        int timeWaitRegistrar;
        int timeWaitCashier;
        int timeWaitFinancial;
        int timeArrival;
        int timeOrder[3];
        string order[3];

        bool finished;
        bool allFinished;

    private:
        int windowCompleted = 0; 
        int timeFinancial;
        int timeRegistrar;
        int timeCashier;
        int totalWait;


};

#endif