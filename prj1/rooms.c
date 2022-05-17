#include "rooms.h"
#include "avarta.h"
#include "items.c"

// return: a char* representing the name of the room
char* get_roomname(struct Room* room){
    if (room == NULL){
        char* p = NULL;
        return p;
    }
    return room->name;
}

// return: a pointer to the north struct in the room
struct Room* get_north(struct Room* room){
    return room->North;
}

// return: a pointer to the south struct in the room
struct Room* get_south(struct Room* room){
    return room->South;
}

// return: a pointer to the west struct in the room
struct Room* get_west(struct Room* room){
    return room->West;
}

// return: a pointer to the east struct in the room
struct Room* get_east(struct Room* room){
    return room->East;
}

// return: a pointer to the itemlist in the room
struct Node* get_itemlist(struct Room* room){
    return room->itemList;
}

// set north of room1
void set_noth(struct Room* room1,struct Room* room2){
    room1-> North = room2;
}

// set south of room1
void set_south(struct Room* room1,struct Room* room2){
    room1-> South = room2;
}

// set east of room1
void set_east(struct Room* room1,struct Room* room2){
    room1-> East = room2;
}

// set west of room1
void set_west(struct Room* room1,struct Room* room2){
    room1-> West = room2;
}

// print all the room information include name, direction and items
void room_information(struct Room* room){
    printf("The room is %s\n",get_roomname(room));
    if (get_roomname(get_north(room)) == NULL){
        
        printf("No room to the North\n");
    }
    else{
        printf("The north room is %s\n",get_roomname(get_north(room)));
    }

    if (get_roomname(get_south(room)) == NULL){
        
        printf("No room to the South\n");
    }
    else{
        printf("The south room is %s\n",get_roomname(get_south(room)));
    }

    if (get_roomname(get_east(room)) == NULL){
        
        printf("No room to the East\n");
    }
    else{
        printf("The east room is %s\n",get_roomname(get_east(room)));
    }

    if (get_roomname(get_west(room)) == NULL){
        
        printf("No room to the West\n");
    }
    else{
        printf("The west room is %s\n",get_roomname(get_west(room)));
    }

    printf("\n");
    printf("You are in the room\n");
    for (int i = 1; i < 5; ++i){
        if((room -> characters)[i] != NULL){
            printf("%s",(room -> characters)[i]);
            printf(" is in the room\n");
        } 
    }
    printf("\n");
    print_rooomItem(room -> itemList);
    printf("\n");

}

// item added to the room when main dropped item 
void Character_dropItem(struct Room* room, char * item){
    add_item(&(room -> itemList),item);
}


//print all the items in the room
void print_rooomItem(struct Node * head) {
  struct Node * current_node = head;
  if (current_node == NULL){
    printf("No item in the room\n");
  }
  else{
    printf("The items are:\n");
    while ( current_node != NULL) {
      printf("%s\n", current_node->item);
      current_node = current_node->next;
    }
  }
}


