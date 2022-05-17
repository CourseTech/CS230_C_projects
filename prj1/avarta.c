#include "avarta.h"
#include <string.h>


// return: a Node* representing the backpack of the Avatar
struct Node* get_backpack(struct Avatar* Avatar){
    return Avatar->backpack;
};

// return: a Room* representing the location of the Avatar
struct Room* get_location(struct Avatar* Avatar){
    return Avatar->location;
};

// move the character in the north room
void move_north(struct Avatar* Avatar){
    if (get_north(Avatar->location) == NULL){
        printf("This direction is outside of the room, you can't go outside of the room\n");
        return;
    }
    // set the room location NULL
    (get_location(Avatar) -> main) = NULL;
    Avatar->location = get_north(Avatar->location);
    (get_location(Avatar) -> main) = Avatar;

};

// move the character in the south room
void move_south(struct Avatar* Avatar){
    if (get_south(Avatar->location) == NULL){
        printf("This direction is outside of the room, you can't go outside of the room\n");
        return;
    }
    (get_location(Avatar) -> main) = NULL;
    Avatar->location = get_south(Avatar->location);
    (get_location(Avatar) -> main) = Avatar;
};

// move the character in the west room
void move_west(struct Avatar* Avatar){
    if (get_west(Avatar->location) == NULL){
        printf("This direction is outside of the room, you can't go outside of the room\n");
        return;
    }
    (get_location(Avatar) -> main) = NULL;
    Avatar->location = get_west(Avatar->location);
    (get_location(Avatar) -> main) = Avatar;

};

// move the character in the east room
void move_east(struct Avatar* Avatar){
    if (get_east(Avatar->location) == NULL){
        printf("This direction is outside of the room, you can't go outside of the room\n");
        return;
    }
    (get_location(Avatar) -> main) = NULL;
    Avatar->location = get_east(Avatar->location);
    (get_location(Avatar) -> main) = Avatar;

};

// set location of the main character when moving
void set_location(struct Avatar* Avatar,struct Room * room){
    Avatar -> location = room;
}

//set new location of the npc
void set_charater(struct Room* room, char* npc, int n){
    (room -> characters)[n] = npc;
}

// add item to the character backpack
void character_addItem(struct Avatar* Avatar,char * item){
    // struct Node * characterItems = get_backpack(Avatar);
    add_item(&(Avatar->backpack), item);
};

// print all the item in the backpack
void print_Characterinventory(struct Node * head) {
  struct Node * current_node = head;
  if (current_node == NULL){
    printf("no item in backpack\n");
  }
  else{
    printf("the items are\n");
    while ( current_node != NULL) {
      printf("%s\n", current_node->item);
      current_node = current_node->next;
    }
  }
}

// move the character to the main room when clue comnmand is called
void clue_avatar(char * str, struct Room arr[], struct Room * current){
    // char * characters[5] = {"Miss_Scarlett","Colonel_Mustard","Professor_Plum","Mrs_Peacock","Mrs_White"};

    int i;
    if (strcmp(str,"Miss_Scarlett") == 0){
        i = 0;
    }
    else if (strcmp(str,"Colonel_Mustard") == 0){
        i = 1;
    }
    else if (strcmp(str,"Professor_Plum") == 0){
        i = 2;
    }
    else if (strcmp(str,"Mrs_Peacock") == 0){
        i = 3;
    }
    else if (strcmp(str,"Mrs_White") == 0){
        i = 4;
    }

    for (int k = 0; k < 9; ++k){
        if (((&arr[k]) -> characters)[i] == NULL){
            continue;
        }
        if (strcmp(((&arr[k]) -> characters)[i],str) == 0){

            (current -> characters)[i] = str;
            // ((&arr[k]) -> character)[i] -> location = current;
            ((&arr[k]) -> characters)[i] = NULL;

            break;
        }
    }

};