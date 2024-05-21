#include "Office.h"

//default constructor
Office::Office(){
    //set all open window numbers to 1
    registrarNum = 1;
    cashierNum = 1;
    financialNum = 1;

    myWindow = new Window(registrarNum, cashierNum, financialNum); // initialize myWindow with the corrensponding window numbers
    myWaitRegistrar = new ListQueue<Customer*>(); //initialize the ListQueue of Customers that are waiting for a Resigtrar window to open
    myWaitCashier = new ListQueue<Customer*>(); //initialize the ListQueue of Customers that are waiting for a Cashier window to open
    myWaitFinancial = new ListQueue<Customer*>(); //initialize the ListQueue of Customers that are waiting for a Financial window to open
}

//overlaoded constructor
Office::Office(int numOffices[]){
    //set number of windows open to the corresponding number of windows open
    registrarNum = numOffices[0];
    cashierNum = numOffices[1];
    financialNum = numOffices[2];

    myWindow = new Window(registrarNum, cashierNum, financialNum); // initialize myWindow with the corrensponding window numbers
    myWaitRegistrar = new ListQueue<Customer*>(); //initialize the ListQueue of Customers that are waiting for a Resigtrar window to open
    myWaitCashier = new ListQueue<Customer*>(); //initialize the ListQueue of Customers that are waiting for a Cashier window to open
    myWaitFinancial = new ListQueue<Customer*>(); //initialize the ListQueue of Customers that are waiting for a Financial window to open
}

//default destructor
Office::~Office(){
    //garbage collect all dynamically allocated classes
    delete myWindow;
    delete myWaitRegistrar;
    delete myWaitCashier;
    delete myWaitFinancial;
}

//waitingroom() function
void Office::waitingRoom(ListNode<Customer*> *student){
    if (student->key->order[student->key->getWindowComp()] == "F"){ //if the window they need to visit first/next is Financial
        if (!myWindow->isOccupied('f')){ //check if Financial window has an open window
            cout << "Sent Student to Financial Window" << endl;
            myWindow->financialWindow(student); //if yes send student to financial window
        } else {
            cout << "Windows Full, sending to Waitlist " << endl;
            myWaitFinancial->insert(student->key); //if not, put them in the financial wait list
        }
    } else if (student->key->order[student->key->getWindowComp()] == "C"){ //if the window they need to visit first/next is Cashier
        if (!myWindow->isOccupied('c')){ //check if Cashier window has an open window
            cout << "Sent Student to Cashier Window" << endl;
            myWindow->cashierWindow(student); //if yes send student to cashier window
        } else {
            cout << "Windows Full, sending to Waitlist " << endl;
            myWaitCashier->insert(student->key); //if not, put them in the cashier wait list
        }
    } else if (student->key->order[student->key->getWindowComp()] == "R") { //if the window they need to visit first/next is Registrar
        if (!myWindow->isOccupied('r')){ //check if Registrar window has an open window
            cout << "Sent Student to Registrar Window" << endl;
            myWindow->registrarWindow(student); //if yes send student to Registrar window
        } else {
            cout << "Windows Full, sending to Waitlist " << endl;
            myWaitRegistrar->insert(student->key); //if not, put them in the registrar wait list
        }
    }
}

//timePassed() function
void Office::timePassed(){
    ListNode<Customer*> *currRegistrar = myWaitRegistrar->front(); //iterate through the waitlist of Registrar
    while (currRegistrar != NULL) {
        //if the number of students at a Registrar window is less than the total number of windows
        if (myWindow->registrar->getSize() < registrarNum){
            myWaitRegistrar->dequeue(); //dequeue student from waitlist
            waitingRoom(currRegistrar); //send student to Registrar
        }

        currRegistrar->key->incrementIdleTime('r'); //increment Idle time of Registrar
        currRegistrar = currRegistrar->next;
    }
    delete currRegistrar;

    ListNode<Customer*> *currCashier = myWaitCashier->front(); //iterate through the waitlist of Cashier
    while (currCashier != NULL) {
        //if the number of students at a Cashier window is less than the total number of windows
        if (myWindow->cashier->getSize() < cashierNum){
            myWaitCashier->dequeue(); //dequeue student from waitlist 
            waitingRoom(currCashier); //send student to Cashier
        }

        currCashier->key->incrementIdleTime('c'); //increment Idle time of Cashier
        currCashier = currCashier->next;
    }
    delete currCashier;

    ListNode<Customer*> *currFinancial = myWaitFinancial->front(); //iterate through the waitlist of Financial
    while (currFinancial != NULL) {
        //if the number of students at a Cashier window is less than the total number of windows
        if (myWindow->financial->getSize() < financialNum){
            myWaitFinancial->dequeue(); //dequeue student from waitlist 
            waitingRoom(currFinancial); //send student to Financial
        }

        currFinancial->key->incrementIdleTime('f'); //increment Idle time of Financial
        currFinancial = currFinancial->next;
    }
    delete currFinancial;

    myWindow->timePassed(); //call timePassed()

    //iterate through all students at Registrar windows
    currRegistrar = myWindow->registrar->front;
    while (currRegistrar != NULL) {
        if(currRegistrar->key->getRegistrarTime() == 0){ //if they are done with their appointment at the window
            cout << "Sending Student from Registrar to Waiting " << endl;
            myWindow->removeFromWindow(currRegistrar->key, 'r'); //remove Student from window
            cout << "Removed Student from Window" << endl;
            waitingRoom(currRegistrar); //send student to waiting room 
        }
        currRegistrar = currRegistrar->next; //iterate
    }

    //iterate through all students at Cashier windows
    currCashier = myWindow->cashier->front;
    while (currCashier != NULL) {
        if(currCashier->key->getCashierTime() == 0){ //if they are done with their appointment at the window
            cout << "Sending Student from Cashier to Waiting " << endl;
            myWindow->removeFromWindow(currCashier->key, 'c'); //remove Student from window
            cout << "Removed Student from Window" << endl;
            waitingRoom(currCashier); //send student to waiting room 
        }
        currCashier = currCashier->next; //iterate
    }

    //iterate through all students at Financial windows
    currFinancial = myWindow->financial->front;
    while (currFinancial != NULL) {
        if(currFinancial->key->getFinancialTime() == 0){ //if they are done with their appointment at the window
            cout << "Sending Student from Financial to Waiting " << endl;
            myWindow->removeFromWindow(currFinancial->key, 'f'); //remove Student from window
            cout << "Removed Student from Window" << endl;
            waitingRoom(currFinancial); //send student to waiting room 
        }
        currFinancial = currFinancial->next; //iterate
    }
    
    //iterate through all students at Registrar window to see if student has completed all appointments
    currRegistrar = myWindow->registrar->front;
    while (currRegistrar != NULL){
        if (currRegistrar->key->finished){
            myWindow->registrar->removeNode(currRegistrar->key); //remove student from Registrar window
            cout << "Student has finished all appointments" << endl;
        }
        currRegistrar = currRegistrar->next; //iterate
    }

    //iterate through all students at Cashier window to see if student has completed all appointments
    currCashier = myWindow->cashier->front;
    while (currCashier != NULL){
        if (currCashier->key->finished){
            myWindow->cashier->removeNode(currCashier->key); //remove student from Registrar window
            cout << "Student has finished all appointments" << endl;
        }
        currCashier = currCashier->next; //iterate
    }

    //iterate through all students at Financial window to see if student has completed all appointments
    currFinancial = myWindow->financial->front;
    while (currFinancial != NULL){
        if (currFinancial->key->finished){
            myWindow->financial->removeNode(currFinancial->key); //remove student from Registrar window
            cout << "Student has finished all appointments" << endl;
        }
        currFinancial = currFinancial->next; //iterate
    }

    //garbage collect dynamically allocated classes
    delete currRegistrar;
    delete currCashier;
    delete currFinancial;
}