string : main.o result.o
	gcc main.o result.o -o string
mian.o : main.c  stdio.h string.h
	gcc -c main.c stdio.h string.h
result.o : result.c string.h
	gcc -c result.c string.h

# This is an easy makefile about string
