#include <iostream>
#include <array>
#include <memory>
#include "bankDetails.h"

#define CARDHOLDERS_CAPACITY 10

std::shared_ptr<std::array<cardholder,CARDHOLDERS_CAPACITY> > bankAccounts (new std::array<cardholder,CARDHOLDERS_CAPACITY>);

void make_dummy_accounts(){
    *bankAccounts = 
    {{
        {1, "Holder 1", 1111, { {1231, 599}, {1232, 346}, {1233, 530} } }, 
        {2, "Holder 2", 2222, { {4561, 345}, {4562, 578}, {4563, 405} } },
        {3, "Holder 3", 3333, { {7891, 157}, {7892, 234}, {7893, 846} } },
    }};
}

std::shared_ptr<cardholder> getCardholder(long cardSerialIn){
    for (auto& acc:*bankAccounts)
    {
        if (acc.cardSerial == cardSerialIn)
        {
            std::shared_ptr<cardholder> temp (new cardholder(acc));
            return temp;
        }
    }
}

bool pinQuery(long cardSerialIn, int pinIn){
    auto currAcc = getCardholder(cardSerialIn);
    if (currAcc->pin == pinIn){
        return true;
    }
    return false;
}


std::unordered_map<long,long> getCarholderAccounts(long cardSerialIn)
{
    auto currAcc = getCardholder(cardSerialIn);
    return currAcc->accounts;
}

long getBal(long cardSerialIn, long accNoIn)
{
    auto currAcc = getCardholder(cardSerialIn);
    return currAcc->accounts[accNoIn];
}

void updateBal(long cardSerialIn, long accNoIn, long amountIn)
{
    for(auto& acc: *bankAccounts){
        if (acc.cardSerial == cardSerialIn)
        {
            std::cout << "Amount before transaction: " << acc.accounts[accNoIn] << std::endl;
            acc.accounts[accNoIn] += amountIn;
            std::cout << "Amount after transaction: " << acc.accounts[accNoIn] << std::endl;
        }
    }
}