#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd_read = open("FIFO1", O_RDONLY);
    int fd_write = open("FIFO2", O_WRONLY);
    char msg[100], response[100];

    while (1) {
        read(fd_read, msg, sizeof(msg));
        printf("Received: %s", msg);

        printf("Send: ");
        fgets(response, sizeof(response), stdin);
        write(fd_write, response, strlen(response) + 1);
    }
    return 0;
}
