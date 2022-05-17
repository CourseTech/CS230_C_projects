#include "items.h"
#include <string.h>

// add item to the list
void add_item(struct Node** head, char * data){
  if (search(head, data) == true){
    return;
  }
  struct Node * new_node = NULL;
  struct Node * last = NULL;

  new_node = (struct Node *)malloc(sizeof(struct Node));

  if (new_node == NULL)
  {
      printf("Failed to insert element. Out of memory");
  }

  new_node->item = data;
  new_node->next = NULL;

  if( *head == NULL)
  {
      *head = new_node;
      return;
  }

  last = *head;
  while(last->next != NULL){
    last = last->next;
  }

  last->next = new_node;
}

// drop item in the linkedlist
void drop_item(struct Node** head, char * data){
  if (search(head, data) == false){
    return;
  }

  struct Node *temp;

  if (strcmp((*head)->item ,data) == 0){

  // if((*head)->data == key){
      temp = *head;  
      *head = (*head)->next;
      free(temp);
  }
  else
  {
      struct Node *current  = *head;
      while(current->next != NULL)
      {
        if (strcmp(current-> next -> item ,data) == 0)
        // if(current->next->data == key)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            break;
        }
        else
              current = current->next;
      }
  }
}

// search if an item exist in the list
bool search(struct Node** head,char * data){
  struct Node* current = *head;

  while (current != NULL) {
    
    if (strcmp(current->item ,data) == 0) return true;
      current = current->next;
    }
  return false;
};