#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include "helper.h"
#include <fstream>
#include <iomanip>
using std::ifstream;
using std::string;
using std::vector;

#include <string>

// constructer, initilialzing head pointer to null and count to 0
LinkedList::LinkedList()
{
    this->head = nullptr;
    this->count = 0;
}

// Deconstructer, freeing up memory
LinkedList::~LinkedList()
{
    Node *head = this->head;
    while (head != nullptr)
    {
        if (head != nullptr)
        {
            Node *toDelete = head;
            head = head->next;

            delete toDelete;
            toDelete = nullptr;
        }
    }
}

bool LinkedList::insert(std::vector<std::string> data)
{

    std::vector<std::string> price_tokens = {};
    Helper::splitString(data[3], price_tokens, ".");

    if (price_tokens.size() != 2)
    {
        std::cout << "Price Error" << std::endl;
        return false;
    }

    Price price = *(new Price());
    price.dollars = std::stoi(price_tokens[0]);
    price.cents = std::stoi(price_tokens[1]);

    Stock *new_stock = new Stock();
    new_stock->id = data[0];
    new_stock->name = data[1];
    new_stock->description = data[2];
    new_stock->on_hand = std::stoi(data[4]);
    new_stock->price = price;

    Node *new_node = new Node();
    new_node->data = new_stock;

    Node *current = head;
    Node *prev = nullptr;

    while (current != nullptr && current->data->name < new_stock->name)
    {
        prev = current;
        current = current->next;
    }

    if (prev == nullptr)
    {
        new_node->next = head;
        head = new_node;
    }
    else
    {
        prev->next = new_node;
        new_node->next = current;
    }

    count += 1;
    return true;
}

string LinkedList::toString()
{
    string new_string = "";
    Node *current = head;

    while (current)
    {
        Stock *data = current->data;
        new_string = new_string + "\n" +
                     data->id + "|" + data->name + "\t\t\t\t" + "|" + std::to_string(data->on_hand) + "$ " + std::to_string(data->price.dollars) + "." + std::to_string(data->price.cents);

        current = current->next;
    }
    return new_string;
}

void LinkedList::remove_index(string index)
{

    Node *current = this->head;
    Node *prev = nullptr;
    bool notFound = false;
    size_t counter_remove = 0;

    if (this->head == nullptr)
    {

        return;
    }

    // Going through the node until the ID is found
    // Errors here - Issues in loop when theres an item that doesn't exist
    while (counter_remove < this->count && current->data->id != index && !notFound)
    {
        prev = current;
        current = current->next;

        if (current == nullptr)
        {
            std::cout << "ID does not exist" << std::endl;

            current = nullptr;
            notFound = true;
        }

        counter_remove = counter_remove + 1;
       
    }

    if (!notFound)
    {
        std::cout << "A" << std::endl;
        // If the node is in the beginning
        if (prev == nullptr)
        {
            this->head = current->next;
            std::cout << "" << current->data->id << " | " << current->data->name << " | " << current->data->description << " has been removed from the system." << std::endl;
            this->count--;
        }

        // If the node is in the middle (checking if index is inside the count)
        else if (counter_remove < this->count)
        {
            prev->next = current->next;
            std::cout << "" << current->data->id << " | " << current->data->name << " | " << current->data->description << " has been removed from the system." << std::endl;
        }
        else
        {
            std::cout << "ID was not found" << std::endl;
        }
    }
   
    // Delete children and then parent
    //delete current->data;
    //delete current;
}

void LinkedList::DisplayItems()
{
    std::cout
        << "Items Menu\n"
        << "----------\n"
        << std::left << std::setw(40) << "ID   |Name"
        << std::left << std::setw(15) << "| Available"
        << "| Price \n"
        << "---------------------------------------------------------------"
        << std::endl;

    Node *current = head;

    while (current)
    {
        Stock *data = current->data;

        int cents = data->price.cents;
        std::string cents_str = std::to_string(cents);
        if (cents < 10)
        {
            cents_str.insert(0, "0");
        }

        std::cout
            << std::left << std::setw(40) << data->id + "|" + data->name
            << std::left << std::setw(15) << "|" + std::to_string(data->on_hand)
            << "|$ " + std::to_string(data->price.dollars) + "." + cents_str
            << std::endl;

        current = current->next;
    }
}

int LinkedList::size()
{
    int length = 0;

    Node *current = head;
    while (current != nullptr)
    {
        ++length;
        current = current->next;
    }
    return length;
}

void LinkedList::BuyItem(string userInput, CashRegister cash_register)
{
    Node *selected_node = nullptr;

    selected_node = getID(userInput);

    bool gave_money = false;
    int cash_owed = 0;

    if (selected_node == nullptr)
    {
        std::cout << "Item not found! ;-;" << std::endl;
    }
    // If item was found
    else
    {
        // If theres no stock of item
        if (selected_node->data->on_hand <= 0)
        {
            std::cout << "Item out of stock! ;-;" << std::endl;
        }
        // If theres stock of item
        else
        {

            // gonna make it so that it gets the first 7 letters and last 7 letters and leave ... in middle
            std::cout << "You have selected "
                      << selected_node->data->description
                      << ". This will cost you $ " << std::to_string(selected_node->data->price.dollars)
                      << "." << std::to_string(selected_node->data->price.cents)
                      << std::endl;

            std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
            std::cout << "Press enter or ctrl-d on a new line to cancel this purchase:" << std::endl;

            cash_owed = selected_node->data->price.dollars * 100;
            cash_owed = cash_owed + selected_node->data->price.cents;

            while (!gave_money)
            {
                std::cout << "You still need to give us "
                          << std::to_string(cash_owed)
                          << ":" << std::endl;

                string userInput_change = Helper::readInput();

                // user validations to check if digit, valid denom etc etc
                // bool check if valid denom, if false Error: $3.00 is not a valid denomination of money. Please try again
                // bool check if is digit, if false Error: hi is not a valid number
                // check of eof

                cash_owed = cash_owed - stoi(userInput_change);

                // Handed direct change
                if (cash_owed == 0)
                {
                    std::cout << "Here is your " << selected_node->data->name << std::endl;
                    gave_money = true;
                }
                // Customer needs change back
                else if (cash_owed < 0)
                {
                    std::cout << "Here is your " << selected_node->data->name << std::endl;
                    std::cout << "Here is your change " << std::endl;

                    // make function to deal with change and stuff
                    // like getChange()
                    // then that function can deal removing it from coin vector
                    // if it cant get change, it will print out saying sorry no change and refund items
                    // once everything is done, we finally remove the item quantity
                    gave_money = true;
                }
            }
        }
    }
}

// Reference: Week 7 notes
// https://stackoverflow.com/questions/45273207/string-searching-in-linked-list-by-c
Node *LinkedList::getID(string index)
{
    Node *ret_item = nullptr;
    Node *head = this->head;

    unsigned counter = 0;

    if (head == nullptr)
    {
        std::cout << "List is empty!" << std::endl;
    }
    else
    {
        while (counter < count)
        {
            if (head->data->id == index)
            {
                ret_item = head;

                // Breaking out of loop
                counter = count + 1;
            }
            head = head->next;
            counter++;
        }
    }

    return ret_item;
}