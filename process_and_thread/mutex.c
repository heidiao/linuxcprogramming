#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thr_fun(void* arg)
{
    int i, j, delay = 10000000;
    char msg[128];
    
    pthread_mutex_lock(&mutex);
    snprintf(msg, 128, "pid:%d tid:%x\n", (int)getpid(), (int)pthread_self());

    char *c = msg;
    while(*c!='\0'){
        fputc(*c, stderr);
        c++;
        for(j=0;j<delay;j++); //delay some time...
    }
    pthread_mutex_unlock(&mutex);
}


int main(void)
{
    int error, i, j, n=3;
    pthread_t tid[n];
    for(i=0;i<n;i++)
        pthread_create(&tid[n], NULL, thr_fun, NULL);

    for(i=0;i<n;i++)
        pthread_join(tid[n], NULL);
    return 0;
}
