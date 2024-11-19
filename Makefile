CFLAGS = -Wall -Werror -Wextra -std=c11

all:
	s21_cat

s21_cat:
	gcc s21_cat.o s21_cat_func.o -o s21_cat

s21_cat.o:
	gcc -c $(CFLAGS) s21_cat.c

s21_cat_func.o:
	gcc -c $(CFLAGS) s21_cat_func.c

clean:
	rm *.o s21_cat

rebuild:
	clean all