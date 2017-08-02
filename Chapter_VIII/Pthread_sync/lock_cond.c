/*对此代码进行
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t      mutex;                             //声明全局变量互斥量

pthread_cond_t       cond;                              //声明全局变量条件变量

void *thread1(void *arg);                               //线程创建调用函数1

void *thread2(void *arg);                               //线程创建调用函数2

int main(void)
{
    pthread_t tid1,tid2;                                //线程ID 1,2 说明要创建两个线程

    printf("Start!\n");
    pthread_mutex_init(&mutex,NULL);                    //初始化互斥锁,并置为默认属性
    pthread_cond_init(&cond,NULL);                      //初始化条件变量
    pthread_create(&tid1,NULL,thread1,NULL);            //创建线程1
    pthread_create(&tid2,NULL,thread2,NULL);            //创建线程2

    do
    {
        pthread_cond_signal(&cond);
        //sleep(1);
    }
    while(1);                                           // 激活等待信号的线程

    sleep(50);                                          //sleep防止主线程先挂掉
    pthread_exit(0);                                    //使用线程退出函数,不会影响其他线程
}

void *thread1(void *arg)
{
    //pthread_cleanup_push (pthread_mutex_unlock,&mutex);

    while(1)
    {
        printf("1 is running!\n");
        pthread_mutex_lock(&mutex);                     //上锁
        printf("1111111\n");
        pthread_cond_wait(&cond,&mutex);                //条件变量阻塞
        printf("1 applied the condition!\n");
        pthread_mutex_unlock(&mutex);                   //解锁
        printf("AAAAAAAAA\n");
        sleep(4);
    }

   // pthread_cleanup_pop(0);                             //清理函数
}

void *thread2(void *arg)
{
    while(1)
    {
        printf("2 is running\n");
        pthread_mutex_lock(&mutex);
        printf("22222222\n");
        pthread_cond_wait(&cond,&mutex);
        printf("2 applied the condition!\n");
        pthread_mutex_unlock(&mutex);
        printf("BBBBBBBBBB\n");
        sleep(1);
    }
}
