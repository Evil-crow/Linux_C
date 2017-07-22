#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>

void _error(const char *err_string,int line);

int main(int argc,char **argv)
{
    if(argc != 3)
    {
        printf("Error!\n");
        exit(0);
    }

    if(rename(argv[1],argv[2]) == -1)
    {
        _error("rename",__LINE__);
    }

    return 0;
}

void _error(const char *err_string,int line)
{
    printf("Error line:  %d\n",line);
    perror(err_string);
    exit(0);
}
