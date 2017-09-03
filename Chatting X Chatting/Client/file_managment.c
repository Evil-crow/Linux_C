#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"struct_node_client.h"

void __change(char *str);

unsigned long get_file_size(const char *path);

void file_managment(int sock_fd)
{
    FILE *fp;
    int ret;
    char ch;
    char file_constpath[200];                             //文件的绝对路径
    char file_constpath_copy[200];                        //文件路径的备份
    struct node_client user;                              //进行包发送要使用的结构体
    user.flag = 4;                                        //表示进行的是文件传输操作
    user.my_file.file_flag = 1;
    
    printf("\t\t\t\t=====================================================================\n");
    printf("\t\t\t\t                             文件传输\n");
    printf("\t\t\t\t=====================================================================\n");
    printf("\t\t\t\t请输入要发送文件的好友:");
    scanf("%s",user.my_firend.friends_name);
    printf("\t\t\t\t请输入要传输的文件名:");
    scanf("%s",file_constpath);
    strcpy(file_constpath_copy,file_constpath);                      //复制
    user.my_file.file_len = get_file_size(file_constpath);           //使用系统调用获取到文件的大小
    __change(file_constpath_copy);                                     //转换
    strcpy(user.my_file.file_name,file_constpath_copy);              //转换过后获取到的是文件名
    printf("开始传输文件\n");
    fp = fopen(file_constpath,"r+");                                 //r+打开文件
    if(fp == NULL)
    {
        printf("该文件不存在,请核实后重新发送!\n");
        return ;
    }
    while((ret = fread(user.my_file.file_data,sizeof(char),200,fp)) > 0)
    {
        user.my_file.file_buffer = ret;
        send(sock_fd,&user,sizeof(struct node_client),0);            //进行文件内容的发送
        usleep(1000);
        memset(&user,0,sizeof(struct node_client));
        user.flag = 4;
    }
    fclose(fp);
    printf("文件发送完成,接受不接受就不是我能管的了!\n");
    printf("按[Enter]键返回\n");
    getchar( );
    if((ch = getchar( )) == '\n')
        return;
}

void __change(char *str)
{
    char ptr[50];
    int i,j;
    j = 0;
    for(i = 0;str[i] != '\0';i++)
    {
	ptr[j++] = str[i];
	if(str[i] == '/')
	{
	    j = 0;
	    continue;
	}
    }
    ptr[j] = '\0';
    strcpy(str,ptr);
}

unsigned long get_file_size(const char *path)  
{  
    unsigned long filesize = -1;      
    struct stat statbuff;  
    if(stat(path, &statbuff) < 0){  
        return filesize;  
    }else{  
        filesize = statbuff.st_size;  
    }  
    return filesize;  
}  