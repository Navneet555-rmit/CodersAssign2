#include <iostream>

#include <fstream>
#include "LinkedList.h"
#include "helper.h"

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>
#include <map>


using std::string;
using std::vector;

LinkedList items;
std::map<int, Coin> cash_register;


/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

 const string menuText = 
                "Main Menu\n"
                "        1. Display Items\n"
                "        2. Purchase Items\n"
                "        3. Save and Exit\n"
                "Administrator-Only Menu:\n"
                "        4. Add Item\n"
                "        5. Remove Item\n"
                "        6. Display Coins\n"
                "        7. Reset Stock\n"
                "        8. Reset Coins\n"
                "        9. Abort Program";
                ; 


int main(int argc, char **argv)
{
    
    if (argc == 3){
        std::ifstream file1(argv[1]);
        if (!file1)
        {
            std::cerr << "Failed to open stock.dat" << std::endl;
            return EXIT_FAILURE;
        }

        items = *(new LinkedList());

        std::string line;
        while (std::getline(file1, line))
        { 
            bool file_error = false;
            std::vector<std::string> tokens = {};
            Helper::splitString(line, tokens, "|");

            if (tokens.size() == 5){
                file_error = !items.insert(tokens);
            }else{
                file_error = true;
            }

            if (file_error){
                std::cout << "file error" << std::endl;
                 return EXIT_FAILURE;
            }
        }

        std::ifstream file2(argv[2]);
        if (!file2)
        {
            std::cerr << "Failed to open coin.dat" << std::endl;
            return EXIT_FAILURE;
        }


        while (std::getline(file2, line))
        { 
            std::vector<std::string> tokens = {};
            Helper::splitString(line, tokens, ",");
            if (tokens.size()==2){

                Coin new_denom = *(new Coin());
                cash_register.insert(std::make_pair(std::stoi(tokens[0]),new_denom));
            }

        }
    }

    std::cout << menuText << std::endl;
    vector<string> tokens = {};
    while (true) {
        std::cout << "\nSelect your option (1-9): ";
        string input  = Helper::readInput();

        if (input == "1")
        {

        }
        else if (input == "2")
        {

        }
        else if (input == "3")
        {      
            return EXIT_SUCCESS;
        }
        else if (input == "4")
        {
            std::string ID = items.getNextID();
            std::cout << "The id of the new stock will be: " << ID << std::endl;
            std::cout << "Enter the item name: ";
            std::string itemName = Helper::readInput();
            std::cout << "Enter the item description: ";
            std::string itemDesc = Helper::readInput();
            bool validPrice = false;
            while (validPrice == false) {
                std::cout << "Enter the item price: ";
                std::string inputPrice = Helper::readInput();
                Helper::splitString(inputPrice, tokens, ".");
                if (tokens.size() == 2) {
                    if (Helper::isNumber(tokens[0]) == true && 
                    Helper::isNumber(tokens[1]) == true) {
                        Price* itemPrice = new Price();
                        itemPrice->dollars = stoi(tokens[0]);
                        itemPrice->cents = stoi(tokens[1]);
                        Stock* newItem = new Stock();
                        newItem->id = ID;
                        newItem->name = itemName;
                        newItem->description = itemDesc;
                        newItem->price = *itemPrice;
                        newItem->on_hand = DEFAULT_STOCK_LEVEL;
                        int index = items.getPosition(newItem);
                        items.addAtPosition(newItem, index);
                        std::cout << index;
                        std::cout << "This item " << "\"" << itemName << " - "
                        << itemDesc << "\" has now been added to the menu.\n";
                        validPrice = true;
                    } else {
                        std::cout << "Error: the price is not valid.\n";
                    }
                } else {
                    std::cout << "Error: the price is not valid.\n";
                }
            }
        }
        else if (input == "5")
        {
            

        }
        else{

        }
    }

}
