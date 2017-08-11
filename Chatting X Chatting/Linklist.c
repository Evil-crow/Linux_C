#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct user                                         //用户信息,将用户信息与socket绑定
{
    int sock_fd;
    char username[12];
    struct user *next;       //构建链表使用
}Node;

struct sign                   //使用包装好的包进行登录
{
    int choice;               //登录注册处的选项
    char _username[12];        //用户名
    char passwd1[12];         //登录用密码
    char passwd2[12];         //注册确认用密码
};

extern Node *pHead;

Node *linklist_init(Node *pHead)
{
    pHead = malloc(sizeof(Node));
    pHead->next = NULL;

    return pHead;
}

Node *linklist_add(Node *pHead,struct sign person,int conn_fd)
{
    Node *pNew = NULL;
    Node *pEnd = NULL;

    pEnd = pHead;
    while(pEnd->next != NULL)
        pEnd = pEnd->next;
    
    pNew = malloc(sizeof(Node));
    pNew->sock_fd = conn_fd;
    strcpy(pNew->username,person._username);
    pEnd->next = pNew; 
    pNew->next = NULL;

    free(pNew);
    return pHead;                
}

Node *linklist_delete(Node *pHead,char *name)
{
    Node *temp;
    temp = linklist_delete(pHead,name);
    if(temp != NULL)
    return pHead;
    else
    return NULL;
}

Node *linklist_seek(Node *pHead,char *name)
{
    Node *temp;
    temp = pHead;
    if(pHead == NULL)
    return NULL;
    while(temp != NULL)
    {
        if(strcmp(temp->username,name) == 0)
            return temp;
        temp = temp->next;
    }
    
    return NULL;
}