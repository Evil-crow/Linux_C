#include<stdio.h>
#include<string.h>
int explain_command(char *command,char parameter [ ][256])
{
    char *p;                                             //定义两个指针用来进行字符串的指向
    char *q;
    int count;                                           //用于参数计数
    int n;                                               //用于字符计数

    count = 0;                                           //初始化参数个数
    p = command;
    q = command;
    while(1)                                             //在while(1)循环里,除非'\n',不退出循环
    {
        if(p[0] == '\n')
            break;                                       //循环终止条件
        if(p[0] == ' ')
            p++;                                         //当读到空格时,则指向下一个单元
        else                                             //'\n'与' '的情况以外,则将命令解析
        {
            q = p;
            n = 0;
            while(1)
            {
                if(*q != '\n' && *q != ' ')
                {
                    q++;                                 //指针向后移动
                    n++;                                 //需要拷贝的字符数目增加
                }
                else
                    break;
            }
            strncpy(parameter[count],p,n+1);             //进行字符串的拷贝,连同其后面的'\n',' '
            parameter[count][n] = '\0';                  //处理上面的多余字符问题,全部置为'\0',进行参数的存储. 
            count++;
            p = q;
        }
    }
  
    return count;
}
