#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
void test(void);

int main(int argc,char **argv)
{
    pthread_t thid;
    int status;

    pthread_create(&thid,NULL,(void *)test,NULL);
    pthread_join(thid,(void *)&status);                                     //使主线程进行阻塞,等待子线程结束
    printf("I  (%u)  have waited for a long time  %d",pthread_self( ) ,status);        

    return 0;
}

void test(void)
{
    printf("I am for test !\n");
    sleep(20);                                                  //用sleep来延时函数
    printf("I have achieved!\n");

    pthread_exit(0) ;
}
