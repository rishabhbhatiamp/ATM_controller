#include <iostream> 
// #include <bankAPI.cpp>
#include <vector>
#include "bankAPI.h"
#define PIN_THRESHOLD 3


using namespace std;

class simpleATM{
public:
    // members
    long cardSerial;

    //constructors
    simpleATM(long serialIn): cardSerial(serialIn) {};
    
    // member functions
    int getPin()
    {
        cout << "Enter pin number: " << endl;
        int pin;
        cin >> pin;
        return pin;
    }

    bool pinCheck()
    {
        int pinCount = 1;
        int pinIn = getPin();
        if (pinQuery(cardSerial, pinIn))
        {
            cout << "Pin verification successfull" << endl;
            return true;
        }
        while (!pinQuery(cardSerial, pinIn) and pinCount < PIN_THRESHOLD)
        {
            cout << "pinCount" << pinCount << endl;
            cout << "Incorrect Pin, you have " << PIN_THRESHOLD - pinCount << " tries left" << endl;
            ++pinCount;
            pinIn = getPin();
            if (pinQuery(cardSerial, pinIn))
            {
                cout << "Pin verification successfull" << endl;
                return true;
            }
        }
        cout << "You have exhausted the number of retries. Goodbye" << endl;
        return false;
    }

    long accountSelection()
    {
        // retrieve all accounts and display
        unordered_map<long,long> accs = getCarholderAccounts(cardSerial);
        cout << "Select one of the below accounts: " << endl;
        int count = 0;
        vector<long> tempAcc;
        for(auto& acc:accs)
        {
            cout << count+1 << ". " << acc.first << endl;
            tempAcc.push_back(acc.first);
            ++count;
        }
        int num;
        cin >> num;
        if (num > tempAcc.size())
        {
            cout << "Please enter a valid account option" << endl;
            return 0;
        }
        long id = tempAcc[num-1];
        return id;
    }

    int methodChoice()
    {
        cout << "What would you like to do today" << endl;
        cout << "1. See Balance" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Deposit Money" << endl << "Select by method number" << endl;
        int methodId;
        cin >> methodId;
        if (methodId > 3 or methodId < 1) 
        {
            cout << " Please enter a method number between 1 to 3" << endl;
            return 0;
        }
        return methodId;
    }

    void display(long accNo)
    {
        long balance = getBal(cardSerial, accNo);
        cout << " Your current balance is: " << balance << endl;
    }

    void withdraw(long accNo, long amountIn)
    {
        updateBal(cardSerial, accNo, -1*amountIn);
    }

    void deposit(long accNo, long amountIn)
    {
        updateBal(cardSerial, accNo, amountIn);
    }

};