#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct sign                   //使用包装好的包进行登录
{
    int choice;               //登录注册处的选项
    char username[12];        //用户名
    char passwd1[12];         //登录用密码
    char passwd2[12];         //注册确认用密码
};
void _error(const char *string,int line);

int sign_in_menu(int sock_fd);

int main(int argc,char **argv)
{
    int                       sock_fd;
    struct sockaddr_in        cli_addr;
    int                       ret;
    int                       result;                           //登录注册返回的结果

    if(argc < 3)
    {
        printf("Error1!\n");
        exit(EXIT_FAILURE);
    }
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
        _error("socket",__LINE__);
    
    memset(&cli_addr,0,sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(atoi(argv[2]));       //设置端口
    inet_aton(argv[1],&cli_addr.sin_addr);          //设置IP地址

    printf("正在尝试连接服务器.....\n");
    ret = connect(sock_fd,(struct sockaddr *)&cli_addr,sizeof(struct sockaddr));
    if(ret < 0)
        _error("connect",__LINE__);
    sleep(1);
    printf("连接成功\n");
    result = sign_in_menu(sock_fd);
    if(result != 0)
    {
        if(result == 1)
        printf("密码错误\n");
        if(result == 2)
        printf("此用户不存在\n");
        if(result == 3)
        printf("此用户已登录/存在\n");
        exit(0);
    }
    printf("登录用户成功!\n");
    getchar( );
    system("cls");                                  //清屏
    
    close(sock_fd);

    return 0;

}

void _error(const char *string,int line)
{
    printf("Error line: %d",line);
    perror(string);
    printf("\n");
    exit(EXIT_FAILURE);
}

int sign_in_menu(int sock_fd)
{
    int           choice;
    struct sign   user;                     //使用的结构体
    int result;
    printf("============================================================\n\n");
    printf("                          1.Sign_in\n\n");
    printf("                          2.Register\n\n");
    printf("                          3.Quit\n\n");
    printf("============================================================\n\n");
    memset(&user,0,sizeof(struct sign));                    //初始化结构体
    scanf("%d",&user.choice);
    switch(choice)
    {
        case 1:
            printf("请输入用户名(12位):");
            scanf("%s",user.username);
            printf("请输入密码(12位):");
            system("stty -echo");                           //隐藏密码
            scanf("%s",user.passwd1);
            system("stty echo");
            send(sock_fd,&user,sizeof(struct sign),0);      //发送登录包
            break;
        case 2:
            printf("请输入用户名(12位):");
            scanf("%s",user.username);
            printf("请输入密码(12位):");
            system("stty -echo");                           //隐藏密码
            scanf("%s",user.passwd1);
            system("stty echo");
            printf("请再次输入密码(12位):");
            system("stty -echo");                           //隐藏密码
            scanf("%s",user.passwd2);
            system("stty echo");
            send(sock_fd,&user,sizeof(struct sign),0);      //发送注册包
            break;
        case 3:
            exit(EXIT_SUCCESS);
            break;
    }
    recv(sock_fd,&result,1,0);
    return result;
}