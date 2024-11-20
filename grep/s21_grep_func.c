#include <stdio.h>
#include <string.h>
#include "s21_grep.h"

//void parse_flags(struct s21_grep_flags *flag_set, int argc, char **argv, char *filename) {
//    for (int i = 1; i < argc; i++) {
//        if (argv[i][0] == '-') {
//            for (size_t j = 1; j < strlen(argv[i]);j++) {
//                switch (argv[i][j]) {
//                    case 'e':
//                        if (i + 1 < argc) {
//                            flag_set->s21_grep_template = argv[i + 1];
//                        } else {
//                            perror("requires argument for -e");
//                        }
//                        break;
//                    case 'i':
//                        flag_set->s21_grep_i = 1;
//                        break;
//                    case 'l':
//                        flag_set->s21_grep_l = 1;
//                        break;
//                    case 'c':
//                        flag_set->s21_grep_c = 1;
//                        flag_set->s21_grep_n = 0;
//                        break;
//                    case 'n':
//                        if (flag_set->s21_grep_c != 1) {
//                            flag_set->s21_grep_n = 1;
//                        }
//                        break;
//                    case 'v':
//                        flag_set->s21_grep_v = 1;
//                        break;
//                    default:
//                        break;
//                }
//            }
//        } else if (!flag_set->s21_grep_template) {
//            flag_set->s21_grep_template = argv[i];
//        } else {
//            filename = argv[i];
//        }
//
//        if (!flag_set->s21_grep_template) {
//            perror("No pattern");
//        }
//    }
//}

struct s21_grep_flags parse_flags(int argc, char **argv, int *index) {
    struct s21_grep_flags flag_set = {0,0,0,0,0,0};

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (size_t j = 1; j < strlen(argv[i]);j++) {
                switch (argv[i][j]) {
                    case 'e':
                        if (i + 1 < argc) {
                            flag_set.s21_grep_template = argv[++i];
                        } else {
                            perror("requires argument for -e");
                        }
                        break;
                    case 'i':
                        flag_set.s21_grep_i = 1;
                        break;
                    case 'l':
                        flag_set.s21_grep_l = 1;
                        break;
                    case 'c':
                        flag_set.s21_grep_c = 1;
                        flag_set.s21_grep_n = 0;
                        break;
                    case 'n':
                        if (flag_set.s21_grep_c != 1) {
                            flag_set.s21_grep_n = 1;
                        }
                        break;
                    case 'v':
                        flag_set.s21_grep_v = 1;
                        break;
                    default:
                        break;
                }
            }
        } else if (!flag_set.s21_grep_template) {
            flag_set.s21_grep_template = argv[i];
        } else {
            *index = i;
        }

        if (!flag_set.s21_grep_template) {
            perror("No pattern");
        }
    }

    return flag_set;
}