#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<unistd.h>

#define LISTENLINE   10                             //等待队列最多10个客户端,超出的会被拒绝
#define SIN_PORT     12121                          //设置绑定的端口

struct sign                   //使用包装好的包进行登录
{
    int choice;               //登录注册处的选项
    char username[12];        //用户名
    char passwd1[12];         //登录用密码
    char passwd2[12];         //注册确认用密码
};

void _error(const char *string,int line);           //自用判断错误函数

void menu(void *arg);

struct user                                         //用户信息,将用户信息与socket绑定
{
    int sock_fd;
    char name[20];
};
int main(int argc,char **argv)
{
    int                sock_fd,conn_fd;             //创建sock_fd,以及accept( )后产生的连接用conn_fd
    int                ret,optval;                  //判断函数的返回值,以及setsocket时使用
    struct sockaddr_in serv_addr,cli_addr;          //两个IPV4的结构体,使用时,强制类型转换
    socklen_t          cli_len;                     //进行accept( )时计算要接受的套接字长度
    pthread_t          thid;                        //创建的线程ID
    int                _signal;                     //传递连接畅通的信号

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
        if(conn_fd < 0)
            _error("accept",__LINE__);
        printf("accept a new client,IP:%s\n",inet_ntoa(cli_addr.sin_addr));
        pthread_create(&thid,NULL,menu,(void *)&conn_fd);
        pthread_detach(thid);
        close(conn_fd);
        
    }
    close(sock_fd);
}

/*void menu(void *arg)
{

}*/

void _error(const char *string,int line)
{
    printf("Error line:%d\n",line);
    perror(string);
    printf("\n");
    exit(EXIT_FAILURE);
}