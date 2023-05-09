#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "helper.h"
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <string.h>
#include <random>
#include "Register.h"
#include "Inventory.h"

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;


/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/


#define RANGE_ADMIN 9
#define RANGE_CUST 3

Register cashRegister;
Inventory inventory;

bool isAdmin = true;

const string MENU_CUST =
    "Main Menu\n"
    "   1.Display Items\n"
    "   2.Purchase Items\n"
    "   3.Save and Exit\n"
    ;

const string MENU_ADMIN =
    MENU_CUST+
    "Administrator-Only Menu:\n"
    "   4.Add Item\n"
    "   5.Remove Item\n"
    "   6.Display Coins\n"
    "   7.Reset Stock\n"
    "   8.Reset Coins\n"
    "   9.Abort Program\n"
    ;

void Menu(){
    bool show_menu = true;
    while(true){
        
        if (show_menu){
            if (isAdmin)
                std::cout << MENU_ADMIN;
        }
            else{
                std::cout << MENU_CUST;
            }
    
       
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
        else if (input == "4" && isAdmin)
        {
        }
        else if (input == "5" && isAdmin)
        {

        }
        else if (input == "6" && isAdmin)
        {

        }
        else if (input == "7" && isAdmin)
        {

        }
        else if (input == "8" && isAdmin)
        {

        }
        else if (input == "9" && isAdmin)
        {

        }
        else{
            show_menu = false;
        }


    }
}



int main(int argc, char **argv)
{

    if (argc == 3){
        cashRegister = *new Register();
        inventory = *new Inventory();

        if (!(inventory.LoadItems(argv[1]) && cashRegister.LoadRegister(argv[2]))){
            return EXIT_FAILURE;
        }
    }

   Menu();

    return EXIT_SUCCESS;
}