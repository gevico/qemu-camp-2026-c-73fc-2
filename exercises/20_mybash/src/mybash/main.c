#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../myfile/myfile.h"
#include "../mysed/mysed.h"
#include "../mywc/mywc.h"

extern int mytrans_main(int argc, char* argv[]);

#define MAX_LINE_LEN 1024
#define MAX_ARGS 64

void trim(char *str) {
    if (!str) return;
    char *start = str;
    while (isspace((unsigned char)*start)) start++;
    if (*start == '\0') {
        *str = '\0';
        return;
    }
    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    memmove(str, start, end - start + 2);
}

char** parse_command(char *line, int *argc) {
    *argc = 0;
    char **argv = malloc(MAX_ARGS * sizeof(char*));
    if (!argv) return NULL;

    int len = strlen(line);
    int i = 0;
    while (i < len && *argc < MAX_ARGS - 1) {
        while (i < len && (line[i] == ' ' || line[i] == '\t')) i++;
        if (i >= len) break;

        int start = i;
        int in_quote = 0;
        char quote_char = '\0';

        if (line[i] == '"' || line[i] == '\'') {
            quote_char = line[i];
            in_quote = 1;
            i++;
            start = i;
        }

        while (i < len) {
            if (in_quote) {
                if (line[i] == quote_char) {
                    in_quote = 0;
                    i++;
                    break;
                }
            } else {
                if (line[i] == ' ' || line[i] == '\t') {
                    break;
                }
            }
            i++;
        }

        int arg_len = in_quote ? (i - start) : (i - start);
        if (in_quote) arg_len--;
        char *arg = malloc(arg_len + 1);
        strncpy(arg, line + start, arg_len);
        arg[arg_len] = '\0';
        argv[(*argc)++] = arg;
    }
    argv[*argc] = NULL;

    return argv;
}

void free_argv(char **argv, int argc) {
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);
}

int execute_command(char **argv, int argc) {
    if (argc == 0) return 0;

    if (strcmp(argv[0], "myfile") == 0) {
        return myfile_main(argc, argv);
    } else if (strcmp(argv[0], "mysed") == 0) {
        return mysed_main(argc, argv);
    } else if (strcmp(argv[0], "mytrans") == 0) {
        return mytrans_main(argc, argv);
    } else if (strcmp(argv[0], "mywc") == 0) {
        return mywc_main(argc, argv);
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[0]);
        return 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: mybash <script_file>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Cannot open script file");
        return 1;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n\r")] = '\0';
        trim(line);

        if (strlen(line) == 0) {
            printf("\n");
            continue;
        }

        int cmd_argc;
        char **cmd_argv = parse_command(line, &cmd_argc);
        if (cmd_argv) {
            execute_command(cmd_argv, cmd_argc);
            free_argv(cmd_argv, cmd_argc);
        }
        printf("\n");
    }

    fclose(file);
    return 0;
}