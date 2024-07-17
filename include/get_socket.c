#include "headers.h"

static int make_socket_ser(uint16_t port)
{
    int sock;
    struct sockaddr_in name;

    // 创建字节类型的IPv4 socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    // 绑定 IP 和 PORT
    name.sin_family = AF_INET;
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htons(INADDR_ANY);

    if (bind(sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
        perror("bind error");
        exit(EXIT_FAILURE);
    }
    return sock;
}

static int make_socket_cli(char *serIP, uint16_t port)
{
    int sockfd;
    struct sockaddr_in seraddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(port);
    inet_pton(AF_INET, serIP, &seraddr.sin_addr);
    int connRes = connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    if (connRes < 0) {
        perror("connect failed");
        exit(1);
    }
    return sockfd;
}

int get_socket_ser(uint16_t port)
{
    return make_socket_ser(port);
}

int get_socket_cli(char *serIP, uint16_t port)
{
    return make_socket_cli(serIP, port);
}
