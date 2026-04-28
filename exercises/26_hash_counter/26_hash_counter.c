#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1024

typedef struct HashNode {
    char *word;
    int count;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **table;
    int size;
} HashTable;

unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
}

HashTable *create_hash_table(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->table = calloc(size, sizeof(HashNode *));
    ht->size = size;
    return ht;
}

void hash_table_insert(HashTable *ht, const char *word) {
    unsigned long hash = djb2_hash(word) % ht->size;
    
    HashNode *current = ht->table[hash];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }
    
    HashNode *new_node = malloc(sizeof(HashNode));
    new_node->word = strdup(word);
    new_node->count = 1;
    new_node->next = ht->table[hash];
    ht->table[hash] = new_node;
}

void get_all_words(HashTable *ht, HashNode **nodes, int *count) {
    *count = 0;
    
    for (int i = 0; i < ht->size; i++) {
        HashNode *node = ht->table[i];
        while (node != NULL) {
            nodes[(*count)++] = node;
            node = node->next;
        }
    }
}

int compare_nodes(const void *a, const void *b) {
    HashNode *node_a = *(HashNode **)a;
    HashNode *node_b = *(HashNode **)b;
    
    if (node_b->count != node_a->count) {
        return node_b->count - node_a->count;
    }
    
    return strcmp(node_a->word, node_b->word);
}

void free_hash_table(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        HashNode *node = ht->table[i];
        while (node != NULL) {
            HashNode *temp = node;
            node = node->next;
            free(temp->word);
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

char *get_next_word(const char **text) {
    while (**text != '\0' && !isalpha(**text)) {
        (*text)++;
    }
    
    if (**text == '\0') {
        return NULL;
    }
    
    const char *start = *text;
    while (**text != '\0' && isalpha(**text)) {
        (*text)++;
    }
    
    int length = *text - start;
    char *word = malloc(length + 1);
    strncpy(word, start, length);
    word[length] = '\0';
    
    for (int i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);
    }
    
    return word;
}

int main(int argc, char *argv[]) {
    const char* file_path = "paper.txt";

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }

    HashTable *ht = create_hash_table(TABLE_SIZE);
    char buffer[4096];
    
    printf("正在读取文件: %s\n", file_path);
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        const char *ptr = buffer;
        char *word;
        
        while ((word = get_next_word(&ptr)) != NULL) {
            hash_table_insert(ht, word);
            free(word);
        }
    }
    
    fclose(file);
    
    HashNode **nodes = malloc(TABLE_SIZE * sizeof(HashNode *));
    int node_count = 0;
    get_all_words(ht, nodes, &node_count);
    
    qsort(nodes, node_count, sizeof(HashNode *), compare_nodes);
    
    printf("\n单词统计结果（按频率降序排列）:\n");
    printf("%-20s %s\n", "单词", "出现次数");
    printf("-------------------- ----------\n");
    for (int i = 0; i < node_count; i++) {
        printf("%s:%d\n", nodes[i]->word, nodes[i]->count);
    }
    
    free(nodes);
    free_hash_table(ht);
    
    return 0;
}