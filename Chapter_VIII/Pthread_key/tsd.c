#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>

pthread_key_t key;                //定义全局变量库--键

void *thread1(void *arg);          //线程1

void *thread2(void *arg);          //线程2

int main(void)
{
    pthread_t tid;                 //线程ID

    printf("main thread begins running!\n");
    pthread_key_create(&key,NULL);                        //参数为,键地址,以及析构函数(用于私有数据的内存清理),如果为NULL,则调用系统的清理函数
    pthread_create(&tid,NULL,thread1,NULL);               //四个参数依次是线程ID,线程属性,调用函数,函数参数
    sleep(10);                                            //睡眠以使主线程等待
    pthread_key_delete(key);                              //销毁键,私有数据的销毁必须在其之前,不然会内存泄漏
    printf("mian pthread ends \n");

    return 0;
}

void *thread1(void *arg)
{
    int tsd = 5;                                          //pthread中的私有数据
    pthread_t thid_1;                                     //分配新的线程号

    printf("pthread 11  %u is running!\n",pthread_self(  ));
    pthread_setspecific(key,(void *)tsd);                        //使键与私有数据绑定
    pthread_create(&thid_1,NULL,thread2,NULL);            //创建新线程
    printf("thread1 %u ends,pthread's tsd is %d\n",pthread_self(  ),pthread_getspecific(key));
    sleep(5);                                            //睡眠以等待新线程结束

}

void *thread2(void *arg)
{
    int tsd = 0;

    printf("pthread 22 %u is running\n",pthread_self(  ));
    pthread_setspecific(key,(void *)tsd);                       //绑定键值与私有数据
    printf("Thread %u ends,thread's tsd is %d\n",pthread_self(  ),pthread_getspecific(key));

}

/* 对此段代码,其中需要注意的地方是,
 *
 * 一,关于Thid的问题,使用%d,整型根本保存不下线程ID,必须使用%u,不然会出现溢出
 *
 * 二,即是任意类型指针的问题,(void *)可以指向任何类型的数据,但是会出现警告
 *
 * 而在网路上的解法都是直接进行取地址去获取地址,并传参
 *
 * 至于细节,还需要再琢磨
 *
 */
