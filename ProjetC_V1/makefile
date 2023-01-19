main: MotDeRech.o main.o
	gcc -o main main.o MotDeRech.o

MotDeRech.o: MotDeRech.c MotDeRech.h
	gcc -c MotDeRech.c

main.o: main.c MotDeRech.h
	gcc -c main.c
