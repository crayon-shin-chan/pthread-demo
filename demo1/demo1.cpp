#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
int global = 20;

/* 线程处理函数，参数、返回值必须是void *类型
线程处理函数可以使用它能访问到的任何全局变量，而不需要通过参数传递 */
void * thread_handle(void * arg){
    printf("线程参数为：%s\n",(char *)arg);
    sleep(3);
    global = 10;
    /* pthread_exit函数的参数为pthread_join第二个参数指向的值 */
    pthread_exit((void *)"线程返回值");
}

int main(){
    int result ;
    /* 线程表标识符，其实为unsigned long int类型 */
    pthread_t a;
    char arg[] = "我是参数";
    /* 返回值本身，这个的指针被传递给pthread_join函数的第二个参数 */
    void * thread_return;
    result = pthread_create(&a,NULL,thread_handle,(void *)arg);
    if(result!=0){
        perror("线程创建失败");
        exit(EXIT_FAILURE);
    }
    /* 线程标识符一般为极大整数，如3682907904 */
    printf("线程创建成功,标识符为：%u\n",(int)a);
    /*等待指定线程结束，并且获取返回值*/
    result = pthread_join(a,&thread_return);
    if(result!=0){
        perror("等待线程结束失败");
        exit(EXIT_FAILURE);
    }
    printf("线程已结束，返回值为：%s\n",(char *)thread_return);
    /* 全局变量值被修改 */
    printf("全局变量的值为：%d\n",global);
    exit(EXIT_SUCCESS);
}
