#include <stdio.h>
#include <stdlib.h>

static int is_delim(char c, const char *delim) {
    while (*delim) {
        if (c == *delim) {
            return 1;
        }
        delim++;
    }
    return 0;
}

char *strtok_r(char *str, const char *delim, char **saveptr) {
    char *start, *end;
    
    if (str == NULL) {
        str = *saveptr;
    }
    
    if (str == NULL) {
        return NULL;
    }
    
    while (*str && is_delim(*str, delim)) {
        str++;
    }
    
    if (*str == '\0') {
        *saveptr = NULL;
        return NULL;
    }
    
    start = str;
    
    while (*str && !is_delim(*str, delim)) {
        str++;
    }
    
    if (*str != '\0') {
        *str = '\0';
        *saveptr = str + 1;
    } else {
        *saveptr = NULL;
    }
    
    return start;
}

int main(void) {
    char buf[] = "hello,world test";
    const char *delim = ", ";
    char *save = NULL;

    char *tok = strtok_r(buf, delim, &save);
    while (tok) {
        printf("%s\n", tok);
        tok = strtok_r(NULL, delim, &save);
    }
    return 0;
}