#ifndef _STRUCT_CLIENT_H
#define _STRUCT_CLIENT_H

#define MAX_STR           30
#define MAX_MESSAGE       45

struct sign
{
    int choice_sign;                        //进行登录选择
    char username[MAX_STR];
    char passwd1[MAX_STR];                  //登录密码
    char passwd2[MAX_STR];                  //注册密码
    int  result;                            //登录注册包回馈的结果
};
struct friend_
{
    int                         choice_friend;                      //进行好友操作选择
    int                         friends_status;                     //表示好友状态,0/离线,1/在线
    char                        friends_name[MAX_STR];              //想要进行处理的好友姓名
    char                        friend_message[MAX_MESSAGE];        //要发送的消息
    char                        date_time[80];                       //发送消息的日期时间
};
struct group
{
    int                         choice_group;                       //进行群聊操作选择
    char                        group_message[MAX_MESSAGE];         //发送群聊消息
    char                        group_name;                         //群组名
};
struct node_client
{
    int                          flag;                               //用于标记是用来进行登录注册还是进行其他操作 1为登录,2为friend,3为group
    int                          decision;                           //表示是否同意请求 1/同意,是,0/不同意,否
    struct sign                  consumer;                           //进行登录的结构体
    struct friend_               my_firend;                          //进行私聊的结构体
    struct group                 my_group;                           //进行群聊的结构体
};
#endif