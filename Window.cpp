#include "Window.h"

//default constructor
Window::Window(int registrarCount, int cashierCount, int financialCount){
    //initializes Doubly Linked List of customers
    registrar = new DblList<Customer*>();
    cashier = new DblList<Customer*>();
    financial = new DblList<Customer*>();

    //initializes the number of windows to open for each window type
    registrarNum = registrarCount;
    cashierNum = cashierCount;
    financialNum = financialCount;

    //initializes the size of array based on the number of windows to open
    idleTimesRegistrar = new int[registrarNum];
    idleTimesCashier = new int[cashierNum];
    idleTimesFinancial = new int[financialNum];

    //populating each element of array with 0 
    for (int i = 0; i < registrarNum; ++i){
        idleTimesRegistrar[i] = 0;
    }
    for (int i = 0; i < cashierNum; ++i){
        idleTimesCashier[i] = 0;
    }
    for (int i = 0; i < financialNum; ++i){
        idleTimesFinancial[i] = 0;
    }
}

//default destructor
Window::~Window(){
    //garbage collecting
    //dynamically allocated array
    delete[] idleTimesCashier;
    delete[] idleTimesFinancial;
    delete[] idleTimesRegistrar;
    
    //dynamically allocated Doubly Linked List
    delete registrar;
    delete cashier;
    delete financial;
}

//isOccupied() function
bool Window::isOccupied(char type){
    if (tolower(type) == 'r'){ //if Registrar
        if (registrar->getSize() < registrarNum){ //has more windows than students at windows
            return false; //it is not occupied
        }
    } else if (tolower(type) == 'c'){ //if Cashier
        if (cashier->getSize() < cashierNum){ //has more windows than students at windows
            return false; //it is not occupied
        }
    } else { //if Financial
        if (financial->getSize() < financialNum){ //has more windows than students at windows
            return false; //it is not occupied
        }
    }
    return true; //if none above were true, then the window is occupied
}

//registrarWindow() function
void Window::registrarWindow(ListNode<Customer*> *student){  
    if (registrar->getSize() < registrarNum){ //if registrar has an open window
        registrar->insertBack(student->key); //add the student to the window
        cout << "Student is at Registrar Window" << endl;
        return;
    }
    cout << "Registrar Windows are Full" << endl; //else return that windows are full
}

//cashierWindow() function
void Window::cashierWindow(ListNode<Customer*> *student){
    if (cashier->getSize() < cashierNum){ //if cashier has an open window
        cashier->insertBack(student->key); //add the student to the window
        cout << "Student is at Cashier Window" << endl;
        return;
    }
    cout << "Cashier Windows are full" << endl; //else return that windows are full
}

//financialWindow() function
void Window::financialWindow(ListNode<Customer*> *student){
    if (financial->getSize() < financialNum){ //if financial has an open window
        financial->insertBack(student->key); //add the student to the window
        cout << "Student is at Financial Window" << endl;
        return;
    }
    cout << "Financial Windows are full" << endl; //else return that windows are full
 }

//timePassed() function
void Window::timePassed(){
    ListNode<Customer*> *currR = registrar->front; //iterate through all students at a Registrar Window
    while (currR != NULL){
        if(currR->key->getRegistrarTime() == 0){ //if student is done with appointment
            cout << "Student does not need Registrar" << endl;
            currR->key->incrementWindowComp(); //increment windowsCompleted
            currR = currR->next;
            continue;
        } else { //if not
            currR->key->decrementTime('r'); //decrement the amount of time needed at Registrar Window
            currR = currR->next;
        }
    }

    ListNode<Customer*> *currC = cashier->front; //iterate through all students at a Cashier Window
    while (currC != NULL){
        if(currC->key->getCashierTime() == 0){ //if student is done with appointment
            cout << "Student does not need Cashier" << endl;
            currC->key->incrementWindowComp(); //increment windowsCompleted
            currC = currC->next;
            continue;
        } else {
            currC->key->decrementTime('c'); //decrement the amount of time needed at Financial Window
            currC = currC->next;
        }
    }

    ListNode<Customer*> *currF = financial->front; //iterate through all students at a Financial Window
    while (currF != NULL){
        if(currF->key->getFinancialTime() == 0){ //if student is done with appointment
            cout << "Student does not need Financial" << endl;
            currF->key->incrementWindowComp(); //increment windowsCompleted
            currF = currF->next;
        } else {
            currF->key->decrementTime('f'); //decrement the amount of time needed at Cashier Window
            currF = currF->next;
        }
    }

    delete currR;
    delete currC;
    delete currF;

    //iterate through registrar
    currR = registrar->front;
    for (int i = 0; i < registrarNum; ++i){
        if (currR == NULL){ //if there is no student at registrar
            idleTimesRegistrar[i]++; //increment idle time
        }
    }

    //iterate through cashier
    currC = cashier->front;
    for (int i = 0; i < cashierNum; ++i){
        if (currC == NULL){ //if there is no student at cashier
            idleTimesCashier[i]++; //increment idle time
        }
    }

    //iterate through financial
    currF = financial->front;
    for (int i = 0; i < financialNum; ++i){
        if (currF == NULL){ //if there is no student at financial
            idleTimesFinancial[i]++; //increment idle time
        }
    }
}

//removeFromWindow() function
void Window::removeFromWindow(Customer* student, char window){
    if (tolower(window) == 'r'){ //if char is r
        registrar->removeNode(student); //remove the passed in student from registrar window
    } else if (tolower(window) == 'c'){ //if char is c
        cashier->removeNode(student); //remove the passed in student from cashier window
    } else if(tolower(window) == 'f'){ //if char is f
        financial->removeNode(student); //remove the passed in student from financial window
    }
}