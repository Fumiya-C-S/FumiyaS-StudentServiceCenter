#include "ServiceCenter.h"

int main(int argc, char const *argv[])
{
    ServiceCenter *mySerCen = new ServiceCenter; //create Service Center class

    try{ //try the following code
        mySerCen->processFile(argv[1]); //processFile from second string in command line argument
    }
    catch(runtime_error &excpt){ //if an error is thrown
        cout << excpt.what() << endl;  //print the error
    }
    
    delete mySerCen; //garbage collect
    return 0;
}
