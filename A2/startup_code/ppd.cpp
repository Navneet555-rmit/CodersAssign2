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

using std::cin;
using std::string;
using std::vector;

std::map<int, Coin> cash_register;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/

const string menuText =
    "Main Menu\n"
    "   1.Display Items\n"
    "   2.Purchase Items\n"
    "   3.Save and Exit\n"
    "Administrator-Only Menu:\n"
    "   4.Add Item\n"
    "   5.Remove Item\n"
    "   6.Display Coins\n"
    "   7.Reset Stock\n"
    "   8.Reset Coins\n"
    "   9.Abort Program";
;
void checkUserInputForRemoveItem(string userInput)
{
    std::regex pattern("^I\\d{4}$");

    while (userInput == "")
    {
        std::cout << "Please input a valid answer" << std::endl;
        userInput = Helper::readInput();
    }
    // Matching regex and is not eof
    if (std::regex_match(userInput, pattern) && !cin.eof())
    {
        //linked_list->remove_index(3);
        std::cout << "hihih" << std::endl;
    } else {
        std::cout << "ID invalid or was not found" << std::endl;
    }
}

int main(int argc, char **argv)
{
    LinkedList *linked_list = new LinkedList();

    // Needs to check if there are exactly 3 lines of code or error

    if (argc == 3)
    {
        std::ifstream file1(argv[1]);
        if (!file1)
        {
            std::cerr << "Failed to open stock.dat" << std::endl;
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
                // file_error = !items.insert(tokens);
                file_error = !linked_list->insert(tokens);
            }
            else
            {
                file_error = true;
            }

            if (file_error)
            {
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
            if (tokens.size() == 2)
            {

                Coin new_denom = *(new Coin());
                cash_register.insert(std::make_pair(std::stoi(tokens[0]), new_denom));
            }
        }
    }
    else if (argc != 3)
    {
        std::cerr << "Too many OR invalid arguments" << std::endl;
    }

    std::cout << menuText << std::endl;
    while (true)
    {
        std::cout << "\nSelect your option (1-9):";
        string input = Helper::readInput();

        if (input == "1")
        {
        }
        else if (input == "2")
        {
        }
        else if (input == "3")
        {
        }
        else if (input == "4")
        {
        }
        else if (input == "5")
        {
            std::cout << "Please select the item you want to remove" << std::endl;

            string userInput = Helper::readInput();

            checkUserInputForRemoveItem(userInput);

            
        }
    }

    delete linked_list;
    linked_list = nullptr;
        
    return EXIT_SUCCESS;
}
