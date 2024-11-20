#include <stdio.h>
#include <string.h>
#include "s21_grep.h"

#define MAX_LENGTH 1024

void s21_grep (struct s21_grep_flags flag, char *name, const char *pattern) {
    char line[MAX_LENGTH];
    int line_count = 0;
    int match_count = 0;

    FILE *file = fopen(name, "r");
    if (file) {
        while (fgets(line, sizeof(line),file)){
            line_count++;
            if (flag.s21_grep_n == 1 && strstr(line, pattern)) {
                printf("%d %s", line_count, line);
            }
            if (flag.s21_grep_l == 1 && strstr(line, pattern)) {
                printf("%s\n", name);
                return;
            }
            if (flag.s21_grep_c && strstr(line, pattern)) {
                match_count++;
            }
            if (flag.s21_grep_v && !strstr(line, pattern)) {
                printf("%s", line);
            }

        }
        if (flag.s21_grep_c) {
            printf("%d\n", match_count);
        }
    } else {
        perror(name);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not enough or wrong arguments");
    } else {
        int index = 0;
        struct s21_grep_flags flags = parse_flags(argc, argv, &index);
        printf("flags:\n e - %s\n i - %d\n c - %d\n l - %d\n n - %d\n v - %d\n", flags.s21_grep_template,
               flags.s21_grep_i, flags.s21_grep_c, flags.s21_grep_l, flags.s21_grep_n, flags.s21_grep_v);


        for (int i = index - 1; i < argc; i++) {
            if (argv[i][0] != '-')
            s21_grep(flags, argv[i], flags.s21_grep_template);
        }
    }
    return 0;
}