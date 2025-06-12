# Hashmap:
This is a simple, modern hashmap library written in C with the goal of simplicity.

## Documentation
Available methods:
```c
// NOTE: All values stored must be casted to (void*) pointers to be stored.

void hashmap_destroy(hashmap_t* hashmap);
hashmap_t* hashmap_initialize(void);

uint64_t hashmap_hash_key(char* key);
void* hashmap_get(hashmap_t* hashmap, char* key);

int hashmap_resize(hashmap_t* hashmap);
int hashmap_append(hashmap_t* hashmap, char* key, void* value);
```

## Inclusion:
To include the library, simply utilize the hashmap-library.h file in your project.

## Test:
You can build the test file using **make**.
