#compile main.c
main : main.o
	gcc -o main main.o -Wall

main.o : main.c
	gcc -c main.c

#compile main and launch with valgrind

valgrind :
	gcc -o main main.c -g -Wall -Wextra
	valgrind ./main