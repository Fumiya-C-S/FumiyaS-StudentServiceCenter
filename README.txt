Fumiya Shinagawa 
2416455
shinagawa@chapman.edu
CPSC-350-01
Assignment 4

The Waiting Game

Files:
Customer.cpp, Customer.h, DblList.h, input.txt, ListQueue.h, main.cpp, Office.cpp, Office.h, README.txt, ServiceCenter.cpp, ServiceCenter.h,
Window.cpp, Window.h

References:
Suparna Pal - went to TA office hours
https://stackoverflow.com/questions/70614880/how-to-stop-infinite-looping-the-output
https://stackoverflow.com/questions/26661877/error-in-a-out-free-invalid-next-size-normal
https://www.w3schools.com/cpp/cpp_arrays_size.asp
https://cplusplus.com/forum/beginner/256567/
https://cplusplus.com/forum/general/122206/

Struggles:
One of the biggest struggles I had with this project was with allocating and deallocating memory. I learned that it is important to keep track of
what memory is stored where from what class, or else I will run into many segmentation faults and ./free() errors. Something new I learned was this
free(): invalid pointer error I was getting. This error occurs when you try to deallocate memory that is already deallocated somewhere else. This 
was especially a struggle when first figuring out because I did not make my Customer listnodes pointers. 

This application:
This application takes in an input file with data of students that are coming to the student service center, along with the number of windows to open
for each window. With this information, we send students to windows or waitlists based on the availabilities of the windows, and at the end, print out
the statistics for each window such as wait time, idle times, and mean wait times for students for a specific window. 


