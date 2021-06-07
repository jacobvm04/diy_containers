#ifndef PRSTD_HASH_MAP_H
#define PRSTD_HASH_MAP_H

#include <stdbool.h>
#include "array_list.h"

struct hash_map {
    struct array_list base;
    unsigned int (*hash)(void*);
    bool (*equals)(void*, void*);
    unsigned int bucket_amount;
    unsigned int size;
    size_t value_size;
    size_t key_size;
};

struct hash_map_bucket {
    struct hash_map_pair* pair;
    struct hash_map_bucket* next;
};

struct hash_map_pair {
    void* key;
    void* value;
};

struct hash_map_iterator {
    struct iterator base;
    struct hash_map* hash_map;
    int index;
    struct hash_map_bucket* bucket;
};

unsigned int hash_map_default_hash(void* data);

struct hash_map hash_map_construct(size_t key_size, size_t var_size, unsigned int buckets, unsigned int (*hash)(void*), bool (*equals)(void*, void*));

void hash_map_put(struct hash_map* hash_map, void* key, void* value);

void* hash_map_get(struct hash_map* hash_map, void* key);

bool hash_map_contains(struct hash_map* hash_map, void* key);

void* hash_map_remove(struct hash_map* hash_map, void* key);

void hash_map_deconstruct(struct hash_map* hash_map);

#endif //PRSTD_HASH_MAP_H
