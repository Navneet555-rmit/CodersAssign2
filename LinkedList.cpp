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

void insert_stock_from_file(string filepath)
{
    // getting the data from filepath
    ifstream stock(filepath);

    // read the database until EOF
    while (!stock.eof())
    {
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
    std::cout << "Check 0" << std::endl;

    Node *current = this->head;
    Node *prev = nullptr;

    size_t counter_remove = 0;

    std::cout << "Check 1" << std::endl;

    if (this->head == nullptr)
    {
        std::cout << "List is empty!" << std::endl;
        return;
    }

    // Going through the node until the ID is found
    // Errors here - Issues in loop when theres an item that doesn't exist
    while ( counter_remove < this->count  && current->data->id != index)
    {
        std::cout << "Check 1.2" << std::endl;
        prev = current;
        current = current->next;
        counter_remove = counter_remove + 1;
        std::cout << "Check 2" << std::endl;
    }
    std::cout << "Check 2.2" << std::endl;
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
    std::cout << "Check 3" << std::endl;

    // Delete children and then parent
    delete current->data;
    delete current;
}

void LinkedList::DisplayItems(){
    std::cout 
    << "Items Menu\n" 
    << "----------\n" 
    << std::left << std::setw(40) << "ID   |Name"
    << std::left << std::setw(15) <<"| Available"
    << "| Price \n"
     << "---------------------------------------------------------------" 
    << std::endl;
 
    Node* current = head;
 
    while (current) {
        Stock *data = current->data;
 
        int cents = data->price.cents;
        std::string cents_str = std::to_string(cents);
        if (cents < 10) {
            cents_str.insert(0, "0");
        }
 
        std::cout 
        << std::left << std::setw(40) << data->id +"|"+ data->name
        << std::left << std::setw(15) <<"|"+std::to_string(data->on_hand)
        << "|$ "+std::to_string(data->price.dollars) +"." + cents_str
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
