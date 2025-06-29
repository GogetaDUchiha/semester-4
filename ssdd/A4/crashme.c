#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buf[20];  // small buffer

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    // ⚠️ Dangerous: no length check!
    fread(buf, 1, 1000, f);
    fclose(f);

    printf("Input: %s\n", buf);
    return 0;
}
