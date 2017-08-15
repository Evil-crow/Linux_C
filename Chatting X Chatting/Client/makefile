Client : main.o _recv.o sign_in.o sock_fd_create.o 
	gcc main.o _recv.o sign_in.o sock_fd_create.o -o Client -lpthread 
main.o : main.c main.h work.h
	gcc -c main.c main.h work.h -lpthread
_recv.o : _recv.c main.h 
	gcc -c _recv.c main.h 
sign_in.o : sign_in.c struct_node.h 
	gcc -c sign_in.c struct_node.h 
sock_fd_create.o : sock_fd_create.c 
	gcc -c sock_fd_create.c 
clean : 
	rm -rf *.o
	rm -rf *.gch