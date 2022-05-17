#include "avarta.c"
#include "rooms.c"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

//generate random number
int randomNum(int upper, int lower){
    int number = (rand() % (upper - lower + 1)) + lower;
    return number;
}

// generate random charater
char * randomCharacter(char * characters[]){
    int random = randomNum(4,0);
    return characters[random];
}

// generate random room
struct Room * randomRoom(struct Room arr_room[]){
    int random = randomNum(8,0);
    // printf("%i",random);
    return &arr_room[random];
}

// check if a character exist
bool existValue(char * array[], char * item, int size){
    for (int i = 0; i < size; ++i){
        if (strcmp(array[i],item) == 0){
            return true;
        }
    }
    return false;
}

// create random item
char * randomItem(char * items[]){
    int r = randomNum(5,0);
    return items[r];
}


void swap(struct Room *a, struct Room *b) {
    struct Room temp = *a;
    *a = *b;
    *b = temp;
}

// craete random list of room
void randomize(struct Room arr[], int n) {
    srand(time(NULL));
    int i;
    for(i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}

void swapNum(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// create a random list of number
void randomizeNum(int arr[], int n) {
    srand(time(NULL));
    int i;
    for(i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swapNum(&arr[i], &arr[j]);
    }
}

// shuffle the rooms
void shuffleBoard(struct Room arr[]){
    randomize(arr,9);
}

//connect all the room together
void connectBoard(struct Room arr[]){
    struct Room * null = NULL;
    set_noth(&arr[0],NULL);
    set_noth(&arr[1],NULL);
    set_noth(&arr[2],NULL);
    set_noth(&arr[3],&arr[0]);
    set_noth(&arr[4],&arr[1]);
    set_noth(&arr[5],&arr[2]);
    set_noth(&arr[6],&arr[3]);
    set_noth(&arr[7],&arr[4]);
    set_noth(&arr[8],&arr[5]);

    set_south(&arr[0],&arr[3]);
    set_south(&arr[1],&arr[4]);
    set_south(&arr[2],&arr[5]);
    set_south(&arr[3],&arr[6]);
    set_south(&arr[4],&arr[7]);
    set_south(&arr[5],&arr[8]);
    set_south(&arr[6],NULL);
    set_south(&arr[7],NULL);
    set_south(&arr[8],NULL);

    set_east(&arr[0],&arr[1]);
    set_east(&arr[1],&arr[2]);
    set_east(&arr[2],NULL);
    set_east(&arr[3],&arr[4]);
    set_east(&arr[4],&arr[5]);
    set_east(&arr[5],NULL);
    set_east(&arr[6],&arr[7]);
    set_east(&arr[7],&arr[8]);
    set_east(&arr[8],NULL);

    set_west(&arr[0],NULL);
    set_west(&arr[1],&arr[0]);
    set_west(&arr[2],&arr[1]);
    set_west(&arr[3],NULL);
    set_west(&arr[4],&arr[3]);
    set_west(&arr[5],&arr[4]);
    set_west(&arr[6],NULL);
    set_west(&arr[7],&arr[6]);
    set_west(&arr[8],&arr[7]);
}

// create the board with shuffle 
void createBoard(struct Room arr[],char * room_name[]){
    for (int i = 0; i < 9; ++i){
        struct Room room = {room_name[i], NULL, NULL, NULL,NULL, NULL};
        arr[i] = room;
    }
    shuffleBoard(arr);
    connectBoard(arr);
}

//randomize item in the room
void distributeItem(struct Room arr[],char * item[]){
    // struct Node itemList[6];
    int nums[9] = {0,1,2,3,4,5,6,7,8};
    randomizeNum(nums,9);
    for (int i = 0; i < 6; ++i){
        add_item(&((&arr[nums[i]]) -> itemList),item[i]);
    }
}

//randomize character in the room
void distributeCharacters(struct Room arr[],char * npcs[]){
    int nums[9] = {0,1,2,3,4,5,6,7,8};
    randomizeNum(nums,9);
    for (int i = 0; i < 5; ++i){
        set_charater(&arr[nums[i]],npcs[i],i);
    }
}

// print the game information with name of the room, characters, and items
void game_info(char * room_name[], char * characters[],char * item[]){
    printf("The 9 rooms are: \n");
    for (int i = 0; i < 9; ++i){
        printf("%s\n", room_name[i]);
    }
    printf("\n");
    printf("The other characters are: \n");
    for (int i = 0; i < 5; ++i){
        printf("%s\n", characters[i]);
    }
    printf("\n");
    printf("All the items are: \n");
    for (int i = 0; i < 6; ++i){
        printf("%s\n", item[i]);
    }
}

// conduct the command in the game
void command(struct Avatar * main_character,char * room_name[], char * characters[],char * items[],char * item_answer,char * answer_character, char * answer_room,struct Room arr_room[]){
    int check = 0;
    printf("Welcome to the game\n");
    char * command;
    command = (char*)malloc(10*sizeof(char));
    while (check < 10){
        printf("If you need help, please enter 'help' for instructions\n\n");
        scanf("%s",command);
        if (strcmp(command,"help") == 0){
            printf("All the commands are 'look', 'go', 'list', 'take', 'drop' ,'inventory', 'clue'\n");
        }

        else if (strcmp(command,"list") == 0){
            game_info( room_name, characters,items);
        }

        else if (strcmp(command,"look") == 0){
            room_information(main_character -> location);
        }

        else if (strcmp(command,"go") == 0){
            printf("please enter the direction\n");
            char *direction;
            direction = (char*)malloc(10*sizeof(char));
            // free(direction);
            scanf("%s",direction);

            for (;;){

                if ((strcmp(direction,"north") == 0) || (strcmp(direction,"south") == 0) || (strcmp(direction,"west")== 0) || (strcmp(direction,"east")== 0)){
                    // printf("true");
                    break;
                }
                else{
                    printf("invalid direction, please enter again\n");
                    scanf("%s",direction);
                }
            }

            if (strcmp(direction,"north") == 0){
                move_north(main_character);
            }
            else if (strcmp(direction,"south")== 0){
                move_south(main_character);
            }
            else if (strcmp(direction,"west")== 0){
                move_west(main_character);
            }
            else if (strcmp(direction,"east")== 0){
                move_east(main_character);
            }
            
        }

        else if (strcmp(command,"take")== 0){
            printf("Enter the items you want to take\n");
            char *item;
            item = (char*)malloc(10*sizeof(char));
            // free(item);
            scanf("%s",item);
            // scan again if item does not in the list
    // char * item[6] = {"knife","candlestick","rope","wrench","gun","hammer"};

            for (;;){
                if ((strcmp(item,"knife") == 0) || (strcmp(item,"candlestick") == 0) || (strcmp(item,"rope")== 0) || (strcmp(item,"wrench")== 0) || (strcmp(item,"gun")== 0) || (strcmp(item,"hammer")== 0)){
                    // printf("true");
                    break;
                }
                else{
                    printf("Invalid item, please enter again\n");
                    scanf("%s",item);
                }
            }
            bool checkRoom = search(&((main_character -> location) -> itemList),item);

            if (checkRoom == false){
                printf("Item is not in the room\n");
            }
            else{
                printf("Item added to inventory\n");
                drop_item(&(get_location(main_character) -> itemList),item);
                character_addItem(main_character, item);
            }
        }

        else if (strcmp(command,"drop")== 0){
            printf("Enter the item you want to drop\n");
            char *item;
            item = (char*)malloc(10*sizeof(char));
            // free(item);
            scanf("%s",item);
            // scan again if item does not in the list
            for (;;){
                if ((strcmp(item,"knife") == 0) || (strcmp(item,"candlestick") == 0) || (strcmp(item,"rope")== 0) || (strcmp(item,"wrench")== 0) || (strcmp(item,"gun")== 0) || (strcmp(item,"hammer")== 0)){
                    // printf("true");
                    break;
                }
                else{
                    printf("Invalid item, please enter again\n");
                    scanf("%s",item);
                }
            }
            bool checkBackpack = search(&(main_character -> backpack),item);
            if (checkBackpack == true){
                printf("Item dropped\n");
                drop_item(&(main_character -> backpack),item);
                Character_dropItem(main_character ->location,item);
            }
            else{
                printf("You don't have this item\n");
            }
        }

        else if (strcmp(command,"inventory")== 0){
            print_Characterinventory(main_character -> backpack);
        }

        else if (strcmp(command,"clue")== 0){
            /* code */
            printf("please enter a character name\n");
            ++check;
            char *predict_character;
            predict_character = (char*)malloc(20*sizeof(char));
            scanf("%s",predict_character);
            for (;;){
                if (existValue(characters,predict_character,5)){
                    break;
                }
                else{
                    printf("Invalid character, please enter again\n");
                    scanf("%s",predict_character);
                }
            }



            // set character to the room with main
            clue_avatar(predict_character,arr_room,main_character -> location);


            bool predict_item = search(&(main_character -> backpack),item_answer) || search(&(main_character -> location -> itemList),item_answer);

            int count = 0;
            if (strcmp(predict_character,answer_character) == 0){
                printf("\nCharacter Match\n");
                ++count;
            }
            if (predict_item){
                printf("\nItem Match\n");
                ++count;
            }
            
            if (strcmp(answer_room,get_roomname(get_location(main_character))) == 0){
                printf("\nRoom Match\n");
                ++count;
            }
            if (count == 0){
                printf("no correct answer\n");
            }
            if (count == 3){
                printf("\nYOU WON!!!\n");
                break;
            }
        }

        else{
            printf("Invalid command, please enter a valid command\n");
        }
        // free(command);

    }
    printf("You have used all your 10 commands. You lost the game.\n");
}

int main(){
    char * room_name[9] = {"hall","study","lounge","library","dining room","ball room","conservatory","bedroom","arcard"};
    char * characters[5] = {"Miss_Scarlett","Colonel_Mustard","Professor_Plum","Mrs_Peacock","Mrs_White"};
    char * item[6] = {"knife","candlestick","rope","wrench","gun","hammer"};
    
    struct Room arr_room[9];

    createBoard(arr_room,room_name);
    distributeItem(arr_room,item);
    distributeCharacters(arr_room,characters);

    char * item_answer = randomItem(item);
    char * answer_character = randomCharacter(characters);
    char * answer_room = get_roomname(randomRoom(arr_room));

    struct Avatar main_character = {"main",NULL,NULL};
    ((&arr_room[0]) -> main) = &main_character;
    ((&main_character) -> location) = &arr_room[0];

    command(&main_character, room_name, characters, item,item_answer,answer_character,answer_room,arr_room);

    return 0;
}