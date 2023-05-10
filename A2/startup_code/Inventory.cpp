#include "Inventory.h"

#include <iostream>
#include "helper.h"
#include <iomanip>

using std::string;
using std::vector;

Inventory::Inventory() {
    items = *new LinkedList();

}

Inventory::~Inventory() {
    // TODO
}

bool Inventory::LoadItems(string file_name){
        std::ifstream stock_file(file_name);
        if (!stock_file)
        {
            std::cout << file_name << " : " << "file error" << std::endl;
            return false;
        }


        std::string line;
        while (std::getline(stock_file, line))
        { 
    
            std::vector<std::string> tokens = {};
            Helper::splitString(line, tokens, "|");

            if (tokens.size() == 5){
                if (!this->AddItem(tokens)){
                    std::cout << file_name << " : " << "could not insert" << std::endl;
                }
            }else{
                std::cout << file_name << " : " << "tokens.size() != 5" << std::endl;
            }

        }

        return true;
}
void Inventory::DisplayInventory(){
    std::cout 
    << "Items Menu\n" 
    << "----------\n" 
    << std::left << std::setw(40) << "ID   |Name"
    << std::left << std::setw(15) <<"| Available"
    << "| Price \n"
     << "---------------------------------------------------------------" 
    << std::endl;
 
    Node* current = this->items.Peek();
 
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
        << "|$ "+std::to_string(data->price.dollars) +"."+cents_str
        << std::endl;
 
 
        current = current->next;
    }
}

bool Inventory::AddItem(std::vector<std::string> data){

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

    items.Insert(new_stock);

    return true;

}

string Inventory::getNextID() {
    Node* current = this->items.Peek();
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

int Inventory::getPosition(Stock* item) {
    int index = 0;
    Node* current = this->items.Peek();
    std::string itemName = item->name;
    std::string currentItemName = current->data->name;
    itemName[0] = std::toupper(itemName[0]);
    currentItemName[0] = std::toupper(currentItemName[0]);
    // std::cout << current->data->name << std::endl;
    while (current->next != nullptr && currentItemName < itemName) {
        current = current->next;
        currentItemName = current->data->name;
        currentItemName[0] = std::toupper(currentItemName[0]);
        // std::cout << current->data->name << std::endl;
        index += 1;
    }
    return index;
}






