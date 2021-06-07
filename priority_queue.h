#ifndef PRSTD_PRIORITY_QUEUE_H
#define PRSTD_PRIORITY_QUEUE_H

#include "array_list.h"

struct priority_queue {
    struct array_list base;
    unsigned int size;
    int (*compare)(void*, void*);
};

struct priority_queue priority_queue_construct(size_t var_size, int capacity, int (*compare)(void*, void*));

unsigned int priority_queue_size(struct priority_queue* priority_queue);

unsigned int priority_queue_parent(const unsigned int index);

unsigned int priority_queue_left(const unsigned int index);

unsigned int priority_queue_right(const unsigned int index);

void priority_queue_swap(struct priority_queue* priority_queue, const unsigned int index1, const unsigned int index2);

void priority_queue_swim(struct priority_queue* priority_queue, unsigned int index);

void priority_queue_sink(struct priority_queue* priority_queue, unsigned int index);

void priority_queue_insert(struct priority_queue* priority_queue, const void* data);

void* priority_queue_remove(struct priority_queue* priority_queue);

void* priority_queue_peek(const struct priority_queue* priority_queue);

struct iterator* priority_queue_iterator(const struct priority_queue* priority_queue);

struct array_list heap_sort(struct container* container, int (*compare)(void*, void*));

void heap_sort_array_list(struct array_list* array_list, int (*compare)(void*, void*));

#endif //PRSTD_PRIORITY_QUEUE_H
