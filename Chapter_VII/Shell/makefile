shell : main.o explain.o find.o get.o go.o print.o
	gcc main.o explain.o find.o get.o go.o print.o -o shell
main.o : main.c
	gcc -c main.c 
explain.o : explain_command.c
	gcc -c explain_command.c -o explain.o
find.o : find_command.c
	gcc -c find_command.c -o find.o
get.o : get_command.c
	gcc -c get_command.c -o get.o
go.o : go_command.c
	gcc -c go_command.c -o go.o
print.o : print_shell.c
	gcc -c print_shell.c -o print.o

clean : 
	   rm -rf *.o
