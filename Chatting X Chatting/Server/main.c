#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"main.h"
#include"Linkedlist.h"

list *pHead;                                //全局链表头节点

void _error(const char *string,int line);

int main(int argc,char **argv)
{
    int listen_fd;                              //监听套接字
    pHead = linkedlist_init(pHead);             //进行链表的初始化
    listen_fd = listen_fd_create( );             //创建监听套接字
    creat("/home/Crow/Public/Information/user",0755);
    creat("/home/Crow/Public/Information/server_log",0755);
    epoll_server(listen_fd);                    //epoll+多线程

    return 0;
}

void _error(const char *string,int line)
{
    printf("Error line:%d",line);
    perror(string);
    printf("\n");
}