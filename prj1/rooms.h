#include <stdio.h>
#include "items.h"

#ifndef ROOMS_H
#define ROOMS_H

// rooom has a main avatar, and an list of characters
struct Room {
    char * name;
    struct Room * North;
    struct Room * South;
    struct Room * East;
    struct Room * West;
    struct Node * itemList;
    struct Avatar * main;
    char * characters[5];
};

// return: a char* representing the name of the room
char* get_roomname(struct Room* room);

// return: a pointer to the north struct in the room
struct Room* get_north(struct Room* room);

// return: a pointer to the south struct in the room
struct Room* get_south(struct Room* room);

// return: a pointer to the west struct in the room
struct Room* get_west(struct Room* room);

// return: a pointer to the east struct in the room
struct Room* get_east(struct Room* room);

// return: a pointer to the itemlist in the room
struct Node* get_itemlist(struct Room* room);

// set north of room1
void set_noth(struct Room* room1,struct Room* room2);

// set south of room1
void set_south(struct Room* room1,struct Room* room2);

// set west of room1
void set_west(struct Room* room1,struct Room* room2);

// set east of room1
void set_east(struct Room* room1,struct Room* room2);

// print all the room information include name, direction and items
void room_information(struct Room* room);

// item added to the room when main dropped item 
void Character_dropItem(struct Room* room, char * item);

//print all the items in the room
void print_rooomItem(struct Node * head);
#endif