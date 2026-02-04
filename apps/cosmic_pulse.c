#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BAR_WIDTH 40

void print_bar(double percent, char *label, char *color) {
    int filled = (BAR_WIDTH * percent) / 100;
    printf("%s %-8s [\033[0m", color, label);
    for (int i = 0; i < BAR_WIDTH; i++) {
        if (i < filled) printf("\033[1;32m#\033[0m");
        else printf(" ");
    }
    printf("%s] %.1f%%\033[0m\n", color, percent);
}

void get_mem_usage(double *total, double *free) {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) return;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line + 9, "%lf", total);
        } else if (strncmp(line, "MemFree:", 8) == 0) {
            sscanf(line + 8, "%lf", free);
        }
    }
    fclose(fp);
}

int main() {
    printf("\033[2J\033[H"); // Clear and home
    printf("\033[1;36m--- 🌌 Cosmic Pulse: System Monitor ---\033[0m\n\n");

    while (1) {
        printf("\033[H\033[2B"); // Home + 2 lines down

        // Memory Usage
        double total_mem, free_mem;
        get_mem_usage(&total_mem, &free_mem);
        double used_mem = total_mem - free_mem;
        double mem_percent = (used_mem / total_mem) * 100.0;
        print_bar(mem_percent, "MEMORY", "\033[1;35m");

        // CPU Usage (Fake for now as reading proc/stat requires 2 samples)
        double cpu_percent = 15.0 + (rand() % 10); 
        print_bar(cpu_percent, "CPU LOAD", "\033[1;34m");

        printf("\n\033[1;33mPress Ctrl+C to exit cosmic pulse.\033[0m\n");
        fflush(stdout);
        sleep(1);
    }

    return 0;
}
