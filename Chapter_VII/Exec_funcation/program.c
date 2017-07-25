#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(void)
{
   printf("HaHa I'm the program to replace the process!\n");
   printf("My pid is %d,my parent pid is %d\n",getpid( ),getppid( ));
   return 0;
}
