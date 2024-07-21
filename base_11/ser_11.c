#include "include/headers.h"

static int count;
static void sig_int(int signo)
{
    printf("\nrecv %d datagrams\n", count);
    exit(0);
}

int main(int argc, char **argv)
{
    struct sockaddr_in cli_addr, ser_addr;
    int listenfd = get_socket_ser(8888);
    int rt = listen(listenfd, LISTENQ);
    if (rt < 0) {
        LOG("listen fail");
    }
    signal(SIGINT, sig_int);
    signal(SIGPIPE, SIG_IGN);

    socklen_t cliLen = sizeof(cli_addr);
    int connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cliLen);
    if (connfd < 0) {
        LOG("bind failed");
    }

    char msg[MAXLINE];
    count = 0;
    while (0) {
        int n = read(connfd, msg, MAXLINE);
        if (n < 0) {
            LOG("read failed");
        } else if (n == 0) {
            LOG("client close");
        }
        msg[n] = 0;
        printf("received %d bytes: %s\n", n, msg);
        count++;

        char send_line[MAXLINE];
        sprintf(send_line, "Hi, %s", msg);

        sleep(5);

        int write_nc = send(connfd, send_line, strlen(send_line), 0);
        printf("send bytes: %zu \n", write_nc);
        if (write_nc < 0) {
            LOG("error write");
        }
    }
}
