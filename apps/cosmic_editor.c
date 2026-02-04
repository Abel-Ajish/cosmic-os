#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINES 1000
#define MAX_LINE_LEN 256

void print_ui(const char *filename) {
    printf("\033[2J\033[H");
    printf("\033[1;37;44m  🌌 COSMIC EDITOR - Editing: %-40s  \033[0m\n", filename);
    printf("\033[1;33m  Commands: :w (save), :q (quit), :wq (save & quit)          \033[0m\n\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cosmic-editor <filename>\n");
        return 1;
    }

    char *filename = argv[1];
    char *lines[MAX_LINES];
    int line_count = 0;

    // Try to read existing file
    FILE *fp = fopen(filename, "r");
    if (fp) {
        char buffer[MAX_LINE_LEN];
        while (fgets(buffer, MAX_LINE_LEN, fp) && line_count < MAX_LINES) {
            lines[line_count] = strdup(buffer);
            line_count++;
        }
        fclose(fp);
    }

    print_ui(filename);

    // Display existing lines
    for (int i = 0; i < line_count; i++) {
        printf("%3d | %s", i + 1, lines[i]);
    }

    char input[MAX_LINE_LEN];
    while (1) {
        printf("%3d | ", line_count + 1);
        if (!fgets(input, MAX_LINE_LEN, stdin)) break;

        // Command checks
        if (strcmp(input, ":q\n") == 0) break;
        
        if (strcmp(input, ":w\n") == 0 || strcmp(input, ":wq\n") == 0) {
            FILE *out = fopen(filename, "w");
            if (out) {
                for (int i = 0; i < line_count; i++) {
                    fputs(lines[i], out);
                }
                fclose(out);
                printf("\033[1;32m[+] File saved.\033[0m\n");
                if (strcmp(input, ":wq\n") == 0) break;
                continue;
            } else {
                perror("\033[1;31mError saving file\033[0m");
            }
        }

        // Add line to memory
        if (line_count < MAX_LINES) {
            lines[line_count] = strdup(input);
            line_count++;
        } else {
            printf("\033[1;31mError: Maximum lines reached!\033[0m\n");
        }
    }

    // Cleanup
    for (int i = 0; i < line_count; i++) free(lines[i]);

    printf("\033[1;36mExiting Cosmic Editor. Stay safe in the void.\033[0m\n");
    return 0;
}
