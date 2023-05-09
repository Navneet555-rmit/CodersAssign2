#include "LinkedList.h"

#include "Node.h"
#include <iostream>
#include <string>
#include "helper.h"
#include <iomanip>

using std::string;
using std::vector;

LinkedList::LinkedList() {
   head = nullptr;
   count = 0;

}

bool LinkedList::insert(std::vector<std::string> data){

    std::vector<std::string> price_tokens = {};
    Helper::splitString(data[3], price_tokens, ".");

    if (price_tokens.size() != 2){
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

 
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr  && current->data->name < new_stock->name) {
        prev = current;
        current = current->next;
    }

    if (prev == nullptr){
        new_node->next = head;
        head = new_node;
    }else{
        prev->next = new_node;
        new_node->next = current;
    }


    count += 1;
    return true;
}

string LinkedList::toString(){
    string new_string = "";
    Node* current = head;

    while (current) {
        Stock *data = current->data;
        new_string = new_string+ "\n"+
        data->id
        +"|"+data->name
        +"\t\t\t\t"
        +"|"+std::to_string(data->on_hand)
        +"$ "+std::to_string(data->price.dollars) +"."+std::to_string(data->price.cents);
        

        current = current->next;
    }
    return new_string;
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

LinkedList::~LinkedList() {
    // TODO
}
