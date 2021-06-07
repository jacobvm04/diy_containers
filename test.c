#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"
#include "priority_queue.h"
#include "hash_map.h"

struct array_list test_array_list() {
    struct array_list array_list = array_list_construct(sizeof(char) * 10, 3);
    array_list_add(&array_list, "hello");
    array_list_add(&array_list, "world");
    array_list_insert(&array_list, 1, "good");
    array_list_insert(&array_list, 1, "amazing");
    array_list_set(&array_list, 3, "day");
    char* removed_value = array_list_remove(&array_list, 2);
    printf("removed index %d value: %s\n", 2, removed_value);
    free(removed_value);

    return array_list;
}

void print_string_callback(char* data) {
    printf("Element: %s\n", data);
}
void print_int_callback(int* data) {
    printf("Element: %d\n", *data);
}

bool string_length_filter(char* data) {
    return strlen(data) <= 5;
}

void setup_testing_array(struct container* container) {
    container_filter(container, string_length_filter);
    container_for_each(container, print_string_callback);
}

int int_compare(int* a, int* b) {
    return *a - *b;
}

unsigned int reflect(void* a) {
    return *(unsigned int*)a;
}

bool int_equals(int* a, int* b) {
    return *a == *b;
}

int main() {
    struct array_list array_list1 = test_array_list();
    struct array_list array_list2 = test_array_list();
    struct array_list array_list3 = array_list_construct(sizeof(struct array_list), 2);
    array_list_add(&array_list3, &array_list1);
    array_list_add(&array_list3, &array_list2);
    array_list_add(array_list_get(&array_list3, 1), "right now");
    container_for_each(&array_list3, setup_testing_array);
    container_deconstruct_custom(&array_list3, container_deconstruct);

    printf("\n\n");
    struct array_list priority_queue = array_list_construct(sizeof(int), 10);
    int a1 = 1;
    int a2 = 7;
    int a3 = 4;
    int a4 = 9;
    int a5 = 20;
    int a6 = 3;
    array_list_add(&priority_queue, &a1);
    array_list_add(&priority_queue, &a2);
    array_list_add(&priority_queue, &a3);
    array_list_add(&priority_queue, &a4);
    array_list_add(&priority_queue, &a5);
    array_list_add(&priority_queue, &a6);

    heap_sort_array_list(&priority_queue, int_compare);

    container_for_each(&priority_queue, print_int_callback);

    container_deconstruct(&priority_queue);

    printf("\n\n");
    struct hash_map hash_map = hash_map_construct(sizeof(int), sizeof(int), 16, reflect, int_equals);
    int a = 2;
    int b = 4;
    hash_map_put(&hash_map, &b, &a);
    hash_map_put(&hash_map, &b, &b);
    int c = 2;
    hash_map_put(&hash_map, &c, &a);
    hash_map_remove(&hash_map, &b);
    if (hash_map_contains(&hash_map, &c))
        printf("%d\n", *(int*)hash_map_get(&hash_map, &c));
    if (hash_map_contains(&hash_map, &b))
        printf("%d\n", *(int*)hash_map_get(&hash_map, &b));

    hash_map_deconstruct(&hash_map);
}
