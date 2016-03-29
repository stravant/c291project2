
all: main.c database
	gcc -o main main.c database.o -ldb


database: database.h database.c
	gcc -c database.c


run: all
	./main