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
#include <regex>
#include "CashRegister.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

std::map<int, Coin> cash_register;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/

const string menuText =
    "\nMain Menu\n"
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
    CashRegister *cash_register = new CashRegister();
    LinkedList *linked_list = new LinkedList();

    // Needs to check if there are exactly 3 lines of code or error
    if (argc != 3)
    {
        return EXIT_FAILURE;
    }
    if (argc == 3)
    {

        std::ifstream file1(argv[1]);
        if (!file1)
        {
            std::cerr << "Failed to open stock.dat" << endl;
            return EXIT_FAILURE;
        }

        std::string line;
        while (std::getline(file1, line))
        {

            bool file_error = false;
            std::vector<std::string> tokens = {};
            Helper::splitString(line, tokens, "|");

            if (tokens.size() == 5)
            {
                file_error = !linked_list->insert(tokens);
            }
            else
            {
                file_error = true;
            }

            if (file_error)
            {
                cout << "file error" << endl;
                return EXIT_FAILURE;
            }
        }

        std::ifstream file2(argv[2]);
        if (!file2)
        {
            std::cerr << "Failed to open coin.dat" << endl;
            return EXIT_FAILURE;
        }

        cash_register->LoadRegister(argv[2]);
    }

    bool quitProgram = false;
    while (!quitProgram)
    {
        cout << menuText << endl;
        cout << "\nSelect your option (1-9): ";
        vector<string> tokens = {};
        string input = Helper::readInput();
        Helper::splitString(input, tokens, " ");

        if (tokens.size() == 0) {
            quitProgram = true;
        }

        else if (tokens.size() == 1 && tokens[0] == "1")
        {
            linked_list->DisplayItems();
        }
        else if (tokens.size() == 1 && tokens[0] == "2")
        {
            // Purchasing
            cout << "Purchase Item" << endl;
            cout << "-------------" << endl;
            cout << "Please enter the id of the item you wish to purchase: ";

            // imma do the user validation stuff later (similar to option 5)
            string userInput = Helper::readInput();

            linked_list->BuyItem(userInput, *cash_register);
        }
        else if (tokens.size() == 1 && tokens[0] == "3")
        {
            quitProgram = true;
        }
        else if (tokens.size() == 1 && tokens[0] == "4")
        {
            // Get the next ID for the new item
            string ID = linked_list->getNextID();
            cout << "The id of the new stock will be: " << ID << endl;
            // Initalize variables
            bool success = false;

            while (!success) {
                // Get input from user
                cout << "Enter the item name: ";
                string itemName = Helper::readInput();
                Helper::splitString(itemName, tokens, ".");
                // If user input is whitespace, cancel add task
                if (tokens.size() == 0) {
                    success = true;
                    Helper::cancelAddTask();
               /*
                * If length of input is above maximum length,
                * alert user that the input is too long
                */ 
                } else if (itemName.length() > NAMELEN) {
                    Helper::printLongInput();
                } else {
                     // Get input from user
                    cout << "Enter the item description: ";
                    string itemDesc = Helper::readInput();
                    Helper::splitString(itemDesc, tokens, ".");
                    // If user input is whitespace, cancel add task
                    if (tokens.size() == 0) {
                        success = true;
                        Helper::cancelAddTask();
                   /*
                    * If length of input is above maximum length,
                    * alert user that the input is too long
                    */ 
                    } else if (itemDesc.length() > DESCLEN) {
                        Helper::printLongInput();
                    } else {
                        bool priceSuccess = false;
                        while (priceSuccess == false) {
                            // Get input from user
                            cout << "Enter the item price: ";
                            string itemPrice = Helper::readInput();
                            Helper::splitString(itemPrice, tokens, ".");
                            // If user input is whitespace, cancel add task
                            if (tokens.size() == 0) {
                                priceSuccess = true;
                                success = true;
                                Helper::cancelAddTask();
                            // Check if input has two strings separated by "."
                            } else if (tokens.size() == 2) {
                                // Check if the two strings are numbers
                                if (Helper::isNumber(tokens[0]) == true && 
                                Helper::isNumber(tokens[1]) == true) {
                                    // Check if the second string is divisible by 5
                                    if (stoi(tokens[1]) % 5 == 0) {
                                        // Create vector containing the new item's details
                                        vector<string> data = Helper::createVector(
                                        ID, itemName, itemDesc, itemPrice);
                                        // Add item to inventory
                                        linked_list->insert(data);
                                        cout << "This item " << "\"" << itemName
                                        << " - " << itemDesc << "\" has now " <<
                                        "been added to the menu.\n";
                                        priceSuccess = true;
                                        success = true;
                                    } else {
                                       /*
                                        * If second string (cents) is not divisible
                                        * by 5, alert user
                                        */ 
                                        Helper::printCentsNotMultipleOf5();
                                    }
                                // If either string is not a number, alert user
                                } else {
                                    Helper::printInvalidPrice();
                                }
                            // If input is not two strings separated by ".", alert user
                            } else {
                                Helper::printInvalidPrice();
                            }
                        }
                    }
                    
                }
                
            }
        }
        else if (tokens.size() == 1 && tokens[0] == "5")
        {
            std::cout << "Please select the item you want to remove" << std::endl;

            string userInput = Helper::readInput();

            if (!cin.eof())
            {
                if (Helper::checkUserInputForRemoveItem(userInput))
                {
                    linked_list->remove_index(userInput);
                }
            }
        }
        else if (tokens.size() == 1 && tokens[0]  == "6")
        {
            cash_register->display_coins();
        }

        else if (tokens.size() == 1 && tokens[0]  == "7") {
            linked_list->resetStock();
            std::cout << "All stock has been reset to the default level of "
            << DEFAULT_STOCK_LEVEL;
        }

        else if (tokens.size() == 1 && tokens[0]  == "9") {
            quitProgram = true;
        }
        else {
            if (tokens.size() >= 2 || Helper::isNumber(tokens[0]) == false) {
                Helper::printInputNotNumber();
            } else {
                Helper::printInvalidInput();
            }
        }
    }

    delete linked_list;
    linked_list = nullptr;

    return EXIT_SUCCESS;
}
