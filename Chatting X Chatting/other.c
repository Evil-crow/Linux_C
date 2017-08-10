#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
void _error(const char *string,int line)
{
    printf("Error line:%d\n",line);
    perror(string);
    printf("\n");
    exit(EXIT_FAILURE);
}