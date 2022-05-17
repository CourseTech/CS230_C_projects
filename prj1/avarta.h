#include <stdio.h>
#include "items.h"
#include "rooms.h"

#ifndef AVARTA_H
#define AVARTA_H

struct Avatar{
    char * name;
    struct Node * backpack;
    struct Room * location;
};

// return: a Node* representing the backpack of the Avatar
struct Node* get_backpack(struct Avatar* Avatar);

// return: a Room* representing the location of the Avatar
struct Room* get_location(struct Avatar* Avatar);

// move the character in the north room
void move_north(struct Avatar* Avatar);

// move the character in the south room
void move_south(struct Avatar* Avatar);

// move the character in the west room
void move_west(struct Avatar* Avatar);

// move the character in the east room
void move_east(struct Avatar* Avatar);

void set_location(struct Avatar* Avatar,struct Room * location);

void set_charater(struct Room* room, char * npc, int n);

void character_addItem(struct Avatar* Avatar,char * item);

#endif