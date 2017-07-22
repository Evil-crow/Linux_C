#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void _error(const char *err_string,int line);

int main(int argc,char **argv)
{
    char dir[100];
    if(argc != 1)
    {
        printf("Error!\n");
    }

    if(getwd(dir,30) == -1)
    {
        _error("getwd",__LINE__);
    }

    printf("%s\n",dir);

    return 0;
}

void _error(const char *err_string,int line)
{
    printf("Error line: %d",line);
    perror(err_string);
    exit(0);
}
