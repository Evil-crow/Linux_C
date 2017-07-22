#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

void _error(const char *err_string,int line);

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Error!\n");
        exit(0);
    }

    if(remove(argv[1]) == -1)
    {
        _error("remove",__LINE__);
        exit(0);
    }

    return 0;
}

void _error(const char *err_string,int line)
{
    printf("Error line:  %d\n",line);
    perror(err_string);
    exit(0);
}
