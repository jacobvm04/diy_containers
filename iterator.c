#include "iterator.h"

bool iterator_has_next(const struct iterator* iterator) {
    return iterator->vtable->has_next(iterator);
}

void* iterator_next(struct iterator* iterator) {
    return iterator->vtable->next(iterator);
}

void* iterator_remove(struct iterator* iterator) {
    return iterator->vtable->remove(iterator);
}

void iterator_deconstruct(struct iterator* iterator) {
    free(iterator->vtable);
    free(iterator);
}
