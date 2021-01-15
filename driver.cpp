#include <iostream>
#include <memory>
// #include "bankDetails.h"
#include "simpleATM.h"
// #include <simpleATM>

using namespace std;

int main()
{
    // make dummy accounts for testing purposes
    make_dummy_accounts();

    // insert card => create simple atm instance
    shared_ptr<simpleATM> atmInstance (new simpleATM(1)); // let 1234 be the card serial number

    // enter pin and check against actual pin
    if (atmInstance -> pinCheck() == false)
    {
        cout << "Session terminated" << endl;
        return 0;
    }
    // if pin correct, moving ahead

    
    bool running = true;
    while (running)
    {
        // display all accounts, ask for a number like 1,2,3
        long accNo = atmInstance->accountSelection();
        while (accNo == 0)
        {
            accNo = atmInstance->accountSelection();
        }

        // ask for one of three methods, (perform validity checks of input just like above)
        int methodId = atmInstance->methodChoice();
        while (methodId == 0)
        {
            methodId = atmInstance->methodChoice();
        }

        // perform the transaction method (see balance, deposit or withdrawal)
        switch(methodId)
        {
            int amount;
            case(1): atmInstance->display(accNo); break;
            case(2): 
                    cout << "Please enter amount to withdraw" << endl;
                    cin >> amount;
                    atmInstance->withdraw(accNo, amount); break;
            case(3): 
                    cout << "Please enter amount to deposit" << endl;
                    cin >> amount;
                    atmInstance->deposit(accNo, amount); break;        
        }
        cout << "Transaction completed! Would you like to perform another transaction? " << endl << "yes/no?" << endl;
        string option;
        cin >> option;
        if (option == "no") running = false; 
    }   
    cout << "Have a nice day" << endl;
    return 0;
}