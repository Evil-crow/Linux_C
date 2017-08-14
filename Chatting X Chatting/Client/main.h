#ifndef _MAIN_H
#define _MAIN_H

int sock_fd_create(void);                       //连接套接字创建函数

void work(int sock_fd);                       //传入连接套接字进行工作

void _recv(int sosk_fd);                      //一直进行内容获取的线程

#endif