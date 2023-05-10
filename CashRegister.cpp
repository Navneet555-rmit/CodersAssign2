#include "CashRegister.h"
#include "LinkedList.h"
#include <iomanip>

using std::cout;
CashRegister::CashRegister()
{
    // stupid bullshit caused out of range segmentation cuz i didnt give it size AAAAAAAAAHHHHHHHH
    // reference: https://stackoverflow.com/questions/22067705/c-vector-stdout-of-range-error i love u
    this->coins.resize(8);
}
CashRegister::~CashRegister()
{
}

void CashRegister::Load_file_coins(string filepath)
{
}

int CashRegister::coin_file_to_denomation(Denomination file_denom) {
    int index = 0;

    if(file_denom == 10){
        index = 1;
    }else if(file_denom == 20){
        index = 2;
    }else if(file_denom == 50){
        index = 3;
    }else if(file_denom == 100){
        index = 4;
    }else if(file_denom == 200){
        index = 5;
    }else if(file_denom == 500){
        index = 6;
    }else if(file_denom == 1000){
        index = 7;
    }  

    std::cout <<  "it do be working in coins in cash register"  << std::endl;
    std::cout << index << std::endl;
    return index;
}

bool CashRegister::LoadRegister(string file_name)
{
    std::ifstream coins_file(file_name);

    std::string line;
    vector<string> coins_output;

    if (!coins_file)
    {
        std::cout << file_name << " : "
                  << "fail to open file" << std::endl;
        return false;
    }

    while (std::getline(coins_file, line))
    {
        // Initialize the vector with the required number of elements
        std::vector<Coin*> ret(8);

        Helper::splitString(line, coins_output, ",");

        if (coins_output.size() >= 2)
        {
            // Getting the coins
            std::string coin_denom = coins_output[0];
            std::string coin_value = coins_output[1];

            // Checks if the denom and value are numbers
            if (Helper::isNumber(coin_value) && Helper::isNumber(coin_denom))
            {
                if (!this->InsertCash(std::stoi(coins_output[0]), std::stoi(coins_output[1])))
                {
                }

                // the denom values are stripped of spaces
                coins_output[0] = Helper::strip_spaces(coins_output.at(0));

                // turns the values into enums for the denomination
                Denomination denomination = Coin::coin_file_to_denomation(stoi(coins_output.at(0)));
                 
                // makes the index of the coins
                int index_coin = coin_file_to_denomation(denomination);
               
                // makes new coin (the denomination, the value)
                Coin *coin_ptr = new Coin(denomination, std::stoi(coins_output.at(1)));
                 
                // this line sets the Coin object pointed to by coin_ptr to the index_coin-th position of the coins vector using the at() function
                this->coins.at(index_coin) = coin_ptr;
                
                
            }
            else
            {
                std::cout << file_name << " : "
                          << "nots a number" << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << file_name << " : "
                      << "coins_output.size()!=2" << std::endl;
            return false;
        }
    }
    return true;
}

bool CashRegister::InsertCash(int denomination, int amount)
{
    for (int i = 0; i < 8; i++)
    {
        if (denominators[i] == denomination)
        {
            amounts[i] += amount;
            return true;
        }
    }
    return false;
}

// reference: chatgpt helped with this part
void CashRegister::display_coins() {
    cout << "Coins Summary" << std::endl;
    cout << "---------------" << std::endl;
    cout << "Denomination     |     Count" << std::endl;
    cout << "-----------------------------" << std::endl;
    
    for (const auto& coin : this->coins) {
        string denom_str;
        if (coin->denom % 100 != 0) {
            denom_str = std::to_string(coin->denom) + " Cents";
        } else {
            denom_str = std::to_string(coin->denom / 100) + " Dollars";
        }
        
        cout << std::left << std::setw(18) << denom_str << "| " << std::right << std::setw(9) << coin->count << std::endl;
    }
}