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
    void remove_index(int index);

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


