// Written by: Christopher Gholmieh
// Guards:
#ifndef __HASHMAP_LIBRARY_H__
#define __HASHMAP_LIBRARY_H__

// Constants:
#ifndef UNSUCCESFUL_OPERATION
    #define UNSUCCESSFUL_OPERATION -1
#endif

#ifndef SUCCESFUL_OPERATION
    #define SUCCESSFUL_OPERATION 1
#endif

// Headers:
#include <stdint.h>
#include <stdlib.h>

#include <string.h>
#include <stdio.h>

// Structures:
typedef struct {
    /* Capacity: */
    size_t capacity;

    /* Length: */
    size_t length;

    /* Values: */
    void** values;

    /* Keys: */
    char** keys;
} hashmap_t;

// Functions:
void hashmap_destroy(hashmap_t* hashmap);
hashmap_t* hashmap_initialize(void);

uint64_t hashmap_hash_key(char* key);
void* hashmap_get(hashmap_t* hashmap, char* key);

int hashmap_resize(hashmap_t* hashmap);
int hashmap_append(hashmap_t* hashmap, char* key, void* value);

// Functions:
inline hashmap_t* hashmap_initialize(void) {
    // Variables (Assignment):
    // Hashmap:
    hashmap_t* hashmap = (hashmap_t*) malloc(sizeof(hashmap_t));

    if (hashmap == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for hashmap.\n");

        // Return:
        return NULL;
    }

    // Capacity:
    hashmap->capacity = 4;

    // Length:
    hashmap->length = 0;

    // Values:
    hashmap->values = (void**) malloc(sizeof(void*) * hashmap->capacity);

    if (hashmap->values == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for values.\n");

        // Memory:
        free(hashmap);

        // Return:
        return NULL;
    }

    memset(hashmap->values, 0, sizeof(void*) * hashmap->capacity);

    // Keys:
    hashmap->keys = (char**) malloc(sizeof(char*) * hashmap->capacity);

    if (hashmap->keys == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for values.\n");

        // Memory:
        free(hashmap->values);
        free(hashmap);

        // Return:
        return NULL;
    }

    memset(hashmap->keys, 0, sizeof(char*) * hashmap->capacity);

    // Logic:
    return hashmap;
}

inline uint64_t hashmap_hash_key(char* key) {
    // Variables (Assignment):
    // Prime:
    uint64_t fnv_prime = 1099511628211ULL;

    // Hash:
    uint64_t hash = 14695981039346656037ULL;

    // Logic:
    while (*key != '\0') {
        // XOR:
        hash = hash ^ *key;

        // Multiply:
        hash = hash * fnv_prime;

        // Increment:
        key++;
    }

    return hash;
}

inline int hashmap_resize(hashmap_t* hashmap) {
    // Variables (Assignment):
    // Capacity:
    size_t updated_capacity = hashmap->capacity * 2;

    // Values:
    void** updated_values = (void**) malloc(sizeof(void*) * updated_capacity);

    if (updated_values == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for updated values.\n");

        // Return:
        return UNSUCCESSFUL_OPERATION;
    }

    memset(updated_values, 0, sizeof(void*) * updated_capacity);

    // Keys:
    char** updated_keys = (char**) malloc(sizeof(char*) * updated_capacity);

    if (updated_keys == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to allocate memory for updated keys.\n");

        // Memory:
        free(updated_values);

        // Return:
        return UNSUCCESSFUL_OPERATION;
    }

    // Logic:
    for (size_t iterator = 0; iterator < hashmap->length; iterator++) {
        if (hashmap->keys[iterator] != NULL) {
            // Variables (Assignment):
            // Value:
            void* value = hashmap->values[iterator];

            // Key:
            char* key = hashmap->keys[iterator];

            // Bucket:
            size_t bucket = hashmap_hash_key(key) & (updated_capacity - 1);

            // Logic:
            while (updated_keys[bucket] != NULL) {
                bucket = (bucket + 1) & (updated_capacity - 1);
            }

            updated_values[bucket] = value;
            updated_keys[bucket] = key;
        }
    }

    // Memory:
    free(hashmap->values);
    free(hashmap->keys);

    // Logic:
    hashmap->capacity = updated_capacity;
    hashmap->values = updated_values;
    hashmap->keys = updated_keys;

    return SUCCESSFUL_OPERATION;
}

inline int hashmap_append(hashmap_t *hashmap, char* key, void *value) {
    // Resize:
    if (hashmap->length >= hashmap->capacity * 0.75) {
        if (hashmap_resize(hashmap) == UNSUCCESSFUL_OPERATION) {
            // Message:
            fprintf(stderr, "[!] Unable to resize hashmap to fit more elements.\n");

            // Return:
            return UNSUCCESSFUL_OPERATION;
        }
    }


    // Variables (Assignment):
    // Duplicate:
    char* duplicate = strdup(key);

    if (duplicate == NULL) {
        // Message:
        fprintf(stderr, "[!] Unable to create duplicate copy of key for lifetime.\n");

        // Return:
        return UNSUCCESSFUL_OPERATION;
    }

    // Bucket:
    size_t bucket = hashmap_hash_key(key) & (hashmap->capacity - 1);

    // Logic:
    while (hashmap->keys[bucket] != NULL) {
        if (strcmp(hashmap->keys[bucket], key) == 0) {
            hashmap->values[bucket] = value;

            return SUCCESSFUL_OPERATION;
        }

        bucket = (bucket + 1) & (hashmap->capacity - 1);
    }

    hashmap->values[bucket] = value;
    hashmap->keys[bucket] = duplicate;

    return SUCCESSFUL_OPERATION;
}

inline void* hashmap_get(hashmap_t* hashmap, char* key) {
    // Variables (Assignment):
    // Bucket:
    size_t bucket = hashmap_hash_key(key) & (hashmap->capacity - 1);

    // Logic:
    for (size_t iterator = 0; iterator < hashmap->capacity; iterator++) {
        // Variables (Assignment):
        // Index:
        size_t index = (bucket + iterator) & (hashmap->capacity - 1);

        // Logic:
        if (hashmap->keys[index] != NULL && hashmap->values[index] != NULL) {
            if (strcmp(hashmap->keys[index], key) == 0) {
                return hashmap->values[index];
            }
        }
    }

    // Error:
    fprintf(stderr, "[!] Unable to locate key-value pair in hashmap.\n");

    return NULL;
}

inline void hashmap_destroy(hashmap_t* hashmap) {
    for (size_t iterator = 0; iterator < hashmap->capacity; iterator++) {
        if (hashmap->values[iterator] != NULL) {
            free(hashmap->values[iterator]);
        }

        if (hashmap->keys[iterator] != NULL) {
            free(hashmap->keys[iterator]);
        }
    }

    free(hashmap->values);
    free(hashmap->keys);

    free(hashmap);
}

// Guard:
#endif /** __HASHMAP_LIBRARY_H__ */
