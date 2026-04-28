#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LRUNode {
    int key;
    int value;
    struct LRUNode* prev;
    struct LRUNode* next;
} LRUNode;

typedef struct HashEntry {
    int key;
    LRUNode* node;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    int capacity;
    int size;
    LRUNode* head;
    LRUNode* tail;
    size_t bucket_count;
    HashEntry** buckets;
} LRUCache;

static unsigned hash_int(int key) {
    unsigned int hash = (unsigned int)key;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;
    return hash;
}

static HashEntry* hash_find(LRUCache* c, int key, HashEntry*** pprev_next) {
    unsigned idx = hash_int(key) % c->bucket_count;
    HashEntry** pp = &c->buckets[idx];
    
    while (*pp) {
        if ((*pp)->key == key) {
            if (pprev_next) {
                *pprev_next = pp;
            }
            return *pp;
        }
        pp = &(*pp)->next;
    }
    
    return NULL;
}

static void list_add_to_head(LRUCache* c, LRUNode* node) {
    node->prev = NULL;
    node->next = c->head;
    
    if (c->head) {
        c->head->prev = node;
    } else {
        c->tail = node;
    }
    c->head = node;
}

static void list_remove(LRUCache* c, LRUNode* node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        c->head = node->next;
    }
    
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        c->tail = node->prev;
    }
}

static void list_move_to_head(LRUCache* c, LRUNode* node) {
    list_remove(c, node);
    list_add_to_head(c, node);
}

static LRUNode* list_pop_tail(LRUCache* c) {
    LRUNode* tail = c->tail;
    if (tail) {
        list_remove(c, tail);
    }
    return tail;
}

static LRUCache* lru_create(int capacity) {
    LRUCache* c = (LRUCache*)malloc(sizeof(LRUCache));
    if (!c) return NULL;
    
    c->capacity = capacity;
    c->size = 0;
    c->head = NULL;
    c->tail = NULL;
    c->bucket_count = capacity * 2;
    c->buckets = (HashEntry**)calloc(c->bucket_count, sizeof(HashEntry*));
    
    if (!c->buckets) {
        free(c);
        return NULL;
    }
    
    return c;
}

static void lru_free(LRUCache* c) {
    if (!c) return;
    
    LRUNode* node = c->head;
    while (node) {
        LRUNode* next = node->next;
        free(node);
        node = next;
    }
    
    for (size_t i = 0; i < c->bucket_count; i++) {
        HashEntry* entry = c->buckets[i];
        while (entry) {
            HashEntry* next = entry->next;
            free(entry);
            entry = next;
        }
    }
    
    free(c->buckets);
    free(c);
}

static int lru_get(LRUCache* c, int key, int* out_value) {
    HashEntry* entry = hash_find(c, key, NULL);
    if (!entry) {
        return 0;
    }
    
    if (out_value) {
        *out_value = entry->node->value;
    }
    
    list_move_to_head(c, entry->node);
    return 1;
}

static void lru_put(LRUCache* c, int key, int value) {
    HashEntry* entry = hash_find(c, key, NULL);
    
    if (entry) {
        entry->node->value = value;
        list_move_to_head(c, entry->node);
        return;
    }
    
    LRUNode* new_node = (LRUNode*)malloc(sizeof(LRUNode));
    if (!new_node) return;
    
    new_node->key = key;
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    
    unsigned idx = hash_int(key) % c->bucket_count;
    HashEntry* new_entry = (HashEntry*)malloc(sizeof(HashEntry));
    if (!new_entry) {
        free(new_node);
        return;
    }
    
    new_entry->key = key;
    new_entry->node = new_node;
    new_entry->next = c->buckets[idx];
    c->buckets[idx] = new_entry;
    
    list_add_to_head(c, new_node);
    c->size++;
    
    if (c->size > c->capacity) {
        LRUNode* removed = list_pop_tail(c);
        if (removed) {
            HashEntry** pprev_next;
            entry = hash_find(c, removed->key, &pprev_next);
            if (entry && pprev_next) {
                *pprev_next = entry->next;
                free(entry);
            }
            free(removed);
            c->size--;
        }
    }
}

static void lru_print(LRUCache* c) {
    LRUNode* p = c->head;
    int first = 1;
    while (p) {
        if (!first) printf(", ");
        first = 0;
        printf("%d:%d", p->key, p->value);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    LRUCache* c = lru_create(3);
    if (!c) {
        fprintf(stderr, "创建 LRU 失败\n");
        return 1;
    }

    lru_put(c, 1, 1);
    lru_put(c, 2, 2);
    lru_put(c, 3, 3);
    lru_put(c, 4, 4);

    int val;
    if (lru_get(c, 2, &val)) {
        (void)val;
    }

    lru_put(c, 5, 5);

    lru_print(c);

    lru_free(c);
    return 0;
}