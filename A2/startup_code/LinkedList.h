#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

#include <string.h>
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

    bool insert(std::vector<std::string> data);
    void DisplayItems();
    std::string toString();
    
    int size();
    void clear();
    int get(int i);

    void addFront(int data);
    void addBack(int data);
    
    void deleteFront();
    void deleteBack();

    void addAt(int i);
    void deleteAt(int i);

    
    // more functions to be added perhaps...

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


