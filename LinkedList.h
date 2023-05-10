#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

#include <string>
#include <string.h>

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>

using std::string;
using std::vector;


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    int size();

    bool insert(std::vector<std::string> data);
    string toString();
    void remove_index(string index);

    // Inserting stock from file reference: https://github.com/Py-Contributors/AlgorithmsAndDataStructure/blob/master/C%2B%2B/Data%20Structure/Linked%20List/Menu_Driven_Linked_List.cpp
    void insert_stock_from_file(string filepath);
    void DisplayItems();
private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


