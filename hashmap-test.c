// Written by: Christopher Gholmieh
// Headers:
#include <assert.h>
#include <stdlib.h>

#include <string.h>
#include <stdio.h>

// Library:
#include "hashmap-library.h"


// Main:
int main(void) {
    // Variables (Assignment):
    // Hashmap:
    hashmap_t* hashmap = hashmap_initialize();

    // Integer:
    int* integer_value = (int*) malloc(sizeof(int));
    *integer_value = 300;

    // String:
    char* string_value = (char*) malloc(sizeof(char) * 14);
    strncpy(string_value, "Hello, world!", sizeof(char) * 14);

    // Logic:
    hashmap_append(hashmap, "integer-value", (void*) integer_value);
    hashmap_append(hashmap, "string-value", (void*) string_value);

    // Integer:
    printf("%d\n", *(int*) hashmap_get(hashmap, "integer-value"));
    printf("%s\n", (char*) hashmap_get(hashmap, "string-value"));

    // Memory:
    hashmap_destroy(hashmap);

    // Return:
    return 0;
}
