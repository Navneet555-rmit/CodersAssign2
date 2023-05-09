#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include "helper.h"
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
        else
        {
            throw std::runtime_error("Nothing to remove");
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

// void LinkedList::remove_index(int index)
// {
//     Node *prev = nullptr, *current;

//     if (index >= 0 && index < size())
//     {
//         if (head != nullptr)
//         {
//             int counter = 0;
//             Node *current = head;
//             // pre should point to node before current;
//             Node *prev = nullptr;

//             while (counter != index)
//             {
//                 ++counter;
//                 prev = current;
//                 current = current->next;
//             }

//             if (prev == nullptr)
//             {
//                 head = current->next;
//             }
//             else
//             {
//                 prev->next = current->next;
//             }

//             //delete current->card;
//             delete current;
//         }
//     }
// }

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
