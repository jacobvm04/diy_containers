#ifndef PRSTD_array_list_H
#define PRSTD_array_list_H

#include <stdbool.h>
#include "iterator.h"
#include "container.h"

struct array_list {
    struct container base;
    void* data;
    unsigned int capacity;
    unsigned int length;
};

struct array_list_iterator {
    struct iterator base;
    struct array_list* array_list;
    int index;
};

struct array_list array_list_construct(const size_t var_size, const unsigned int capacity);

unsigned int array_list_size(struct array_list* array_list);

void array_list_reallocate(struct array_list* array_list);

void array_list_add(struct array_list* array_list, const void* data);

// Returns a pointer to the element at the specified index. Remember that since array_list function returns a pointer to the specific,
// location in the array_list containing the element, any subsequent mutations to the array_list such as those caused by the array_list_insert
// or array_list_remove may invalidate the previously returned pointer. Therefore, if you must preserve a returned value from array_list
// method following certain mutations to it, remember to dereference or copy the data at the returned pointer.
void* array_list_get(const struct array_list* array_list, const unsigned int index);

void array_list_set(struct array_list* array_list, const unsigned int index, const void* data);

void array_list_insert(struct array_list* this, const unsigned int index, const void* data);

// Removes an element at the specified index. To return the removed element so that it may be cleaned up before deletion
// or to do something else, the element is copied into a newly allocated piece of memory. Therefore, remember to free the pointer
// that is returned by array_list function at some point.
void* array_list_remove(struct array_list* array_list, const unsigned int index);

void array_list_deconstruct_custom(struct array_list* array_list, void (*deconstructor)(void*));

void array_list_deconstruct(struct array_list* array_list);

bool array_list_iterator_has_next(const struct array_list_iterator* iterator);

void* array_list_iterator_next(struct array_list_iterator* iterator);

struct array_list_iterator* array_list_iterator(const struct array_list* array_list);

void* array_list_iterator_remove(struct array_list_iterator* iterator);

#endif //PRSTD_array_list_H
