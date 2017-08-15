#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"menu.h"
#include"Linkedlist.h"

extern list *pHead;                                                 //主函数中的头节点,此处引用

extern void _error(const char *string,int line);

int judge(FILE*fp);                                                   //判断文件是否为空
void sign_register(int conn_fd,struct node_server user)
{
    FILE *fp;                                                          //文件指针
    char username[MAX_STR];
    char password[MAX_STR];
    fp = fopen("/home/Crow/Public/Information/user","a+");              //以a+方式打开文件
    if(fp == NULL)
        _error("fopen",__LINE__);
    fseek(fp,0L,0);                                                     //使文件指针处于文件开始处
    switch(user.consumer.choice_sign)
    {
        case 1:                                                   //进行登录选项
            if(judge(fp))
            {
                while(!feof(fp))                                  //当没有读到文件末尾时
                {
                    fscanf(fp,"%s %s\n",username,password);       //读出文件中的用户名和密码
                    if(strcmp(username,user.consumer.username) == 0)          //如果用户名存在
                    {
                        if(strcmp(password,user.consumer.passwd1) == 0)
                        {
                            user.consumer.result = 0;              //用户名,密码完全匹配.登录成功
                            pHead = linkedlist_add(pHead,conn_fd,user.consumer.username);
                            /*将登录成功的用户,添加进入链表中*/
                            break;
                        }
                        user.consumer.result = 3;                  //登录时.密码错误
                        break;
                    }
                }
                user.consumer.result = 2;                          //遍历完成,没有该用户名
                break;
            }
            user.consumer.result = 2;                              //文件为空,用户名不存在
            break;
        case 2:                                                  //进行注册选项
            if(judge(fp))
            {
                while(!feof(fp))
                {
                    fscanf(fp,"%s %s\n",username,password);             //从文件中读出用户名及密码
                    if(strcmp(username,user.consumer.username) == 0)    //该用户已经被注册过
                    {
                        user.consumer.result = 1;
                        break; 
                    }      
                }
            }
            fseek(fp,0L,2);                                             //移动文件指针至文件末尾进行追加
            fprintf(fp,"%s %s\n",user.consumer.username,user.consumer.passwd1);      //写入注册用户的信息
            fclose(fp);                                                              //写完记得关闭文件
            char str[200] = "/home/Crow/Public/Information/";
            strcat(str,user.consumer.username);                                      //拼接出路径名
            mkdir(str,0755);
            chdir(str);
            creat("group_information",0755);
            creat("friens_list",0755);
            creat("belong_to_group",0755);
            user.consumer.result = 0;
            break;
    }
    /*在switch-case语句之后,进行sign数据包的回馈*/
    send(conn_fd,&user,sizeof(struct node_server),0);                      //将处理后的信息包发送回去
}

int judge(FILE *fp)
{
    if(fgetc(fp) == EOF)
    {
        fseek(fp,0L,0);                                        //重新回到文件头
        return 0;
    }
    return 1;
}