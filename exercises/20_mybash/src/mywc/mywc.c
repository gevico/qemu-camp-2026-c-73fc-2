#include "mywc.h"

WordCount **mywc_create_hash_table() {
  WordCount **hash_table = calloc(HASH_SIZE, sizeof(WordCount *));
  return hash_table;
}

unsigned int mywc_hash(const char *word) {
  unsigned long hash = 5381;
  int c;
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c;
  return hash % HASH_SIZE;
}

bool mywc_is_valid_word_char(char c) { return isalpha(c) || c == '\''; }

char mywc_to_lower(char c) { return tolower(c); }

void mywc_add_word(WordCount **hash_table, const char *word) {
    unsigned int idx = mywc_hash(word);
    WordCount *curr = hash_table[idx];
    while (curr) {
        if (strcmp(curr->word, word) == 0) {
            curr->count++;
            return;
        }
        curr = curr->next;
    }
    WordCount *new_node = (WordCount*)malloc(sizeof(WordCount));
    if (!new_node) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    strncpy(new_node->word, word, MAX_WORD_LEN - 1);
    new_node->word[MAX_WORD_LEN - 1] = '\0';
    new_node->count = 1;
    new_node->next = hash_table[idx];
    hash_table[idx] = new_node;
}

void mywc_print_word_counts(WordCount **hash_table) {
  int total = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordCount *p = hash_table[i];
        while (p) {
            total++;
            p = p->next;
        }
    }
    if (total == 0) return;

    WordCount **arr = (WordCount**)malloc(total * sizeof(WordCount*));
    if (!arr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    int idx = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordCount *p = hash_table[i];
        while (p) {
            arr[idx++] = p;
            p = p->next;
        }
    }
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (strcmp(arr[i]->word, arr[j]->word) > 0) {
                WordCount *tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    for (int i = 0; i < total; i++) {
        printf("%-20s %d\n", arr[i]->word, arr[i]->count);
    }
    free(arr);
}

void mywc_free_hash_table(WordCount **hash_table) {
    if (!hash_table) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordCount *p = hash_table[i];
        while (p) {
            WordCount *next = p->next;
            free(p);
            p = next;
        }
    }
    free(hash_table);
}

void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  WordCount **hash_table = mywc_create_hash_table();
  char word[MAX_WORD_LEN];
  int word_pos = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (mywc_is_valid_word_char(c)) {
      if (word_pos < MAX_WORD_LEN - 1) {
        word[word_pos++] = mywc_to_lower(c);
      }
    } else {
      if (word_pos > 0) {
        word[word_pos] = '\0';
        mywc_add_word(hash_table, word);
        word_pos = 0;
      }
    }
  }

  if (word_pos > 0) {
    word[word_pos] = '\0';
    mywc_add_word(hash_table, word);
  }

  fclose(file);
  mywc_print_word_counts(hash_table);
  mywc_free_hash_table(hash_table);
}

int mywc_main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: mywc <file>\n");
    return 1;
  }
  process_file(argv[1]);
  return 0;
}