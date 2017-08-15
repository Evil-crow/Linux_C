#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

typedef struct link_user               //链表的节点定义
{
    int conn_fd;
    char name[30];
    struct link_user *next;
}list;                                

list *linkedlist_init(list *pHead);                             //链表初始化函数

list *linkedlist_add(list *pHead,int conn_fd,char *name);       //添加节点函数 

list *linkedlist_del(list *pHead,char *name);                   //节点删除函数

list *linkedlist_seek(list *pHead,char *name);                  //查询节点函数

#endif