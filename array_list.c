#include <string.h>
#include <assert.h>
#include "array_list.h"

struct array_list array_list_construct(const size_t var_size, const unsigned int capacity) {
    assert(var_size > 0);
    assert(capacity > 0);

    struct array_list array_list;
    struct container_vtable vtable = { .size = array_list_size, .iterator = array_list_iterator,
            .deconstruct = array_list_deconstruct, .deconstruct_custom = array_list_deconstruct_custom };
    array_list.base.vtable = calloc(1, sizeof(struct container_vtable));
    memcpy(array_list.base.vtable, &vtable, sizeof(struct container_vtable));

    array_list.capacity = capacity;
    array_list.length = 0;
    array_list.base.var_size = var_size;
    array_list.data = calloc(capacity, var_size);

    return array_list;
}

unsigned int array_list_size(struct array_list* array_list) {
    return array_list->length;
}

void array_list_reallocate(struct array_list* array_list) {
    array_list->capacity *= 2;
    array_list->data = realloc(array_list->data, array_list->capacity * array_list->base.var_size);
}

void array_list_add(struct array_list* array_list, const void* data) {
    if (array_list->length >= array_list->capacity) array_list_reallocate(array_list);
    memcpy(array_list->data + (array_list->length * array_list->base.var_size), data, array_list->base.var_size);
    array_list->length++;
}

void* array_list_get(const struct array_list* array_list, const unsigned int index) {
    assert(index >= 0 && index <= array_list->length - 1);
    return array_list->data + (index * array_list->base.var_size);
}

void array_list_set(struct array_list* array_list, const unsigned int index, const void* data) {
    assert(index >= 0 && index <= array_list->length - 1);
    memcpy(array_list->data + (index * array_list->base.var_size), data, array_list->base.var_size);
}

void array_list_insert(struct array_list* this, const unsigned int index, const void* data) {
    this->length++;
    assert(index >= 0 && index <= this->length - 1);
    if (this->length >= this->capacity) array_list_reallocate(this);
    memcpy(this->data + (index * this->base.var_size) + this->base.var_size, this->data + (index * this->base.var_size),
           this->base.var_size * (this->length - 1 - index));
    memcpy(this->data + (index * this->base.var_size), data, this->base.var_size);
}

void* array_list_remove(struct array_list* array_list, const unsigned int index) {
    assert(index >= 0 && index <= array_list->length - 1);
    void* old_value = calloc(1, array_list->base.var_size);
    memcpy(old_value, array_list->data + (index * array_list->base.var_size), array_list->base.var_size);
    array_list->length--;
    memcpy(array_list->data + (index * array_list->base.var_size), array_list->data + (index * array_list->base.var_size) + array_list->base.var_size,
           array_list->base.var_size * (array_list->length - index));
    return old_value;
}

void array_list_deconstruct_custom(struct array_list* array_list, void (*deconstructor)(void*)) {
    for (int i = 0; i < array_list->length; i++) {
        deconstructor(array_list->data + (i * array_list->base.var_size));
    }
    free(array_list->data);
    free(array_list->base.vtable);
}

void array_list_deconstruct(struct array_list* array_list) {
    free(array_list->data);
    free(array_list->base.vtable);
}

bool array_list_iterator_has_next(const struct array_list_iterator* iterator) {
    if (iterator->index == -1) return iterator->array_list->length > 0;
    return iterator->index < (iterator->array_list->length - 1);
}

void* array_list_iterator_next(struct array_list_iterator* iterator) {
    return array_list_iterator_has_next(iterator) ?
           array_list_get(iterator->array_list, ++iterator->index) :
           NULL;
}

struct array_list_iterator* array_list_iterator(const struct array_list* array_list) {
    struct array_list_iterator* iterator = calloc(1, sizeof(struct array_list_iterator));
    struct iterator_vtable vtable = { .has_next = array_list_iterator_has_next, .next = array_list_iterator_next, .remove = array_list_iterator_remove };
    iterator->base.vtable = calloc(1, sizeof(struct iterator_vtable));
    memcpy(iterator->base.vtable, &vtable, sizeof(struct iterator_vtable));

    iterator->array_list = array_list;
    iterator->index = -1;

    return iterator;
}

void* array_list_iterator_remove(struct array_list_iterator* iterator) {
    void* old_value = array_list_remove(iterator->array_list, iterator->index);
    iterator->index--;
    return old_value;
}
