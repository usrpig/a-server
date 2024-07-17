#include "include/headers.h"

#define MSG_SIZE 102400

void send_data(int sockfd)
{
    char *query;
    query = malloc(MSG_SIZE + 1);
    for (int i = 0; i < MSG_SIZE; ++i) {
        query[i] = i % 26 + 'a';
    }
    query[MSG_SIZE] = '\0';

    const char *cp;
    cp = query;
    size_t remainLen = strlen(query);
    while (remainLen) {
        int n_written = send(sockfd, cp, remainLen, 0);
        fprintf(stdout, "send into buffer %ld\n", n_written);
        if (n_written <= 0) {
            perror("send failed");
            exit(1);
        }
        remainLen -= n_written;
        cp += n_written;
    }
    return;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        perror("usage: tcpclient <IPaddress>");
        exit(1);
    }
    int sockfd = get_socket_cli(argv[1], 12345);
    send_data(sockfd);
    exit(0);
}