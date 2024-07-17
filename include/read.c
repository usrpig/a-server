#include "headers.h"

size_t readn(int fd, void *buf, size_t size)
{
    char *buf_ptr = buf;
    int len = size;

    while (len > 0) {
        int res = read(fd, buf_ptr, len);

        if (res < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                return (-1);
            }
        } else if (res == 0) {
            break;
        }

        len -= res;
        buf_ptr += res;
    }
    return (size - len);
}