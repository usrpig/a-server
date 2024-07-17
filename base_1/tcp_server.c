#include <stdio.h>

#include "include/headers.h"

void read_data(int sockfd)
{
    ssize_t n;
    char buf[1024];
    int time = 0;

    for (;;) {
        fprintf(stdout, "block in read\n");
        if ((n = readn(sockfd, buf, 1024)) == 0) {
            return ;
        }
        ++time;
        fprintf(stdout, "1K read, time = %d\n", time);
        usleep(1000);
    }
}

int main(int args, char** argv)
{
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int listenfd, connfd;
    listenfd = get_socket_ser((uint16_t)12345);
    listen(listenfd, 1024);

    while (1) {
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
        read_data(connfd);
        close(connfd);
    }
}
