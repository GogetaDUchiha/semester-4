#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

int main() {
    char str[256];
    int fifo_write = open("pipe_one", O_WRONLY);

    if (fifo_write < 0) {
        cout << "Error opening file" << endl;
        return 1;
    }

    while (true) {
        cout << "Enter text: ";
        cin.getline(str, 256);

        write(fifo_write, str, sizeof(str));
        cout << "Sent: " << str << endl;

        if (strcmp(str, "abort") == 0)
            break;
    }

    close(fifo_write);
    return 0;
}
