#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd_write = open("chat_send", O_WRONLY);
    int fd_read = open("chat_receive", O_RDONLY);
    char msg[100], response[100];

    while (1) {
        printf("You: ");
        fgets(msg, sizeof(msg), stdin);
        write(fd_write, msg, strlen(msg) + 1);

        if (strncmp(msg, "bye", 3) == 0) break;

        read(fd_read, response, sizeof(response));
        printf("Friend: %s", response);

        if (strncmp(response, "bye", 3) == 0) break;
    }

    close(fd_write);
    close(fd_read);
    return 0;
}
