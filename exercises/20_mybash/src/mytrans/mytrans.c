#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mytrans_trim(char *str) {
    if (!str) return;
    
    int start = 0;
    int end = strlen(str) - 1;
    
    while (start <= end && isspace((unsigned char)str[start])) {
        start++;
    }
    
    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }
    
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

int load_dictionary(const char *filename, HashTable *table, uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;
  *dict_count = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n\r")] = '\0';
    mytrans_trim(line);
    
    if (line[0] == '\0') continue;
    
    if (line[0] == '#') {
      if (in_entry && current_word[0] != '\0' && current_translation[0] != '\0') {
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
      }
      
      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
      current_translation[0] = '\0';
      in_entry = 1;
    } else if (strncmp(line, "Trans:", 6) == 0) {
      strncpy(current_translation, line + 6, sizeof(current_translation) - 1);
      current_translation[sizeof(current_translation) - 1] = '\0';
    } else if (in_entry && current_translation[0] != '\0') {
      strncat(current_translation, "@", sizeof(current_translation) - strlen(current_translation) - 1);
      strncat(current_translation, line, sizeof(current_translation) - strlen(current_translation) - 1);
    }
  }

  if (in_entry && current_word[0] != '\0' && current_translation[0] != '\0') {
    hash_table_insert(table, current_word, current_translation);
    (*dict_count)++;
  }

  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int mytrans_main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: mytrans <text_file>\n");
    return 1;
  }

  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  uint64_t dict_count = 0;
  char dict_path[512];
  const char* text_dir = argv[1];
  char* last_slash = strrchr(text_dir, '/');
  if (last_slash) {
    strncpy(dict_path, text_dir, last_slash - text_dir + 1);
    dict_path[last_slash - text_dir + 1] = '\0';
  } else {
    strcpy(dict_path, "./");
  }
  strcat(dict_path, "dict.txt");
  
  FILE* dict_file = fopen(dict_path, "r");
  if (!dict_file) {
      snprintf(dict_path, sizeof(dict_path), "src/mytrans/dict.txt");
      dict_file = fopen(dict_path, "r");
  }
  if (!dict_file) {
      snprintf(dict_path, sizeof(dict_path), "../exercises/20_mybash/src/mytrans/dict.txt");
      dict_file = fopen(dict_path, "r");
  }
  if (dict_file) {
      fclose(dict_file);
  }
  
  if (load_dictionary(dict_path, table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }

  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 %s。\n", argv[1]);
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    char *token = strtok(line, " ");
    while (token != NULL) {
        char word[256];
        strncpy(word, token, sizeof(word) - 1);
        word[sizeof(word) - 1] = '\0';
        to_lowercase(word);

        const char *translation = hash_table_lookup(table, word);
        if (translation != NULL) {
            printf("原文: %s\t翻译: %s\n", token, translation);
        } else {
            printf("原文: %s\t未找到该单词的翻译。\n", token);
        }

        token = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  fclose(file);
  return 0;
}