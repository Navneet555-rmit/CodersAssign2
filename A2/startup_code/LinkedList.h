#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

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


