#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t rawtime;
    struct tm *info;
    char buffer[80];

    time(&rawtime);
    info = localtime(&rawtime);

    printf("\033[1;36m┌─────────────────────────────────────┐\033[0m\n");
    printf("\033[1;36m│\033[0m \033[1;35m🌌 Cosmic Chronometer\033[0m              \033[1;36m│\033[0m\n");
    printf("\033[1;36m├─────────────────────────────────────┤\033[0m\n");

    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", info);
    printf("\033[1;36m│\033[0m \033[1;33m📅 Date:\033[0m %-27s \033[1;36m│\033[0m\n", buffer);

    strftime(buffer, sizeof(buffer), "%I:%M:%S %p", info);
    printf("\033[1;36m│\033[0m \033[1;33m⌚ Time:\033[0m %-27s \033[1;36m│\033[0m\n", buffer);

    printf("\033[1;36m└─────────────────────────────────────┘\033[0m\n");

    return 0;
}
