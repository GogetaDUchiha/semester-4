#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

int main() {
    char str[256];
    int fifo_read = open("pipe_one", O_RDONLY);

    if (fifo_read < 0) {
        cout << "Error opening file" << endl;
        return 1;
    }

    while (true) {
        read(fifo_read, str, sizeof(str));
        cout << "Received: " << str << endl;

        if (strcmp(str, "abort") == 0)
            break;
    }

    close(fifo_read);
    return 0;
}
