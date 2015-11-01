#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void* thr_fun(void* arg)
{
    fprintf(stderr, "tid:%x\n", (int)pthread_self());
    sleep(3);
    srand(time(NULL));
    *(float*)arg = rand()/(float)RAND_MAX;
    return arg;
}

int main(void)
{
    int error;
    float ret, *ret1;
    pthread_t tid;
    if(error = pthread_create(&tid, NULL, thr_fun, &ret)){
        fprintf(stderr, "Failed to create thread:%s\n", strerror(error));
    }
    if(error = pthread_join(tid, (void**)&ret1)){
        fprintf(stderr, "Failed to join thread:%s\n", strerror(error));
    }
    fprintf(stderr, "thread exit code:%.2f\n", *(ret1));
    sleep(1);
    return 0;
}
