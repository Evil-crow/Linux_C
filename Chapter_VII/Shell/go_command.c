#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/param.h>
#include<time.h>
#include<syslog.h>

#define normal      0                                                                  //一般命令
#define in_put      1                                                                  //输入重定向1 >
#define out_put     2                                                                  //输出重定向1 <
#define In_put      3                                                                  //输入重定向2 >>
#define _pipe       4                                                                  //管道命令

int find_command(char *);

void go_command(int count,char parameter[][256])
{
    int   fd;                                                                    //重定向时的文件标识符
    int   status;                                                                //wait/waitpid函数中进行退出码的记录
    int   flag = 0;                                                              //判断是否为>,<,>>,<<,|等单一命令
    int   background = 0;                                                        //判断是否是后台命令
    int   how = 0;                                                               //用来记录输入的命令形式,单命令,重定向,管道
    int   i;                                                                     //存在二维数组进行记录
    char  *command[count+1];                                                     //用来记录多个命令
    char  *command_next[count+1];                                                //用来记录管道命令中的第二个
    pid_t pid;                                                                   //fork( )进程后,用来获取的子进程PID
    char  *file;                                                                 //使用file存储要重定向,管道处理的文件
    
    /*从parameter中取出命令*/
    for(i = 0;i < count;i++)
    {
        command[i] =(char *)parameter[i];
    }
    command[i] = NULL;

    /*判断如果存在'&',则为后台命令,进行标记*/
    for(i = 0;i < count;i++)
    {
        if(strcmp(command[i],"&") == 0)
        { 
            if(i == count-1)
            {
                background = 1;
                command[count-1] = NULL;
            }
            else
            {
                printf("Illegal Command!\n");
                return;
            }
        }
    }

    /*进行how的权数处理*/ 
    for(i = 0;command[i] != NULL;i++)
    {
        if(strcmp(command[i],">") == 0)
        {
            flag++;                                                              //判断不合法
            how = in_put;                                                        //输入重定向1
            if(command[i+1] == NULL)                                             //如果没有文件
                flag++;
        }

        if(strcmp(command[i],"<") == 0)
        {
            flag++;
            how = out_put;                      
            if(i == 0)
                flag++;
        }
        if(strcmp(command[i],">>") == 0)
        {
            flag++;
            how = In_put;
            if(command[i+1] == NULL)
                flag++;
        }
        if(strcmp(command[i],"|") == 0)
        {
            flag++;
            how = _pipe;
            if(command[i+1] == NULL || i == 0)
                flag++;
        }
    }

    /*如果其中有多个重定向,或者管道命令,报错*/ 
    if(flag > 1)
    {
        printf("error command!\n");
        return;
    }
    
    /*对重定向,管道之类的命令处理,保存文件,截断命令*/
    if(how == in_put)                        
    {
        for(i = 0;command[i] != NULL;i++)
        {
            if(strcmp(command[i],">") == 0)
            {
                file = command[i+1];
                command[i] = NULL;
            }
        }        
    }

    if(how == out_put)
    {
        for(i = 0;command[i] != NULL;i++)
        {
            if(strcmp(command[i],"<") == 0)
            {
                file = command[i+1];
                command[i] = NULL;
            }
        }
    }

    if(how == In_put)
    {
        for(i = 0;command[i+1] != NULL;i++)
        {
            if(strcmp(command[i],">>") == 0)
            {
                file = command[i+1];
                command[i] = NULL;
            }
        }
    }


    if(how == _pipe)
    {
        for(i = 0;command[i] != NULL;i++)
        {
            if(strcmp(command[i],"|") == 0)
            {
                command[i] = NULL;
                int j;
                for(j = i+1;command[j] != NULL;j++)
                {
                   command_next[j-i-1] = command[j]; 
                }
                command_next[j-i-1] = command[j];                                        //对管道中第二条命令,最后也应该置为空指针
                break;
            }
        }
    } 
    
    /*实现内置命令cd*/
    if(strcmp(command[0],"cd") == 0)
    {
        if(count == 1)
        { 
            return ;
        }
        if(strcmp(command[1],"~") == 0)
            chdir("/home/Crow");
        if(chdir(command[1]) < -1)
        {
            printf("error!");
            exit(0);
        }
        return ;
    }
    
    /*fork( )产生父子进程,进行资源调度*/ 
    pid = fork( );
    if(pid == -1)
    {
        printf("fork failed!\n");
        exit(0);
    }

    /*case 0,1,2,3,4 分别为单命令,各种重定向(3)和管道*/ 
    switch(how)
    {
        case 0:
            if(pid == 0)
            {
                if(!find_command(command[0]))
                {
                    printf("shell: %s: command not found...\n",command[0]);
                    exit(0);
                }
                if(background == 1)                                                        /*表示是后台进程*/
                {
                    daemon(0,0); 
                    execvp(command[0],command);
                    exit(0);
                }        
                execvp(command[0],command);
                exit(0);
            }
            break;
        case 1:
            if(pid == 0)
            {
                if(!find_command(command[0]))
                {
                    printf("shell: %s: command not found...\n",command[0]);
                    exit(0);
                }
                fd = open(file,O_RDWR|O_CREAT|O_TRUNC,0664);
                dup2(fd,1);
                execvp(command[0],command);
                exit(0);
            }
            break;
        case 2:
            if(pid == 0)
            {
                if(!find_command(command[0]))
                {
                    printf("shell: %s: command not found...\n",command[0]);
                    exit(0);
                }
                fd = open(file,O_RDONLY);
                dup2(fd,0);
                execvp(command[0],command);
                exit(0);
            }
            break;
        case 3:
            if(pid == 0)
            {
                if(!find_command(command[0]))
                {
                    printf("shell: %s: command not found...\n",command[0]);
                    exit(0);
                }
                fd = open(file,O_RDWR|O_CREAT|O_APPEND,0644);
                dup2(fd,1);
                execvp(command[0],command);
                exit(0);
            }
            break;
        case 4:
            {
            
                if(pid==0)
            {
                int pid2;
                int status;
                int fd2;

                if((pid2 = fork())<0){
                    printf("fork2 error\n");
                    return ;
                    }
                else if(pid2 ==0 ){ 
                    if(!(find_command(command[0]))){
                        printf("%s : command not found\n",command[0]);
                        exit(0);
                    }
                fd2 = open("/tmp/pipefile",O_WRONLY|O_CREAT|O_TRUNC,0644);
                dup2(fd2,1);
                execvp(command[0],command);
                exit(0);
                }

                if(waitpid(pid2,&status,0) == -1)
                    printf("wait for child process error");

                if(!find_command(command_next[0])){
                    printf("%s : command not found\n",command_next[0]);
                    exit(0);
                }

                fd2 = open("/tmp/pipefile",O_RDONLY);
                dup2(fd2,0);
                execvp(command_next[0],command_next);

                if(remove("/tmp/pipefile"))
                    printf("remove error\n");
                exit(0);
            }
            break;
            }
        default:
            break;
            
    }
    
    if(waitpid(pid,&status,0) == -1)                                      //父进程等待子进程失败
    {
        printf("wait chile process failed!");
        exit(0);
    }
}
