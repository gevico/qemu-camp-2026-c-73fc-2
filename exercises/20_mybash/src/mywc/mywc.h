#ifndef MYWC_H
#define MYWC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LEN 128
#define HASH_SIZE 1000

typedef struct WordCount {
    char word[MAX_WORD_LEN];
    int count;
    struct WordCount *next;
} WordCount;

void process_file(const char *filename);
WordCount **mywc_create_hash_table();
unsigned int mywc_hash(const char *word);
void mywc_add_word(WordCount **hash_table, const char *word);
void mywc_print_word_counts(WordCount **hash_table);
void mywc_free_hash_table(WordCount **hash_table);
bool mywc_is_valid_word_char(char c);
char mywc_to_lower(char c);
int mywc_main(int argc, char* argv[]);

#endif