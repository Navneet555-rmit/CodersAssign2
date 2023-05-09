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

string LinkedList::getNextID() {
    Node* current = head;
    std::string currentItem = current->data->id;
    std::string nextItem = "";
    int currentID = std::stoi(currentItem.substr(1));
    int nextID = 0;
    while (current->next != NULL) {
        current = current->next;
        nextItem = current->data->id;
        nextID = std::stoi(nextItem.substr(1));
        if (nextID > currentID) {
            currentID = nextID;
            currentItem = nextItem;
        }
    }
    currentID += 1;
    std::string newID = "I" + std::to_string(currentID);
    int numOfDigits = 0;
    while (currentID != 0) {
        currentID = currentID / 10;
        numOfDigits += 1;
    }
    int i = 1;
    while (i != IDLEN-numOfDigits) {
        newID.insert(1, "0");
        i += 1;
    }
    return newID;
}
   

int LinkedList::getPosition(Stock* item) {
    int index = 0;
    Node* current = head;
    std::string itemName = item->name;
    std::string currentItemName = current->data->name;
    itemName[0] = std::toupper(itemName[0]);
    currentItemName[0] = std::toupper(currentItemName[0]);
    std::cout << current->data->name << std::endl;
    while (current->next != nullptr && currentItemName < itemName) {
        current = current->next;
        currentItemName = current->data->name;
        currentItemName[0] = std::toupper(currentItemName[0]);
        std::cout << current->data->name << std::endl;
        index += 1;
    }
    return index;
}

void LinkedList::addAtPosition(Stock* item, int position) {
    Node* current = head;
    Node* prev = nullptr;
    int i = 0;
    while (i < position) {
        i += 1;
        prev = current;
        current = current->next;
    }
    if (i == 0) {
        Node* newItem = new Node();
        newItem->data = item;
        newItem->next = head;
        head = newItem;
        count += 1;
    } else if (current->next == nullptr) {
        Node* newItem = new Node();
        newItem->data = item;
        newItem->next = nullptr;
        current->next = newItem;
        count += 1;
    } else {
        Node* newItem = new Node();
        newItem->data = item;
        prev->next = newItem;
        newItem->next = current;
        count += 1;
    }
}

LinkedList::~LinkedList() {
    // TODO
}
