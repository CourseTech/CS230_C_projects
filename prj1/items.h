#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef ITEMS_H
#define ITEMS_H

struct Node {
    char * item;
    struct Node* next;
};

// add to the linkedlist
void add_item(struct Node** node, char * data);

//delete item from the linkedlist
void drop_item(struct Node** node, char * data);

//search if an item exist or not
bool search(struct Node** node,char * data);


#endif