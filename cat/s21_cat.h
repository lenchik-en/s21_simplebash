#ifndef S21_SIMPLEBASH_S21_CAT_H
#define S21_SIMPLEBASH_S21_CAT_H

struct s21_cat_flags {
    int s21_cat_line_numbers;      //-n (--number)
    int s21_cat_not_empty_lines;   // -b (--number-nonblank)
    int s21_cat_end_of_line;       // -e -v (-E)
    int s21_cat_squeeze_blank;     // -s (--squeeze-blank)
    int s21_cat_show_tabs;         // -t -tv (-T)
    int s21_cat_show_nonprinting; // -v
};

void parse_flags_short(struct s21_cat_flags *flag_set, char argv);
void parse_flags_long(struct s21_cat_flags *flag_set, char* argv);
struct s21_cat_flags parse_flags(int argc, char **argv);


void print_file(char *name, struct s21_cat_flags flags);
void print_symb(int ch, int *prev, int *line_num, struct s21_cat_flags flags);
int s21_set_s(struct s21_cat_flags flag_set, int ch, int prev, int *emp_lines);
void s21_set_v(int ch);

#endif //S21_SIMPLEBASH_S21_CAT_H
