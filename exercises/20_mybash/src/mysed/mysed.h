#ifndef MYSED_H
#define MYSED_H

int parse_replace_command(const char* cmd, char** old_str, char** new_str);
void replace_first_occurrence(char* str, const char* old, const char* new);
int mysed_main(int argc, char* argv[]);

#endif