#include <stdio.h>
#include <string.h>
#include "s21_cat.h"

int main(int argc, char* argv[]) {
    if (argc < 3 || strcmp(argv[1], "cat") != 0) {
        printf("Not enough or wrong arguments");
    } else {
        struct s21_cat_flags flags;
        //находим файлы
        flags = parse_flags(argc, argv);
        printf("e - %d \ns - %d\nn - %d\nb - %d\nt - %d\nv - %d\n", flags.s21_cat_end_of_line,
               flags.s21_cat_squeeze_blank, flags.s21_cat_line_numbers, flags.s21_cat_not_empty_lines,
               flags.s21_cat_show_tabs, flags.s21_cat_show_nonprinting);

        for (int i = 2; i < argc; i++) {
            if (argv[i][0] != '-') print_file(argv[i], flags);
        }

    }
    return 0;
}
