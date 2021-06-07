#include <string.h>
#include <stdio.h>
#include "hash_map.h"

unsigned int hash_map_default_hash(void* data) {
    return (unsigned int) data;
}

struct hash_map hash_map_construct(size_t key_size, size_t var_size, unsigned int buckets, unsigned int (*hash)(void*), bool (*equals)(void*, void*)) {
    struct hash_map hash_map;
    hash_map.base = array_list_construct(sizeof(struct hash_map_bucket), buckets);
    hash_map.value_size = var_size;
    hash_map.hash = hash != NULL ? hash : hash_map_default_hash;
    hash_map.equals = equals;
    hash_map.size = 0;
    hash_map.bucket_amount = buckets;
    hash_map.key_size = key_size;

    int padding = 0;
    for (int i = 0; i < hash_map.base.capacity; i++) {
        array_list_add(&hash_map.base, &padding);
    }

    return hash_map;
}

void hash_map_put(struct hash_map* hash_map, void* key, void* value) {
    if (hash_map_contains(hash_map, key)) {
        memcpy(hash_map_get(hash_map, key), value, hash_map->key_size);
    }

    unsigned int index = hash_map->hash(key) % hash_map->bucket_amount;
    struct hash_map_pair* pair = calloc(1, sizeof(struct hash_map_pair));
    pair->key = calloc(1, hash_map->key_size);
    pair->value = calloc(1, hash_map->value_size);
    memcpy(pair->key, key, hash_map->key_size);
    memcpy(pair->value, value, hash_map->value_size);

    struct hash_map_bucket* hash_map_bucket = calloc(1, sizeof(struct hash_map_bucket));
    hash_map_bucket->next = NULL;
    hash_map_bucket->pair = pair;

    if (*(int*)array_list_get(&hash_map->base, index) == 0) {
        array_list_set(&hash_map->base, index, hash_map_bucket);
        free(hash_map_bucket);
    } else {
        struct hash_map_bucket* bucket = array_list_get(&hash_map->base, index);
        while (bucket->next != NULL) bucket = bucket->next;
        bucket->next = hash_map_bucket;
    }
}

void* hash_map_get(struct hash_map* hash_map, void* key) {
    unsigned int index = hash_map->hash(key) % hash_map->bucket_amount;
    if (*(int*)array_list_get(&hash_map->base, index) == 0) return NULL;
    struct hash_map_bucket* bucket = array_list_get(&hash_map->base, index);
    if (bucket->pair->key == NULL) return NULL;
    while (bucket->next != NULL && bucket->pair->key != NULL && !hash_map->equals(bucket->pair->key, key)) bucket = bucket->next;
    if (bucket->pair->key != NULL && !hash_map->equals(bucket->pair->key, key)) return NULL;
    else return bucket->pair->value;
}

bool hash_map_contains(struct hash_map* hash_map, void* key) {
    unsigned int index = hash_map->hash(key) % hash_map->bucket_amount;
    if (*(int*)array_list_get(&hash_map->base, index) == 0) return false;
    struct hash_map_bucket* bucket = array_list_get(&hash_map->base, index);
    if (bucket->pair->key == NULL) return NULL;
    while (bucket->next != NULL && bucket->pair->key != NULL && !hash_map->equals(bucket->pair->key, key)) bucket = bucket->next;
    if (bucket->pair->key != NULL && !hash_map->equals(bucket->pair->key, key)) return false;
    else return true;
}

void hash_map_deconstruct(struct hash_map* hash_map) {
    struct array_list_iterator* iterator = array_list_iterator(&hash_map->base);
    while (iterator_has_next(iterator)) {
        if(*(int*)iterator_next(iterator) != 0) {
            struct hash_map_bucket* bucket = iterator_remove(iterator);
            struct hash_map_bucket* next = bucket->next;
            while (next != NULL) {
                free(bucket->pair->key);
                free(bucket->pair->value);
                free(bucket->pair);
                free(bucket);
                bucket = next;
                next = bucket->next;
            }
            free(bucket->pair->key);
            free(bucket->pair->value);
            free(bucket->pair);
            free(bucket);
        } else {
            free(iterator_remove(iterator));
        }
    }
    array_list_deconstruct(hash_map);
    iterator_deconstruct(iterator);
}

void* hash_map_remove(struct hash_map* hash_map, void* key) {
    unsigned int index = hash_map->hash(key) % hash_map->bucket_amount;
    if (*(int*)array_list_get(&hash_map->base, index) == 0) return NULL;
    struct hash_map_bucket* bucket = array_list_get(&hash_map->base, index);
    while (bucket->next != NULL && bucket->pair->key != NULL && !hash_map->equals(bucket->pair->key, key)) bucket = bucket->next;
    if (hash_map->equals(bucket->pair->key, key)) {
        free(bucket->pair->key);
        bucket->pair->key = NULL;
    }
}
