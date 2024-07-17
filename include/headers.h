#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

int get_socket_ser(uint16_t port);
int get_socket_cli(char *serIP, uint16_t port);
size_t readn(int fd, void *buf, size_t size);
#endif