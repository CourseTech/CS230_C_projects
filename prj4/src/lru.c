#include "lru.h"
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

void lru_init_queue(Set *set) {
  LRUNode *s = NULL;
  LRUNode **pp = &s;  // place to chain in the next node
  for (int i = 0; i < set->line_count; i++) {
    Line *line = &set->lines[i];
    LRUNode *node = (LRUNode *)(malloc(sizeof(LRUNode)));
    node->line = line;
    node->next = NULL;
    (*pp) = node;
    pp = &((*pp)->next);
  }
  set->lru_queue = s;
}

void lru_init(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    lru_init_queue(&sets[i]);
  }
}

void lru_destroy(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    LRUNode *p = sets[i].lru_queue;
    LRUNode *n = p;
    while (p != NULL) {
      p = p->next;
      free(n);
      n = p;
    }
    sets[i].lru_queue = NULL;
  }
}

void lru_fetch(Set *set, unsigned int tag, LRUResult *result) {
  // TODO:
  // Implement the LRU algorithm to determine which line in
  // the cache should be accessed.

  LRUNode * previous_node = NULL;
  LRUNode * current_node = set->lru_queue;
  while (current_node != NULL){
    Line * current_line = current_node->line;
    if (current_line->valid == 1 && current_line->tag == tag){
      result->line = current_line;
      result->access = HIT;
    }
    else if (current_line->valid == 0){
      result->access = COLD_MISS;
      result->line = current_line;
      result->line->valid = 1;
      result->line->tag = tag;
    }
    else if (current_node->next == NULL){
      result->access = CONFLICT_MISS;
      result->line = current_line;
      result->line->tag = tag;
    }
    else{
      previous_node = current_node;
      current_node = current_node->next;
      continue;
    }
    if (previous_node != NULL){
      previous_node->next = current_node->next;
      current_node->next = set->lru_queue;
      set->lru_queue = current_node;
    }
    return;
  }

}
