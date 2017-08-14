#include<stdio.h>
#include<errno.h>

void _error(const char *string,int line)
{
    printf("Error line:%d",line);
    perror(string);
    printf("\n");
}