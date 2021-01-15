#pragma once
#include <string>
#include <unordered_map>

struct cardholder
{
    long cardSerial;
    std::string name;
    int pin;
    std::unordered_map<long,long> accounts;
};
