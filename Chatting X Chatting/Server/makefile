Server : main.o epoll_server.o listen_fd_creat.o menu.o sign_register.o Linkedlist.o
	gcc main.o epoll_server.o listen_fd_creat.o menu.o sign_register.o Linkedlist.o -o Server -lpthread
main.o : main.c main.h Linkedlist.c Linkedlist.h
	gcc -c main.c main.h Linkedlist.h Linkedlist.c -lpthread
epoll_server.o : epoll_server.c epoll_server.h main.h
	gcc -c epoll_server.c epoll_server.h main.h -lpthread
listen_fd_creat.o : listen_fd_creat.c main.h
	gcc -c listen_fd_creat.c main.h
menu.o : menu.c menu.h main.h
	gcc -c menu.c menu.h main.h 
sign_register.o : sign_register.c menu.h Linkedlist.h Linkedlist.c 
	gcc -c sign_register.c menu.h Linkedlist.h Linkedlist.c 
clean : 
	rm -rf *.o
	rm -rf *.gch