#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

void _error(const char *err_string,int line);

int main(int argc,char **argv)
{
    char str[1000];
    if(argc != 2)
    {
        printf("Error!\n");
        exit(0);
    }
    if(chdir(argv[1]) < -1)
    {
        _error("chdir",__LINE__);
    }

    if(getcwd(str,100) == NULL)
    {
        _error("getcwd",__LINE__);
    }
    printf("\n%s\n",str);

    return 0;
}

void _error(const char *err_string,int file)
{
    printf("Error line:%d\n",file);
    perror(err_string);
    exit(0);
}
