#ifndef PRSTD_CONTAINER_H
#define PRSTD_CONTAINER_H

#include "iterator.h"

struct container {
    struct container_vtable* vtable;
    size_t var_size;
};

struct container_vtable {
    unsigned int (*size)(struct container*);
    struct iterator* (*iterator)();
    void (*deconstruct)(struct container*);
    void (*deconstruct_custom)(struct container*, void (*deconstructor)(void*));
};

unsigned int container_size(const struct container* container);

struct iterator* container_iterator(const struct container* container);

void container_for_each(struct container* container, void (*operation)(void*));

void container_filter(struct container* container, bool (*filter)(void*));

struct container* container_copy(const struct container* container);

void container_deconstruct(struct container* container);

void container_deconstruct_custom(struct container* container, void (*deconstructor)(void*));

#endif //PRSTD_CONTAINER_H
