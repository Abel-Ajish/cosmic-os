#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cosmic-edit <filename>\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    printf("--- 🌌 cosmic-edit: %s ---\n", filename);
    printf("Type your text. Type ':wq' on a new line to save and exit.\n");
    printf("--------------------------------------------------\n");

    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, stdin)) {
        if (strcmp(buffer, ":wq\n") == 0) {
            break;
        }
        fputs(buffer, fp);
        fflush(fp);
    }

    fclose(fp);
    printf("\033[1;32mFile saved: %s\033[0m\n", filename);
    return 0;
}
