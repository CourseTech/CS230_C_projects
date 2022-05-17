This is an implementation of the Cluedo game

Explains how to compile the code  (3 points)
There are 4 c files in the folder
the avarta.c, avarta.h is a file for the main character to move around, pick item and look inside the look

rooms.c, rooms.h, items.c and items.h are the requirement of the project
rooms is the file for look inside the room, pick an item when character drop and contain all the chracters
items.c is the linkedlist of items, we can add, drop and search for an item


Overview/description of the overall structure of the game board with pointers (3 points)
whenever I created a struct, could be a room, character or item, I would use malloc, also pointers also points to other room, item in the linkedlist. Pointer could be point to a character as well


Explains how to manage user input (3 points)
I used the scanf function to take input from the user, whenenver a input is not in the commands, the user needs to input again