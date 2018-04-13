#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void * thread_handle(void * arg){
    int oldstate;
    int result;
    result = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,&oldstate);
    if(result!=0){
        printf("设置线程取消状态失败");
        pthread_exit(NULL);
    }
    printf("设置线程取消状态成功，之前状态为：%d\n",oldstate);
    while(true){
        sleep(1);
        printf("线程执行中\n");
    }
}

int main(){
    pthread_t a;
    int result ;
    result = pthread_create(&a,NULL,thread_handle,NULL);
    if(result!=0){
        printf("创建线程失败\n");
        exit(EXIT_FAILURE);
    }
    sleep(3);
    printf("取消线程\n");
    result = pthread_cancel(a);
    if(result!=0){
        printf("取消线程失败\n");
        exit(EXIT_FAILURE);
    }
    printf("取消线程成功\n");
    exit(EXIT_SUCCESS);
}