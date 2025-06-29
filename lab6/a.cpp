#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd_write = open("FIFO1", O_WRONLY);
    int fd_read = open("FIFO2", O_RDONLY);
    char msg[100], response[100];

    while (1) {
        printf("Send: ");
        fgets(msg, sizeof(msg), stdin);
        write(fd_write, msg, strlen(msg) + 1);

        read(fd_read, response, sizeof(response));
        printf("Received: %s", response);
    }
    return 0;
}
