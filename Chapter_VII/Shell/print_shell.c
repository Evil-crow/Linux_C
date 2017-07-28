#include<stdlib.h>
#include<stdio.h>
void print_shell(void)
{
    char dir[100];

    if(getcwd(dir,100) == -1)
    {
        printf("Error!\n");
        exit(0);
    }
    int i,j;
    for(i = 0;dir[i] != '\0';i++)
    {
        if(dir[i] == '/')
            j = i+1;
    }
    char Dir[30];
    for(i = 0;i < 100;i++,j++)
    {
        Dir[i] = dir[j];
    }
    Dir[i+1] = '\0';

    printf("[Crow@Shell %s]Σ ",Dir);
}
