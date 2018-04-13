#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *thread_handle(void *arg)
{
    int index = *(int *)arg;
    printf("第%d个线程启动\n", index);
    for (int i = 0; i < 10; i++)
    {
        sleep(1);
        printf("第%d个线程，第%d次\n", index, i);
    }
    printf("第%d个线程退出\n", index);
}

int main()
{
    int result;
    pthread_t arr[10];
    printf("开始创建线程\n");
    for (int i = 0; i < 10; i++)
    {
        int arg = i + 1;
        result = pthread_create(arr + i, NULL, thread_handle, (void *)&arg);
        if (result != 0)
        {
            printf("创建第%d个线程失败", arg);
            exit(EXIT_FAILURE);
        }
        sleep(3);
    }
    /* 线程处理函数没有返回值，传递NULL依然可以等待指定线程结束 */
    result = pthread_join(*(arr+9),NULL);
    printf("创建线程结束，主线程退出\n");
}