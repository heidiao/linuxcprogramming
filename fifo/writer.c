#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main()
{
    int fd, i=0;
    char* myfifo = "/tmp/myfifo";
    
    char buf[MAX_BUF];

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY);
    if(fd<0){
        perror("open myfifo");
        exit(1);
    }
    
    while(1){
        sprintf(buf, "Hi->%d", i);
        write(fd, buf, sizeof(buf));
        sleep(1);
        i++;
    }
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;
}
