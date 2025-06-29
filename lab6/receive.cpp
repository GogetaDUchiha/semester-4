#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd_read = open("chat_send", O_RDONLY);
    int fd_write = open("chat_receive", O_WRONLY);
    char msg[100], response[100];

    while (1) {
        read(fd_read, msg, sizeof(msg));
        printf("Friend: %s", msg);

        if (strncmp(msg, "bye", 3) == 0) break;

        printf("You: ");
        fgets(response, sizeof(response), stdin);
        write(fd_write, response, strlen(response) + 1);

        if (strncmp(response, "bye", 3) == 0) break;
    }

    close(fd_read);
    close(fd_write);
    return 0;
}
