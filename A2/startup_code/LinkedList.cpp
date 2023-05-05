#include "LinkedList.h"

#include "Node.h"
#include <iostream>
#include <string>
#include "helper.h"

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

int LinkedList::size() {
    return count;
}

Stock* LinkedList::get(int i) {
    Stock* lastNode = nullptr;

    if (i >= 0 && i < size()){

        int counter = 0;
        Node* current = head;

        while (counter < i){
            ++counter;
            current = current->next;
        }

        lastNode = current->data;
    }
    return lastNode;
}

LinkedList::~LinkedList() {
    // TODO
}
