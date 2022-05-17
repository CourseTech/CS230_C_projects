#include "bits.h"
#include "cache.h"

int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  unsigned int new_address = (unsigned int) address;
  new_address <<= (32 - cache->set_bits - cache->block_bits);
  new_address >>= (32 - cache->set_bits);
  return new_address;
}

int get_line(Cache *cache, address_type address) {
  // TODO:
  unsigned int new_address = (unsigned int) address;
  new_address >>= (cache->set_bits + cache->block_bits);
  return new_address;
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  unsigned int new_address = (unsigned int) address;
  new_address <<= (32 - cache->block_bits);
  new_address >>= (32 - cache->block_bits);
  return new_address;
}
