#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include "helper.h"
#include <iomanip>

#include <string>

using std::string;
using std::vector;

 

// constructer, initilialzing head pointer to null and count to 0
LinkedList::LinkedList()
{
    this->head = nullptr;
    this->count = 0;
}

// Deconstructer, freeing up memory
LinkedList::~LinkedList(){
   //
}

bool LinkedList::Insert(Stock* new_stock){


    Node  *new_node = new Node();
    new_node->data = new_stock;


    Node *current = head;
    Node *prev = nullptr;

    while (current != nullptr && current->data->name < new_stock->name) {
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

Node* LinkedList::Peek(){
    return head;
}