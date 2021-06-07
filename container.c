#include <stdio.h>
#include "container.h"

unsigned int container_size(const struct container* container) {
    return container->vtable->size(container);
}

struct iterator* container_iterator(const struct container* container) {
    return container->vtable->iterator(container);
}

void container_for_each(struct container* container, void (*operation)(void*)) {
    struct iterator* iterator = container_iterator(container);
    while (iterator_has_next(iterator)) {
        operation(iterator_next(iterator));
    }
    iterator_deconstruct(iterator);
}

void container_filter(struct container* container, bool (*filter)(void*)) {
    struct iterator* iterator = container_iterator(container);
    while (iterator_has_next(iterator)) {
        if (!filter(iterator_next(iterator))) {
            free(iterator_remove(iterator));
        }
    }
    iterator_deconstruct(iterator);
}

void container_deconstruct(struct container* container) {
    container->vtable->deconstruct(container);
}

void container_deconstruct_custom(struct container* container, void (*deconstructor)(void*)) {
    container->vtable->deconstruct_custom(container, deconstructor);
}
