#include "mywc.h"

// 创建哈希表
WordCount **create_hash_table() {
  WordCount **hash_table = calloc(HASH_SIZE, sizeof(WordCount *));
  return hash_table;
}

// 简单的哈希函数
unsigned int hash(const char *word) {
  unsigned long hash = 5381;
  int c;
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % HASH_SIZE;
}

// 检查字符是否构成单词的一部分
bool is_valid_word_char(char c) { return isalpha(c) || c == '\''; }

// 转换为小写
char to_lower(char c) { return tolower(c); }

// 添加单词到哈希表
void add_word(WordCount **hash_table, const char *word) {
    // TODO: 在这里添加你的代码
    unsigned int idx = hash(word);
    WordCount *curr = hash_table[idx];
    while (curr) {
        if (strcmp(curr->word, word) == 0) {
            curr->count++;
            return;
        }
        curr = curr->next;
    }
    // 未找到，创建新节点（头插法）
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

// 打印单词统计结果
void print_word_counts(WordCount **hash_table) {
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
    // 按单词字典序排序
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (strcmp(arr[i]->word, arr[j]->word) > 0) {
                WordCount *tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    // 输出，单词左对齐15字符，次数右对齐（保证对齐）
    for (int i = 0; i < total; i++) {
        printf("%-20s %d\n", arr[i]->word, arr[i]->count);
    }
    free(arr);
}

// 释放哈希表内存
void free_hash_table(WordCount **hash_table) {
    // TODO: 在这里添加你的代码
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

// 处理文件并统计单词
void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  WordCount **hash_table = create_hash_table();
  char word[MAX_WORD_LEN];
  int word_pos = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (is_valid_word_char(c)) {
      if (word_pos < MAX_WORD_LEN - 1) {
        word[word_pos++] = to_lower(c);
      }
    } else {
      if (word_pos > 0) {
        word[word_pos] = '\0';
        add_word(hash_table, word);
        word_pos = 0;
      }
    }
  }

  // 处理文件末尾的最后一个单词
  if (word_pos > 0) {
    word[word_pos] = '\0';
    add_word(hash_table, word);
  }

  fclose(file);
  print_word_counts(hash_table);
  free_hash_table(hash_table);
}
