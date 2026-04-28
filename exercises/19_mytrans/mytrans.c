// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
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

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
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
    trim(line);
    
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