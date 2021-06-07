#include <string.h>
#include "priority_queue.h"

struct priority_queue priority_queue_construct(size_t var_size, int capacity, int (*compare)(void*, void*)) {
    struct priority_queue priority_queue;
    priority_queue.base = array_list_construct(var_size, capacity + 1);
    priority_queue.base.base.vtable->size = priority_queue_size;
    priority_queue.base.base.vtable->iterator = priority_queue_iterator;
    int padding = 0;
    array_list_add(&priority_queue.base, &padding);
    priority_queue.compare = compare;
    priority_queue.size = 0;

    return priority_queue;
}

unsigned int priority_queue_size(struct priority_queue* priority_queue) {
    return priority_queue->size;
}

void priority_queue_swap(struct priority_queue* priority_queue, const unsigned int index1, const unsigned int index2) {
    void* temp = calloc(1, priority_queue->base.base.var_size);
    memcpy(temp, array_list_get(priority_queue, index1), priority_queue->base.base.var_size);
    array_list_set(priority_queue, index1, array_list_get(priority_queue, index2));
    array_list_set(priority_queue, index2, temp);
    free(temp);
}

unsigned int priority_queue_parent(const unsigned int index) {
    return index / 2;
}

unsigned int priority_queue_left(const unsigned int index) {
    return index * 2;
}

unsigned int priority_queue_right(const unsigned int index) {
    return index * 2 + 1;
}

void priority_queue_swim(struct priority_queue* priority_queue, unsigned int index) {
    while (index > 1 && priority_queue->compare(array_list_get(priority_queue, priority_queue_parent(index)), array_list_get(priority_queue, index)) < 0) {
        priority_queue_swap(priority_queue, index / 2, index);
        index /= 2;
    }
}

void priority_queue_sink(struct priority_queue* priority_queue, unsigned int index) {
    while (index * 2 <= priority_queue->size) {
        int old_index = priority_queue_left(index);
        if (priority_queue_right(index) <= priority_queue->size && priority_queue->compare(array_list_get(priority_queue, old_index), array_list_get(priority_queue,
                                                                                                         priority_queue_right(index))) < 0) {
            old_index = priority_queue_right(index);
        }
        if (priority_queue->compare(array_list_get(priority_queue, old_index), array_list_get(priority_queue, index)) < 0) break;
        priority_queue_swap(priority_queue, index, old_index);
        index = old_index;
    }
}

void priority_queue_insert(struct priority_queue* priority_queue, const void* data) {
    priority_queue->size++;
    array_list_add(priority_queue, data);
    priority_queue_swim(priority_queue, priority_queue->size);
}


void* priority_queue_remove(struct priority_queue* priority_queue) {
    if (priority_queue->size < 1) return NULL;
    priority_queue_swap(priority_queue, 1, priority_queue->size);
    void* element = array_list_remove(priority_queue, priority_queue->size);
    priority_queue->size--;
    priority_queue_sink(priority_queue, 1);
    return element;
}

void* priority_queue_peek(const struct priority_queue* priority_queue) {
    if (priority_queue->size < 1) return NULL;
    return array_list_get(priority_queue, 1);
}

struct iterator* priority_queue_iterator(const struct priority_queue* priority_queue) {
    struct array_list_iterator* iterator = array_list_iterator(priority_queue);
    iterator->index = 0;
    iterator->base.vtable->remove = NULL;
    return iterator;
}

struct array_list heap_sort(struct container* container, int (*compare)(void*, void*)) {
    struct array_list sorted = array_list_construct(container->var_size, container_size(container));
    struct iterator* iterator = container_iterator(container);
    struct priority_queue temp_queue = priority_queue_construct(container->var_size, container_size(container), compare);

    while (iterator_has_next(iterator)) {
        priority_queue_insert(&temp_queue, iterator_next(iterator));
    }
    free(iterator);

    while (temp_queue.size > 0) {
        array_list_add(&sorted, priority_queue_remove(&temp_queue));
    }

    return sorted;
}

void heap_sort_array_list(struct array_list* array_list, int (*compare)(void*, void*)) {
    struct priority_queue temp_queue = priority_queue_construct(array_list->base.var_size, array_list->length, compare);
    while (array_list->length > 0) {
        void* element = array_list_remove(array_list, 0);
        priority_queue_insert(&temp_queue, element);
        free(element);
    }
    while (temp_queue.size > 0) {
        void* element = priority_queue_remove(&temp_queue);
        array_list_add(array_list, element);
        free(element);
    }
    container_deconstruct(&temp_queue);
}
