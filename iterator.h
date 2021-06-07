#ifndef PRSTD_ITERATOR_H
#define PRSTD_ITERATOR_H
#include <stdbool.h>
#include <stdlib.h>

struct iterator {
    struct iterator_vtable* vtable;
};

struct iterator_vtable {
    bool (*has_next)(struct iterator*);
    void* (*next)(struct iterator*);
    void* (*remove)(struct iterator*);
};

bool iterator_has_next(const struct iterator* iterator);

void* iterator_next(struct iterator* iterator);

void* iterator_remove(struct iterator* iterator);

void iterator_deconstruct(struct iterator* iterator);

#endif //PRSTD_ITERATOR_H
