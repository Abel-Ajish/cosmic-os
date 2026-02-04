#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_cpu_info() {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) return;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "model name", 10) == 0) {
            printf("CPU:         %s", strchr(line, ':') + 2);
            break;
        }
    }
    fclose(fp);
}

void print_mem_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) return;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "MemTotal", 8) == 0 || strncmp(line, "MemFree", 7) == 0) {
            printf("%s", line);
        }
    }
    fclose(fp);
}

void print_uptime() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (fp) {
        double uptime;
        if (fscanf(fp, "%lf", &uptime) == 1) {
            int h = (int)uptime / 3600;
            int m = ((int)uptime % 3600) / 60;
            int s = (int)uptime % 60;
            printf("Uptime:      %dh %dm %ds\n", h, m, s);
        }
        fclose(fp);
    }
}

int main() {
    printf("--- 🌌 cosmic-os System Information ---\n");
    printf("OS:          cosmic-os Stage 2\n");
    print_cpu_info();
    print_mem_info();
    print_uptime();
    printf("---------------------------------------\n");
    return 0;
}
