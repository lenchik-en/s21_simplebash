#ifndef S21_SIMPLEBASH_S21_GREP_H
#define S21_SIMPLEBASH_S21_GREP_H

//1	-e	Шаблон.
//2	-i	Игнорирует различия регистра.
//3	-v	Инвертирует смысл поиска соответствий.
//4	-c	Выводит только количество совпадающих строк.
//5	-l	Выводит только совпадающие файлы.
//6	-n	Предваряет каждую строку вывода номером строки из файла ввода.

struct s21_grep_flags {
    char *s21_grep_template;
    int s21_grep_i;
    int s21_grep_v;
    int s21_grep_c;
    int s21_grep_l;
    int s21_grep_n;
};

//void parse_short_flags(struct s21_grep_flags *flag_set, char argv);
struct s21_grep_flags parse_flags(int argc, char **argv, int *index);

#endif //S21_SIMPLEBASH_S21_GREP_H
