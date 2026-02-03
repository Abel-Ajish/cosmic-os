#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_cpu_info() {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) return;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "model name", 10) == 0) {
            printf("CPU: %s", strchr(line, ':') + 2);
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
        if (strncmp(line, "MemTotal", 8) == 0) {
            printf("Memory: %s", strchr(line, ':') + 1);
            break;
        }
    }
    fclose(fp);
}

int main() {
    printf("--- cosmic-os System Info ---\n");
    print_cpu_info();
    print_mem_info();
    
    FILE *fp = fopen("/proc/version", "r");
    if (fp) {
        char version[512];
        if (fgets(version, sizeof(version), fp)) {
            printf("Kernel: %s", version);
        }
        fclose(fp);
    }
    return 0;
}
