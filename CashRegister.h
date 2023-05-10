#ifndef CASHREGISTER_H
#define CASHREGISTER_H
#include <string>
#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "helper.h"


using std::string;

class CashRegister{
    private:

        int denominators[8]   = {5,10,20,50,100,200,500,1000};
        int amounts[8]        = {0,0,0,0,0,0,0,0};

        // i hate u
        std::vector<Coin*> coins;

    public:
        CashRegister();
        ~CashRegister();

        void Load_file_coins(string filepath);

        bool LoadRegister(string fileName);

        bool InsertCash(int denomination,int amount);
        int* GetChange(int amount);
        string DenomToString(int denomination);

        int coin_file_to_denomation(Denomination file_denom);

        void display_coins();
};

#endif 