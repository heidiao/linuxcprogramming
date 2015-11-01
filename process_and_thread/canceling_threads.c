#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void* thr_fun(void* arg)
{
    int oldstate;
    fprintf(stderr, "tid:%x\n", (int)pthread_self());
    sleep(3);
    srand(time(NULL));

    while(1){
        // it won't receive any pthread cancel request, like a "lock"
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
        char msg[100];
        float randnum = rand()/(float)RAND_MAX;
        sprintf(msg, "random number(0-1.0):%.5f\n", randnum);
        char* c = msg;
        while(*c!='\0'){
            fputc(*c, stderr);
            c++;
        }
        // resume the cancel request, like "unlock"
        pthread_setcancelstate(oldstate, NULL);
        // request delivery of any pending cancellation request
        pthread_testcancel();
    }
}

int main(void)
{
    int error;
    pthread_t tid;
    if(error = pthread_create(&tid, NULL, thr_fun, NULL)){
        fprintf(stderr, "Failed to create thread:%s\n", strerror(error));
    }
    sleep(3);
    pthread_cancel(tid);
    if(error = pthread_join(tid, NULL)){
        fprintf(stderr, "Failed to join thread:%s\n", strerror(error));
    }
    return 0;
}
