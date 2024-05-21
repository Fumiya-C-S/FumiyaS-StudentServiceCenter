#include "Customer.h"

//default constructor
Customer::Customer(){
    //set all default settings
    timeWaitRegistrar = 0;
    timeWaitCashier = 0;
    timeWaitFinancial = 0;
    finished = false;
    allFinished = false; 
}

//overloaded constructor
Customer::Customer(string info, int time){
    string timeInfo;
    stringstream ss(info); //split the string info by its spaces 
    int i = 0;
    while (getline(ss, timeInfo, ' ')){
        if (i < 3){
            timeOrder[i] = stoi(timeInfo); //put first 3 numbers into timeOrder
        } else {
            order[i % 3] = timeInfo; //put last 3 numbers into order arrat
        }
        ++i;
    }

    //populate time neede for each window
    for (int i = 0; i < 3; ++i){
        if(order[i] == "F"){
            timeFinancial = timeOrder[i];
        } else if (order[i] == "C"){
            timeCashier = timeOrder[i];
        } else {
            timeRegistrar = timeOrder[i];
        }
    }

    //update the time that this student arrived
    timeArrival = time;
}

//default destructor
Customer::~Customer(){}

//incrementIdleTime() function
void Customer::incrementIdleTime(char window){
    if (tolower(window) == 'r'){ //if waiting for registrar
        timeWaitRegistrar++; //increment waittime for registrar
        cout << "Student has been waiting " << timeWaitRegistrar << " for register." << endl;
    } else if(tolower(window) == 'c'){ //if waiting for cashier
        timeWaitCashier++; //increment waittime for cashier
        cout << "Student has been waiting " << timeWaitCashier << " for cashier." << endl;
    } else { //if waiting for financial
        timeWaitFinancial++; //increment waittime for financial
        cout << "Student has been waiting " << timeWaitFinancial << " for financial." << endl;
    }
}

//decrementTime() function
void Customer::decrementTime(char window){
    if (tolower(window) == 'r'){ //if currently in registrar
        cout << "Customer appointment time for Registrar decreasing from " << timeRegistrar << " to ";
        timeRegistrar--; //decrease the time needed to spent there
        cout << timeRegistrar << "." << endl;
        if (timeRegistrar == 0){ //if student is done with appointment
            cout << "Customer Completed Appointment at " << window << "." << endl;
            if (windowCompleted == 2){ //if this was student's last appointment needed
                finished = true; //student has completed all appointments
                return;
            }
            windowCompleted++; //increment windowCompelted
        }
    } else if (tolower(window) == 'c'){ //if currently in cashier
        cout << "Customer appointment time for Cashier decreasing from " << timeCashier << " to ";
        timeCashier--; //decrease the time needed to spent there
        cout << timeCashier << "." << endl;
        if (timeCashier == 0){ //if student is done with appointment
            cout << "Customer Completed Appointment at " << window << "." << endl;
            if (windowCompleted == 2){ //if this was student's last appointment needed
                finished = true; //student has completed all appointments
                return;
            }
            windowCompleted++; //increment windowCompelted
        }
    } else if (tolower(window) == 'f'){ //if currently in financial
        cout << "Customer appointment time for Financial decreasing from " << timeFinancial << " to ";
        timeFinancial--; //decrease the time needed to spent there
        cout << timeFinancial << "." << endl;
        if (timeFinancial == 0){ //if student is done with appointment
            cout << "Customer Completed Appointment at " << window << "." << endl;
            if (windowCompleted == 2){ //if this was student's last appointment needed
                finished = true; //student has completed all appointments
                return;
            }
            windowCompleted++; //increment windowCompelted
        }
    }
}

//getWindowComp() function
int Customer::getWindowComp(){
    return windowCompleted; 
}

//getRegistrarTime() function
int Customer::getRegistrarTime(){
    return timeRegistrar; 
}

//getCashierTime() function
int Customer::getCashierTime(){
    return timeCashier;
}

//getFinancialTime() function
int Customer::getFinancialTime(){
    return timeFinancial;
}

//incrementWindowComp() function
void Customer::incrementWindowComp(){
    windowCompleted++; //increment windowCompleted
    if (windowCompleted == 2){ //if all windows are completed
        finished = true; //student is finished
        return;
    }
}

//getTotalWaitTime() function
int Customer::getTotalWaitTime(){
    totalWait = timeWaitCashier + timeWaitFinancial + timeWaitRegistrar; //add all wait times across all windows
    return totalWait;
}