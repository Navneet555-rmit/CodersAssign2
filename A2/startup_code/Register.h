#ifndef REGISTER_H
#define REGISTER_H
#include <string>
#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "helper.h"
#include "Register.h"

using std::string;

class Register{
    private:

        int denominators[8]   = {5,10,20,50,100,200,500,1000};
        int amounts[8]        = {0,0,0,0,0,0,0,0};

    public:
        Register();
        ~Register();

        bool LoadRegister(string fileName);
        bool InsertCash(int denomination,int amount);
        int* GetChange(int amount);
        string DenomToString(int denomination);
};

#endif 
