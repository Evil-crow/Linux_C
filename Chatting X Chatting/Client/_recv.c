#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include"struct_node.h"
#include"main.h"

extern void _error(const char *string,int line);

void _recv(int sock_fd)
{
    struct node_client   user;            //用于recv的结构体
    int                  ret;             //用来处理返回值

    while(1)
    {
        ret = recv(sock_fd,&user,sizeof(struct node_client),0);           //收包

        /*收包后进行参数的解析*/
        switch(user.flag)                                                //对大标识进行解析
        {
            case 1:                                                      //如果是登录/注册的包
                switch(user.consumer.choice_sign)
                {
                    case 1:                                              //表示是登录包
                        switch(user.consumer.result)
                        {
                            case 0:                                              //表示成功登录信息
                                printf("登录成功!(´･_･`)\n");
                                getchar( );
                                system("cls");
                                break;
                            case 1:                                              //此用户已在线
                                printf("你的帐号已被隔壁练腰的老王提前登录(ಡωಡ)\n");
                                getchar( );
                                system("cls");
                                exit(EXIT_SUCCESS);
                                break;
                            case 2:                                              //用户名错误
                                printf("没注册用户就想上车,做梦去吧你₍₍ (̨̡ ‾᷄ᗣ‾᷅ )̧̢ ₎₎\n");
                                getchar( );
                                system("cls");
                                exit(EXIT_SUCCESS);
                                break;
                            case 3:                                              //密码错误
                                printf("自己的密码都记不住,玩锤子(˵¯͒⌢͗¯͒˵)\n");
                                getchar( );
                                system("cls");
                                exit(EXIT_SUCCESS);
                                break;
                        }
                        break;
                    case 2:
                        switch(user.consumer.result)
                        {
                            case 0:
                                printf("注册成功!(´･_･`)\n");
                                getchar( );
                                system("cls");                                   //清屏操作
                                break;
                            case 1:
                                printf("隔壁老王抢先一步了呢!(ಡωಡ)\n");
                                getchar( );
                                system("cls");
                                exit(EXIT_SUCCESS);
                                break;
                        }
                        break;
                }
                break;
            //case 2:                               处理数据信息

        }
    }
}

