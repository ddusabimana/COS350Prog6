# makefile for prog6

all : lc1 lc2 lc3

lc1:
	gcc -o lc1 lc1.c
lc2:
	gcc -o lc2 lc2.c
lc3:
	gcc -o lc3 lc3.c -lpthread
