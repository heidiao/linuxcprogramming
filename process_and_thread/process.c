#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handler()
{
    printf("signal handler\n");
}
int main()
{
    pid_t child;
    printf("Standard IO:%d, %d, %d\n", STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
    signal(SIGUSR1, handler);
    child = fork();
    if (child > 0){
        printf("Im parent, child id:%d\n", child);
        pause();
        printf("parent end\n");
    }else{
        printf("Im child\n");
        sleep(1);
        printf("send signal\n");
        kill(getppid(), SIGUSR1);
        printf("send signal end\n");
    }
    return 0;
}
