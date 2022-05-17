#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool check(struct DataNode** head){
  struct DataNode *tmp;
  tmp = *head;
  while (tmp->next != NULL){
    if (tmp->number == '0'){
      tmp = tmp->next;
    }
    else{return false;}
  }
  return true;
  
}

void add_head(struct DataNode** head_ref, char data)
{
    struct DataNode* new_node = (struct DataNode*) malloc(sizeof(struct DataNode));
    new_node->number  = data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

void add_number(struct DataNode** head, char data){

  struct DataNode * new_node = NULL;
  struct DataNode * last = NULL;

  new_node = (struct DataNode *)malloc(sizeof(struct DataNode));

  if (new_node == NULL){
      printf("Failed to insert element. Out of memory");
  }

  new_node->number = data;
  new_node->next = NULL;

  if(*head == NULL)
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

void delete_first_node(struct DataNode **head) {
  struct DataNode *tmp;
  if(head == NULL || *head == NULL) return;
    tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void delete_last_node(struct DataNode **head) {
  struct DataNode *prev = NULL, *cur = NULL;
  if(head == NULL || *head == NULL) return;

  if((*head)->next == NULL) {
    free(*head);
    *head = NULL;
  }
  
  prev = *head;
  cur = prev->next;
  
  while(cur->next) {
    prev = prev->next;
    cur = cur->next;
  }
  
  prev->next = NULL;
  free(cur);
}

int convertCharToNumber(char ch) {
  if (ch >= '0' && ch <= '9') {
    return ch - '0';
  } else if (ch >= 'A' && ch <= 'F') {
    return ch - 'A' + 10;
  } else {
    return -1;
  }
}

char convertNumberToChar(int n) {
  if (n >= 0 && n <= 9) {
    return n + '0';
  } else if (n >= 10 && n <= 15) {
    return n - 10 + 'A';
  } else {
    return 0;
  }
}

void ReverseArray(char arr[], int len)
{
    for (int i = 0; i < len/2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = temp;
    }
}

void ReverseNumArray(int arr[], int len)
{
    for (int i = 0; i < len/2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = temp;
    }
}

int power(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    else if (y%2 == 0)
        return power(x, y/2)*power(x, y/2);
    else
        return x*power(x, y/2)*power(x, y/2);
}

int unsignedbase10(Data src){
  int b = src.base;
  int s = src.sign;
  int len = src.len;
  int bit = src.number_bits;
  int num = 0;
  struct DataNode * cur = src.data;
  while (cur != NULL){
    int nodeNum = convertCharToNumber(cur->number);
    int mul = power(b, len-1);
    num += nodeNum * mul;
    --len;
    cur = cur->next;
  }
  int check = power(2,bit)-1;
  return num;
}

int* digitArr(int num){
  static int digits[100];
  int i = 0;
  int j;
  int k;
  while (num != 0){
    k = num % 10;
    digits[i] = k;
    ++i;
    num = num /10;
  }
  ReverseNumArray(digits,i);
  return digits;
}


Data convert_to_base_n(Data src, unsigned char n) {
  Data new_data;
  struct DataNode * node = NULL;
  char base = n;
  if (base < 2 || base > 16){
    return new_data;
  }
  if (base == src.base){
    return src;
  }
  else{
    int q = unsignedbase10(src);
    int r = 0;
    int i = 0;
    char numbers[100];
    if (q == 0 || q == -1){
      add_number(&node,convertNumberToChar(0));
      new_data.len = 1;
    }
    else{
      while (q != 0){
        numbers[i++] = convertNumberToChar(q % base);
        q = q / base;
      }
      numbers[i] = '\0';
      ReverseArray(numbers,i);
      
      for (int j = 0; j < i; j++) {
        add_number(&node,numbers[j]);
      }
      new_data.len = i;
    }
    
  }
  new_data.data = node;
  new_data.base = base;
  new_data.sign = src.sign;
  new_data.number_bits = src.number_bits;
  return new_data;
}


int convert_to_int(Data src) {
  // TODO
  int num = unsignedbase10(src);
  int bit = src.number_bits;
  int s = src.sign;
  int check = power(2,bit)-1;
  if (s == 0){
    return num;
  }
  else{
    int ne = -power(2,bit-1)-1;
    int po = power(2,bit-1)-1;
    if (po > num){
      return num;
    }
    int final = ne + num - po;
    return final;
  }
}

Data left_shift(Data src, int n) {
  Data new_data;
  // TODO
  if (n == 0){
    return src;
  }

  if (src.data->number == '0'){
      DataNode * node = (struct DataNode*) malloc(sizeof(struct DataNode));
      add_number(&node,'0');
      new_data.len = 1;
      new_data.data = node;
      return new_data;
  }

  new_data = convert_to_base_n(src,2);

  DataNode * list = new_data.data;

  while (new_data.len < new_data.number_bits){
    add_head(&list, '0');
    new_data.len++;
  }

  if (n >= new_data.len){
      DataNode * node = (struct DataNode*) malloc(sizeof(struct DataNode));;
      add_number(&node,'0');
      new_data.len = 1;
      new_data.data = node;
      return new_data;
  }

  while (n > 0){
    delete_first_node(&list);
    add_number(&list,'0');
    n--;
  }
  if (check(&list) == true){
      DataNode * node = (struct DataNode*) malloc(sizeof(struct DataNode));
      node->number = '/0';
      new_data.len = 1;
      new_data.data = node;
      return new_data;
  }

  while (list->number == '0'){
    delete_first_node(&list);
    new_data.len--;
  }

  new_data.data = list;
  return new_data;
}

Data right_shift(Data src, int n) {
  Data new_data;
  // TODO
 if (n == 0){
    return src;
  }

  if (src.data->number == '0'){
      DataNode * node = (struct DataNode*) malloc(sizeof(struct DataNode));
      add_number(&node,'0');
      new_data.len = 1;
      new_data.data = node;
      return new_data;
  }

  new_data = convert_to_base_n(src,2);

  DataNode * list = new_data.data;

  while (new_data.len < new_data.number_bits){
    add_head(&list, '0');
    new_data.len++;
  }

  if (n >= new_data.len){
      DataNode * node = (struct DataNode*) malloc(sizeof(struct DataNode));;
      add_number(&node,'0');
      new_data.len = 1;
      new_data.data = node;
      return new_data;
  }

  if (new_data.sign == 1){
    while (n > 0){
      delete_last_node(&list);
      add_head(&list,list->number);
      n--;
    }
  }
  else{
    while (n > 0){
      delete_last_node(&list);
      add_head(&list,'0');
      n--;
    }
  }
  
  if (check(&list) == true){
      DataNode * node = (struct DataNode*) malloc(sizeof(struct DataNode));
      node->number = '/0';
      new_data.len = 1;
      new_data.data = node;
      return new_data;
  }
  while (list->number == '0'){
    delete_first_node(&list);
    new_data.len--;
  }

  new_data.data = list;
  return new_data;
}
