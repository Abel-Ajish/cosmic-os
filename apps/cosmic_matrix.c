#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define MAX_DROPS 256

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;
    int height = w.ws_row;

    int drops[MAX_DROPS];
    for (int i = 0; i < width && i < MAX_DROPS; i++) {
        drops[i] = rand() % height;
    }

    printf("\033[2J"); // Clear screen
    printf("\033[?25l"); // Hide cursor

    while (1) {
        for (int i = 0; i < width && i < MAX_DROPS; i++) {
            // Print a random green character at the drop position
            printf("\033[%d;%dH\033[1;32m%c\033[0m", drops[i], i, (char)(rand() % 94 + 33));
            
            // Increment the drop position
            drops[i]++;
            if (drops[i] > height) {
                drops[i] = 1;
            }

            // Periodically clear characters to create the "tail" effect
            if (rand() % 10 > 7) {
                 printf("\033[%d;%dH ", (drops[i] + height - 5) % height + 1, i);
            }
        }
        fflush(stdout);
        usleep(50000); // 50ms delay
    }

    printf("\033[?25h"); // Restore cursor (wont be reached usually)
    return 0;
}
