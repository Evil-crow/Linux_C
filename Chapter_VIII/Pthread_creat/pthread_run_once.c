/* 进行线程时,只允许子线程进行一次调度执行时,sleep( )
 *
 * 函数十分关键,否则你能看到的便不是想要的结果
 *
 * 因为有可能不同电脑的调度算法,使得main_thread优先完成,
 *
 * 则所有子线程的操作,就是失去意义了
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run_thid(void);

void *thread1(void);

void *thread2(void);

int main(int argc,char **argv)
{
    pthread_t thid1,thid2;

    printf("Thread start!\n");
    pthread_create(&thid1,NULL,(void *)thread1,NULL);                        //创建第一个线程
    pthread_create(&thid2,NULL,(void *)thread2,NULL);                        //创建第二个线程
    sleep(3);                                                                //十分关键的一步,不然会使程序结构出错!!!
    printf("main thread ends\n");

    return 0;
}
void *thread1(void)
{
    pthread_t thid;

    thid = pthread_self( );                          //获取线程ID;
    printf("Current thread: %u\n",thid);
    pthread_once(&once,run_thid);                         //确保多个线程只调用目标函数一次
    printf("thread1 ends\n");
}

void *thread2(void)
{
    pthread_t thid;

    thid = pthread_self( );                          //获取线程ID;
    printf("Current thread: %u\n",thid);
    pthread_once(&once,run_thid);
    printf("thread2 ends\n");
}

void run_thid(void)
{
    pthread_t thid;

    thid = pthread_self( );
    printf("Now is pthread %u is running!\n",pthread_self( ));

    return ;
}


