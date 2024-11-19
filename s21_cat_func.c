#include <string.h>
#include <stdio.h>
#include "s21_cat.h"

void parse_flags_short(struct s21_cat_flags *flag_set, char argv) {
    if (strchr("bevnstET", argv)) {
        switch (argv) {
            case 'b':
                flag_set->s21_cat_not_empty_lines = 1;
                flag_set->s21_cat_line_numbers = 0;
                break;
            case 'e':
                flag_set->s21_cat_end_of_line = 1;
                flag_set->s21_cat_show_nonprinting = 1;
                break;
            case 'E':
                flag_set->s21_cat_end_of_line = 1;
                break;
            case 'v':
                flag_set->s21_cat_show_nonprinting = 1;
                break;
            case 'n':
                if (flag_set->s21_cat_not_empty_lines != 1) {
                    flag_set->s21_cat_line_numbers = 1;
                }
                break;
            case 's':
                flag_set->s21_cat_squeeze_blank = 1;
                break;
            case 't':
                flag_set->s21_cat_show_tabs = 1;
                flag_set->s21_cat_show_nonprinting = 1;
                break;
            case 'T':
                flag_set->s21_cat_show_tabs = 1;
                break;
            default:
                break;
        }
    }
}

void parse_flags_long(struct s21_cat_flags *flag_set, char* argv) {
    if (strcmp("--number-nonblank", argv) == 0) {
        flag_set->s21_cat_not_empty_lines = 1;
        flag_set->s21_cat_end_of_line = 0;
    }
    if (strcmp("--number", argv) == 0 && flag_set->s21_cat_not_empty_lines != 1)
        flag_set->s21_cat_line_numbers = 1;
    if (strcmp("--squeeze-blank", argv) == 0)
        flag_set->s21_cat_squeeze_blank = 1;
}

struct s21_cat_flags parse_flags(int argc, char **argv) {
    struct s21_cat_flags flag_set = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') {
                parse_flags_long(&flag_set, argv[i]);
            }
            else {
                for (size_t j = 0; j < strlen(argv[i]); j++) {
                    parse_flags_short(&flag_set, argv[i][j]);
                }
            }
        }
    }
    return flag_set;
}

void print_symb(int ch, int *prev, int *line_num, struct s21_cat_flags flags) {
    //1 -b (GNU: --number-nonblank)	нумерует только непустые строки
    //2	-e предполагает и -v (GNU only: -E то же самое, но без применения -v)	также отображает символы конца строки как $
    //3	-n (GNU: --number)	нумерует все выходные строки
    //4	-s (GNU: --squeeze-blank)	сжимает несколько смежных пустых строк
    //5	-t предполагает и -v (GNU: -T то же самое, но без применения -v)	также отображает табы как ^

    if (flags.s21_cat_not_empty_lines == 1 && ch != '\n' && *prev == '\n') {
        printf("%d\t", *line_num);
        *line_num += 1;
    }

    if (flags.s21_cat_end_of_line == 1 && ch == '\n') {
        printf("$");
    }

    if (flags.s21_cat_line_numbers == 1  && *prev == '\n') {
        printf("%d\t", *line_num);
        *line_num += 1;
    }

    if (flags.s21_cat_show_tabs == 1 && ch == '\t') {
        printf("^");
    }

    printf("%c", ch);
}

int s21_set_s(struct s21_cat_flags flag_set, int ch, int prev, int *emp_lines) {
    int res = 0;
    if (flag_set.s21_cat_squeeze_blank == 1){
        if (ch == '\n' && prev == '\n') {
            (*emp_lines)++;
        } else {
            *emp_lines = 0;
        }

        if (*emp_lines > 1) res = 1;
    }

    return res;
}

void print_file(char *name, struct s21_cat_flags flags) {
    //check_directories

    FILE *file = fopen(name, "r");

    if (file) {
        int ch;
        int prev_ch = '\n';
        int emp_line = 0;
        int line_number = 1;
        while ((ch = fgetc(file)) != EOF) {
            if(s21_set_s(flags, ch, prev_ch, &emp_line)) {
                continue;
            }

            print_symb(ch, &prev_ch, &line_number, flags);

            prev_ch = ch;
        }
        printf("\n");
    } else
        perror(name);

    fclose(file);
}
