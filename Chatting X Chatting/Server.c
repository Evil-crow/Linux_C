#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>

#define LISTENLINE   10                             //等待队列最多10个客户端,超出的会被拒绝
#define SIN_PORT     12121                          //设置绑定的端口

struct sign                   //使用包装好的包进行登录
{
    int choice;               //登录注册处的选项
    char _username[12];        //用户名
    char passwd1[12];         //登录用密码
    char passwd2[12];         //注册确认用密码
};

typedef struct user                                         //用户信息,将用户信息与socket绑定
{
    int sock_fd;
    char username[12];
    struct user *next;       //构建链表使用
}Node;

char name[12];                                       //全局变量用来在链表中查找用户

Node *pHead;                                         //变量头节点

pthread_mutex_t         mutex;                       //声明全局变量互斥锁

void _error(const char *string,int line);           //自用判断错误函数

void menu(int conn_fd);

struct sign sign_in_server(int conn_fd);                   //服务器登录函数

void operation(int conn_fd);                          //开线程,供用户操作

Node *linklist_init(Node *pHead);

Node *linklist_add(Node *pHead,struct sign person,int conn_fd);

Node *linklist_delete(Node *pHead,char *name);

Node *linklist_seek(Node *pHead,char *name);

int main(int argc,char **argv)
{
    int                sock_fd,conn_fd;             //创建sock_fd,以及accept( )后产生的连接用conn_fd
    int                ret,optval;                  //判断函数的返回值,以及setsocket时使用
    struct sockaddr_in serv_addr,cli_addr;          //两个IPV4的结构体,使用时,强制类型转换
    socklen_t          cli_len;                     //进行accept( )时计算要接受的套接字长度
    pthread_t          thid;                        //创建的线程ID
    int                _signal;                     //传递连接畅通的信号

    pHead = linklist_init(pHead);                   //链表的初始化
    pthread_mutex_init(&mutex,NULL);                //初始化互斥量
    /*第一步,创建套接字socket*/
    sock_fd = socket(AF_INET,SOCK_STREAM,0);        //创建IPV4协议族,TCP,的套接字
    if(sock_fd < 0)
        _error("socket",__LINE__);

    /*第二步,设置套接字socket*/
    optval = 1;
    ret = setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int));
    if(ret < 0)
        _error("setsockopt",__LINE__);

    /*第三步,设置对应的套接字地址*/
    bzero(&serv_addr,sizeof(serv_addr));                     //用法含义同memset
    serv_addr.sin_family = AF_INET;                          //设置协议族
    serv_addr.sin_port = htons(SIN_PORT);                    //设置主机地址
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);           //设置任意IP地址

    /*第四步,进行套接字的命名/绑定*/
    ret = bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in));
    if(ret < 0)
        _error("bind",__LINE__);                             //进行命名时,强制类型转换为通用结构体

    /*第五步,进行套接字的监听,转换为被动的套接字*/
    ret = listen(sock_fd,LISTENLINE);                        //转换为被动的/监听套接字,即可以进行监听连接
    if(ret < 0)
        _error("listen",__LINE__);
    
    /*第六步,使用accept( )进行,其中注意会生成新的套接字用于进行通信*/
    cli_len = sizeof(struct sockaddr_in);
    while(1)
    {
        conn_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&cli_len);
        printf("连接:%d\n",conn_fd);
        if(conn_fd < 0)
            _error("accept",__LINE__);
        printf("accept a new client,IP:%s\n",inet_ntoa(cli_addr.sin_addr));
        signal(SIGPIPE,SIG_IGN);

        pthread_create(&thid,NULL,(void *)operation,conn_fd);        //开线程区处理事务
        pthread_detach(thid);
        

    }
    close(sock_fd);
}

void operation(int conn_fd)
{
    struct sign temp;
    temp = sign_in_server(conn_fd);
    pthread_mutex_lock(&mutex);                                    //进行链表操作时上锁
    printf("%d\n",conn_fd);
    pHead = linklist_add(pHead,temp,conn_fd);                      //向全局链表中添加在线成员
    pthread_mutex_lock(&mutex);                                    //进行解锁操作,解除互斥量
    menu(conn_fd);  
}
struct sign sign_in_server(int conn_fd)
{
    int result;
    struct sign temp;
    FILE *fp;                                                        //文件指针
    char username[12],passwd[12];
    printf("%d\n",conn_fd);
    result = recv(conn_fd,&temp,sizeof(struct sign),0);              //接受发送过来的结构体
    switch(temp.choice)
    {
        case 1:                                                      //进行登录
            fp = fopen("/home/Crow/Templates/file/user","r+");
            if(fp == NULL)
                _error("fopen",__LINE__);
            while(!feof(fp))
            {
                fscanf(fp,"%s %s\n",username,passwd);                //读出一组用户名和密码
                if(strcmp(username,temp._username) == 0)             //姓名匹配成功
                {
                    if(linklist_seek(pHead,username))
                    {
                        fclose(fp);
                        result = 3;
                        send(conn_fd,&result,sizeof(int),0);
                        return temp;
                    }
                    if(strcmp(passwd,temp.passwd1) == 0)
                    {
                        fclose(fp);
                        result = 0;
                        send(conn_fd,&result,sizeof(int),0);
                        exit(EXIT_SUCCESS);
                    }
                    else
                    {
                        result = 1;
                        send(conn_fd,&result,sizeof(int),0);
                        exit(EXIT_SUCCESS);
                    }
                }
            }
            result = 2;
            send(conn_fd,&result,sizeof(int),0);
            exit(EXIT_SUCCESS);
            fclose(fp);
            return temp;
        case 2:                                                   //进行注册操作
            fp = fopen("/home/Crow/Templates/file/user","a+");    //打开文件
            while(!feof(fp))                                      //检查重名
            {
                fscanf(fp,"%s %s\n",username,passwd);             //读出用户名以及密码
                if(strcmp(username,temp._username) == 0)
                {
                    result = 4;
                    send(conn_fd,&result,sizeof(int),0);
                    exit(EXIT_SUCCESS);
                }
            }
            if(strcmp(temp.passwd1,temp.passwd2) != 0)            //检查密码一致性
            {
                result = 5;
                send(conn_fd,&result,sizeof(int),0);
                exit(EXIT_SUCCESS);
            }
            fseek(fp,0L,2);                                       //文件指针移动到文件末尾
            fprintf(fp,"%s %s\n",username,passwd);                //将新用户信息写入文件
            fclose(fp);
            exit(EXIT_SUCCESS);                                                
    }

    return temp;
}

void menu(int conn_fd)
{
    printf("Hello World!\n");
}

void _error(const char *string,int line)
{
    printf("Error line:%d\n",line);
    perror(string);
    printf("\n");
    exit(EXIT_FAILURE);
}
