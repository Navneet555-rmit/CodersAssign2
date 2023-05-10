#include "Coin.h"
#include <iostream>
#include <map>
#include "Coin.h"

Coin::Coin()
{
}

// This is the constructer of the coin
Coin::Coin(Denomination denom, unsigned count) {
    this->denom = denom;
    this->count = count;

    //Coin::print();
}

void Coin::print(){
    std::cout << "Denomination: " << this->denom << std::endl;
    std::cout << "Count: " << this->count << std::endl; 
}

Denomination Coin::coin_file_to_denomation(unsigned file_denom)
{
    Denomination denomination = Denomination(FIVE_CENTS);

    if (file_denom == 10)
    {
        denomination = TEN_CENTS;
    }
    else if (file_denom == 20)
    {
        denomination = TWENTY_CENTS;
    }
    else if (file_denom == 50)
    {
        denomination = FIFTY_CENTS;
    }
    else if (file_denom == 100)
    {
        denomination = ONE_DOLLAR;
    }
    else if (file_denom == 200)
    {
        denomination = TWO_DOLLARS;
    }
    else if (file_denom == 500)
    {
        denomination = FIVE_DOLLARS;
    }
    else if (file_denom == 1000)
    {
        denomination = TEN_DOLLARS;
    }
    std::cout << denomination << std::endl;
    return denomination;
}