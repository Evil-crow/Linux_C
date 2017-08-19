#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include"struct_node_client.h"

extern int chat_status;

extern char *get_time(void);

extern void change(char *str);                                      //进行时间内容的转换

void chatting_with_group(int sock_fd)                               //发起群聊函数
{
    int ch;
    struct node_client user;                                         //进行群聊消息发送的结构体
    user.flag = 3;                                                   //进行的是群聊操作
    user.my_group.choice_group = 1;                                  //进行的是群聊
    char date_time[40];
    char _message[40];                                               //暂存信息
    char _name[40];
    FILE *fp;

    printf("请输入要进行发言的群组名:");
    scanf("%s",user.my_group.group_name);                            //录入群组名
    printf("开始聊天:\n");
    chat_status = 1;                                                 //状态的切换
    fp = fopen("/home/Crow/Public/buffer1","r+");                    //用r+将暂存内容取出来
    if((ch = fgetc(fp)) != EOF)
    {
        while(!feof(fp))
        {
            fscanf(fp,"%s\n%s %s\n",date_time,_name,_message);
            printf("%s\n%s:%s\n",date_time,_name,_message);
        }
    }
    fclose(fp);
    fp = fopen("/home/Crow/Public/buffer1","w+");
    fclose(fp);                                                           //清空缓冲区
    while(1)
    {
        printf("%s",get_time( ));
        scanf("%s",_message);                                    //暂存
        if(strcmp(_message,"quit") != 0)
        {
            strcpy(date_time,get_time( ));
            change(date_time);
            strcpy(user.my_group.date_time,date_time);          //保存时间信息
  
            strcpy(user.my_group.group_message,_message);
            send(sock_fd,&user,sizeof(struct node_client),0);
        }
        else
        break;
    }
    printf("聊天结束\n");
    chat_status = 0;
    getchar( );                                                      //实现按任意键退出
    if((ch = getchar( )) == '\n')
    return;      
}
void create_new_group(int sock_fd)
{
    char ch;                                                        //用于任意键退出
    struct node_client user;
    user.flag = 3;                                                  //进行群组的操作
    user.my_group.choice_group = 2;                                          //创建群组

    printf("请输入你要创建的群组:");
    scanf("%s",user.my_group.group_name);                           //存入群组名
    printf("继续创建吗?(0/1)");
    getchar( );
    if((ch = getchar( )) == '1')
    {
        send(sock_fd,&user,sizeof(struct node_client),0);            //发送信息包
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;                                                     //按回车键返回菜单
    }
    getchar( );
    if((ch = getchar ( )) == '\n')
    return ;                                                          //返回菜单
}

void join_group(int sock_fd)
{
    int ch;
    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 3;                                //加入群组的操作

    printf("请输入你想要加入的群组:");
    getchar( );
    scanf("%s",user.my_group.group_name);                         //录入想要加入的群组名
    printf("确定加入该群组吗?(0/1)");
    getchar( );
    if((ch = getchar( )) == '1')
    {
        send(sock_fd,&user,sizeof(struct node_client),0);           //发送信息包
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;
    }  
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void display_group_member(int sock_fd)
{
    int ch;
    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 4;

    printf("请输入群组名:");
    scanf("%s",user.my_group.group_name);
    send(sock_fd,&user,sizeof(struct node_client),0);           //发包
    printf("群组成员显示如下:\n");
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void display_member_status(int sock_fd)
{
    int ch;

    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 5;                                      //显示群组成员的状态

    printf("请输入群组名:");
    scanf("%s",user.my_group.group_name);
    send(sock_fd,&user,sizeof(struct node_client),0);
    printf("群组成员状态如下:\n");
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void view_group_chat_log(int sock_fd)                                       //查看群消息
{
    int ch;
    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 6;                                        //表示查看群组历史记录

    printf("请输入你想查看历史消息的群组名:");
    scanf("%s",user.my_group.group_name);                                    //存入目标群组名
    send(sock_fd,&user,sizeof(struct node_client),0);
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;                                                              //按任意键退出
} 
void display_joined_group(int sock_fd)
{
    int ch;
    struct node_client user;
    user.flag = 3;                                                 //表示是好友的操作
    user.my_group.choice_group = 7;                                //显示所有加入的群的操作

    printf("您所加入的群组以下:\n");
    send(sock_fd,&user,sizeof(struct node_client),0);
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void del_group(int sock_fd)
{
    int ch;
    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 8;                                 //表示删除群组的操作

    printf("请输入想退出的群组:");
    scanf("%s",user.my_group.group_name);
    printf("确认退出吗?(0/1)");
    getchar( );
    if((ch = getchar( )) == '1')
    {
        send(sock_fd,&user,sizeof(struct node_client),0);
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;
    }
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}