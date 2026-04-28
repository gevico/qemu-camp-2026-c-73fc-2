#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#define HASH_TABLE_SIZE 10000003

typedef struct HashNode {
    char *key;
    char *value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *buckets[HASH_TABLE_SIZE];
} HashTable;

HashTable* create_hash_table();
void free_hash_table(HashTable *table);
int hash_table_insert(HashTable *table, const char *key, const char *value);
const char* hash_table_lookup(HashTable *table, const char *key);
int load_dictionary(const char *filename, HashTable *table, uint64_t* dict_count);

#endif