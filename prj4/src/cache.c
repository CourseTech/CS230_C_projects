#include "cache.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"
#include "cpu.h"
#include "lru.h"

char *make_block(int block_size) {
  // TODO:
  //   Make and initialize a block's accessed bits given the block_size.
  //
  // HINT: if it wasn't clear already, this gets put in the "accessed" field
  char* new_block = (char*) malloc(sizeof(char) * block_size); 
  return new_block;
}

Line *make_lines(int line_count, int block_size) {
  // TODO:
  //   Make and initialize the lines given the line count. Then
  //   make and initialize the blocks.
  //
  //   HINT: this will be placed in the "accessed" field of a Line
  Line * lines_array;
  lines_array = (Line*) malloc(line_count * sizeof(Line)); 
  for (int i = 0; i < line_count; ++i){
    lines_array[i].accessed = make_block(block_size);
    lines_array[i].block_size = block_size;
    lines_array[i].tag = -1;
    lines_array[i].valid = 0;
  }
  return lines_array;

}

Set *make_sets(int set_count, int line_count, int block_size) {
  // TODO:
  //   Make and initialize the sets given the set count. Then
  //   make and initialize the line and blocks.

  Set * sets_array;
  sets_array = (Set*) malloc(set_count * sizeof(Set)); 
  for (int i = 0; i < set_count; ++i){
    LRUNode * new_node = (LRUNode*) malloc(sizeof(LRUNode));

    sets_array[i].lru_queue = new_node;
    sets_array[i].line_count = line_count;  
    sets_array[i].lines = make_lines(line_count,block_size);

  }
  return sets_array;
}

Cache *make_cache(int set_bits, int line_count, int block_bits) {
  Cache *cache = NULL;

  cache = (Cache*) malloc(sizeof(Cache));
  int count_of_set = (int) pow(2,set_bits); 
  int bloc_size_count = (int) pow(2,block_bits);
  cache->set_bits = set_bits;
  cache->block_bits= block_bits;
  cache->sets = make_sets(count_of_set, line_count,bloc_size_count);
  cache->set_count = count_of_set;
  cache->block_size = bloc_size_count;
  cache->line_count = line_count;
  // Create LRU queues for sets:
  if (cache != NULL) {
    lru_init(cache);
  }

  return cache;
}

void delete_block(char *accessed) { free(accessed); }

void delete_lines(Line *lines, int line_count) {
  for (int i = 0; i < line_count; i++) {
    delete_block(lines[i].accessed);
  }
  free(lines);
}

void delete_sets(Set *sets, int set_count) {
  for (int i = 0; i < set_count; i++) {
    delete_lines(sets[i].lines, sets[i].line_count);
  }
  free(sets);
}

void delete_cache(Cache *cache) {
  lru_destroy(cache);
  delete_sets(cache->sets, cache->set_count);
  free(cache);
}

AccessResult cache_access(Cache *cache, TraceLine *trace_line) {
  unsigned int s = get_set(cache, trace_line->address);
  unsigned int t = get_line(cache, trace_line->address);
  unsigned int b = get_byte(cache, trace_line->address);

  // Get the set:
  Set *set = &cache->sets[s];

  // Get the line:
  LRUResult result;
  lru_fetch(set, t, &result);
  Line *line = result.line;

  // If it was a miss we will clear the accessed bits:
  if (result.access != HIT) {
    for (int i = 0; i < cache->block_size; i++) {
      line->accessed[i] = 0;
    }
  }

  // Then set the accessed byte to 1:
  line->accessed[b] = 1;

  return result.access;
}
