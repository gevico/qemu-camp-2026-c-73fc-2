#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // TODO: 在这里添加你的代码
    const char* old_start = cmd + 2;
    const char* old_end = strchr(old_start, '/');
    if (!old_end) return -1;

    // 查找第三个 '/' 分隔 new
    const char* new_start = old_end + 1;
    const char* new_end = strchr(new_start, '/');
    if (!new_end) return -1;

    // 提取 old
    size_t old_len = old_end - old_start;
    *old_str = (char*)malloc(old_len + 1);
    if (!*old_str) return -1;
    memcpy(*old_str, old_start, old_len);
    (*old_str)[old_len] = '\0';

    // 提取 new
    size_t new_len = new_end - new_start;
    *new_str = (char*)malloc(new_len + 1);
    if (!*new_str) {
        free(*old_str);
        return -1;
    }
    memcpy(*new_str, new_start, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // TODO: 在这里添加你的代码
    if (!str || !old || !new) return;
    size_t old_len = strlen(old);
    if (old_len == 0) return;

    char* pos = strstr(str, old);
    if (!pos) return;

    size_t new_len = strlen(new);
    size_t tail_len = strlen(pos + old_len);

    // 计算替换后需要的位移
    if (new_len > old_len) {
        // 向后移动尾部
        memmove(pos + new_len, pos + old_len, tail_len + 1);
    } else if (new_len < old_len) {
        // 向前移动尾部
        memmove(pos + new_len, pos + old_len, tail_len + 1);
    }
    // 复制 new 字符串
    memcpy(pos, new, new_len);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
