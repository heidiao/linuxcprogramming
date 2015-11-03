#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char* myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    /* open, read, and display the message from the FIFO */
    //if(fd = open(myfifo, O_RDONLY)<0);
    fd = open(myfifo, O_RDONLY);
    if(fd<0){
        perror("open");
        exit(1);
    }
    while(read(fd, buf, MAX_BUF)>0){
        printf("Received: %s\n", buf);
    }
    close(fd);

    return 0;
}
