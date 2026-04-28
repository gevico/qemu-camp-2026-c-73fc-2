#include "myhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash_function(const char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash;
}

HashTable *create_hash_table() {
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));
  if (!table)
    return NULL;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

void free_node(HashNode *node) {
  if (node) {
    free(node->key);
    free(node->value);
    free(node);
  }
}

void free_hash_table(HashTable *table) {
  if (!table)
    return;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode *curr = table->buckets[i];
    while (curr) {
      HashNode *tmp = curr;
      curr = curr->next;
      free_node(tmp);
    }
  }
  free(table);
}

int hash_table_insert(HashTable *table, const char *key, const char *value) {
  if (!table || !key || !value)
    return 0;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  
  HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
  if (!new_node)
    return 0;
  
  new_node->key = (char *)malloc(strlen(key) + 1);
  strcpy(new_node->key, key);
  new_node->value = (char *)malloc(strlen(value) + 1);
  strcpy(new_node->value, value);
  new_node->next = table->buckets[hash];
  table->buckets[hash] = new_node;

  return 1;
}

const char *hash_table_lookup(HashTable *table, const char *key) {
  if (!table || !key)
    return NULL;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[hash];

  while (node) {
    if (strcmp(node->key, key) == 0) {
      return node->value;
    }
    node = node->next;
  }

  return NULL;
}