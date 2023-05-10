#ifndef INVENTORY
#define INVENTORY
#include <string>
#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "helper.h"


using std::string;

class Inventory{
    private:
        LinkedList items;

    public:
        Inventory();
        ~Inventory();

        bool LoadItems(string file_name);
        bool AddItem(std::vector<std::string> data);
        void DisplayInventory();
        string getNextID();
        int getPosition(Stock* item);

};

#endif 
