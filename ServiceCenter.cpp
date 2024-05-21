#include "ServiceCenter.h"

//default constructor
ServiceCenter::ServiceCenter(){
    //set necessaru variables to 0
    time = 0;
    temp = 0; 

    //initialize ListQueue and DoubleList
    myCustomerList = new ListQueue<Customer*>();
    finishedCustomers = new DblList<Customer*>();
}

//default destructor
ServiceCenter::~ServiceCenter(){
    //garbage collect dynamically allocated lists
    delete finishedCustomers;
    delete myCustomerList;
}

//processFile() function
void ServiceCenter::processFile(string inputFile){

    ifstream inFile(inputFile); //create input File stream
    string officeNums; //officeNums string to hold string from input.txt
    int numStudents = 0;  // Initialize numStudents
    int lastStudentNumIndex = 0; // Initialize lastStudentNumIndex that will hold the last time a student came

    if (inFile.is_open()) { //if file is open
        int i = 1; //i will count the current line in input.txt
        while (getline(inFile, officeNums)) {
            if (i < 4) { //the first 3 lines will be the number of offices that will open
                temp = stoi(officeNums); //change from string to int
                offices[i-1] = temp; 
            }

            if (i == 4){ //the 4th number will always be the time the next student arrives
                time = stoi(officeNums);
            } else if (i == 5){ //the 5th number will always by the number of students that arrives at the previous time
                numStudents = stoi(officeNums);
                lastStudentNumIndex = i; //set lastStudentNumIndex to the number of students that arrive
            }

            if (officeNums.size() > 5) { //if the string length is longer than 5, that means that line contains student info
                Customer *myCustomer = new Customer(officeNums, time);
                myCustomerList->insert(myCustomer);  
            }

            if (i > 5){ //after index 5
                if (i == lastStudentNumIndex + numStudents + 1){ //if i = the lastTime a student came plus number of students that came plus 1, then it will be the next time that the student came
                    time = stoi(officeNums);
                } else if (i == lastStudentNumIndex + numStudents + 2){ //the number after that will hold the number of students that came at that time
                    numStudents = stoi(officeNums);
                    lastStudentNumIndex = i;
                }
            }

            i++; //increment index
        }
        inFile.close();  // Close the file after processing
    } else {
        cerr << "Error: Unable to open file " << inputFile << endl; //throw error if file is unable to opens
    }

    myCustomerList->print(); //print the students that came to the ServiceCenter

    myOffice = new Office(offices); //intialize Office Class with the array of offices
    startTime();  // Start processing
    delete myOffice; //delete the Office after program ends
}

//startTime() function
void ServiceCenter::startTime(){
    cout << "Service Center Has Opened" << endl;
    time = 0;
    while (true){ //while true
        time++;
        cout << "Time: " << time << endl; //print out current time

        ListNode<Customer*> *curr = myCustomerList->front(); //iterate throw the list of customers that came
        while (curr != NULL){ 
            if (curr->key->timeArrival == time){ //if the current time equals the time that the student arrived
                myOffice->waitingRoom(curr); //send that student to the waiting room
            }
            curr = curr->next; //iterate
        }
        
        myOffice->timePassed(); //call timePassed()
        
        //detect when all students are done with all appointments
        ListNode<Customer*> *currCust = myCustomerList->front(); //iterate through all the students that came
        while (currCust != NULL){
            if (!currCust->key->finished){ //if the finished boolean is false, there is a student that is not done with all appointments
                allCustomersFinished = false; //set allCustomersFinished to false
                break; //break
            } else { //if student is finished
                allCustomersFinished = true; //set allCustomersFinished to true
            }
            currCust = currCust->next; //iterate
        }
        if (allCustomersFinished){ //if allCustomersFinished is trues
            cout << "All Customers have finished their appointment" << endl;
            delete curr; //garbage collect
            break; //break out of while(true) loop
        }
    }

    cout << "Service Center is closed" << endl;
    
    printStats(); //call printStats()
}

//printStats() function
void ServiceCenter::printStats(){

    cout << endl;
    cout << "Printing Wait-Time Statistics:" << endl; //start printing statistics

    int i = 0;
    ListNode<Customer*> *curr = myCustomerList->front(); //iterate through all of the customers that arrived
    while (curr != NULL){
        //add all the times that students had to wait for respective windows
        meanCashierWait += curr->key->timeWaitCashier;
        meanRegistrarWait += curr->key->timeWaitRegistrar;
        meanFinancialWait += curr->key->timeWaitFinancial;

        //this will keep the largest wait time value
        if (curr->key->timeWaitCashier > longestCashierWait){
            longestCashierWait = curr->key->timeWaitCashier;
        }
        if (curr->key->timeWaitFinancial > longestFinancialWait){
            longestFinancialWait = curr->key->timeWaitFinancial;
        }
        if (curr->key->timeWaitRegistrar > longestRegistrarWait){
            longestRegistrarWait = curr->key->timeWaitRegistrar;
        }

        //if the student waited for more than 10 minutes for a window, then increment numWaitOverTen
        if (curr->key->timeWaitCashier > 10){
            numWaitOverTen++;
        }
        if (curr->key->timeWaitFinancial > 10){
            numWaitOverTen++;
        }
        if (curr->key->timeWaitRegistrar > 10){
            numWaitOverTen++;
        }

        curr = curr->next;
        i++;
    }
    //divide by the number of students that came, to obtain the mean
    meanCashierWait = meanCashierWait / i;
    meanRegistrarWait = meanRegistrarWait / i;
    meanFinancialWait = meanFinancialWait / i;


    //iterate through all windows of registrar
    for (int i = 0; i < myOffice->registrarNum; ++i){
        meanRegistrarIdle += myOffice->myWindow->idleTimesRegistrar[i]; //add all idle times to find mean
        if (myOffice->myWindow->idleTimesRegistrar[i] > 5){ //if window was idle for more than 5 mins
            numIdleOverFive++; //increment numIdleOverFive
        }
        //this will keep the longest idle time in lognestRegistrarIdle
        if (myOffice->myWindow->idleTimesRegistrar[i] > longestRegistrarIdle){ 
            longestRegistrarIdle = myOffice->myWindow->idleTimesRegistrar[i];
        }
    }
    meanRegistrarIdle = meanRegistrarIdle / myOffice->registrarNum; //divide by number of windows to get mean
    
    //iterate through all windows of cashier
    for (int i = 0; i < myOffice->cashierNum; ++i){
        meanCashierIdle += myOffice->myWindow->idleTimesCashier[i]; //add all idle times to find mean
        if (myOffice->myWindow->idleTimesCashier[i] > 5){ //if window was idle for more than 5 mins
            numIdleOverFive++;
        }
        //this will keep the longest idle time in lognestCashierIdle
        if (myOffice->myWindow->idleTimesCashier[i] > longestCashierIdle){
            longestCashierIdle = myOffice->myWindow->idleTimesCashier[i];
        }
    }
    meanCashierIdle = meanCashierIdle / myOffice->cashierNum; //divide by number of windows to get mean

    //iterate through all windows of financial
    for (int i = 0; i < myOffice->financialNum; ++i){
        meanFinancialIdle += myOffice->myWindow->idleTimesFinancial[i]; //add all idle times to find mean
        if (myOffice->myWindow->idleTimesFinancial[i] > 5){ //if window was idle for more than 5 mins
            numIdleOverFive++;
        }
        //this will keep the longest idle time in lognestFinancialIdle
        if (myOffice->myWindow->idleTimesFinancial[i] > longestFinancialIdle){
            longestFinancialIdle = myOffice->myWindow->idleTimesFinancial[i];
        }
    }
    meanFinancialIdle = meanFinancialIdle / myOffice->financialNum; //divide by number of windows to get mean

    //print out Registrar/Cashier/Financial window stats
    cout << "Registrar: " << endl;
    cout << "Mean Student Wait Time Registrar: " << meanRegistrarWait << " min(s)." << endl;
    cout << "Longest Student Wait Time Registrar: " << longestRegistrarWait << " mins(s)." << endl;
    cout << "Mean Window Idle Time Registrar: " << meanRegistrarIdle << " min(s)." << endl;
    cout << "Longest Window Idle Time Registrar: " << longestRegistrarIdle << " min(s)." << endl;
    cout << endl;
    cout << "Cashier: " << endl;
    cout << "Mean Student Wait Time Cashier: " << meanCashierWait << " min(s)." << endl;
    cout << "Longest Student Wait Time Cashier: " << longestCashierWait << " mins(s)." << endl;
    cout << "Mean Window Idle Time Cashier: " << meanCashierIdle << " min(s)." << endl;
    cout << "Longest Window Idle Time Cashier: " << longestCashierIdle << " min(s)." << endl;
    cout << endl;
    cout << "Financial: " << endl;
    cout << "Mean Student Wait Time Financial: " << meanFinancialWait << " min(s)." << endl;
    cout << "Longest Student Wait Time Financial: " << longestFinancialWait << " mins(s)." << endl;
    cout << "Mean Window Idle Time Financial: " << meanFinancialIdle << " min(s)." << endl;
    cout << "Longest Window Idle Time Financial: " << longestRegistrarIdle << " min(s)." << endl;
    cout << endl;

    //print out number of students that waited over 10 minutes and number of windows that were idle for more than 5 mins
    cout << "Number of Students Waiting Over 10 Minutes Across All Offices: " << numWaitOverTen << " student(s)." << endl;
    cout << "Number of Windows Idle Over 5 Minutes Across All Offices: " << numIdleOverFive << " window(s)." << endl;
    cout << endl;

    
    
}