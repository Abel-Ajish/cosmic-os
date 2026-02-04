#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

void print_process_info(const char *pid_str) {
    char path[256];
    char comm[256] = "unknown";
    char state;
    long utime, stime;
    
    snprintf(path, sizeof(path), "/proc/%s/stat", pid_str);
    FILE *fp = fopen(path, "r");
    if (fp) {
        // Format of /proc/[pid]/stat: pid (comm) state ppid pgrp ...
        // We just need pid and comm for now
        if (fscanf(fp, "%*d (%[^)]) %c", comm, &state) == 2) {
            printf("%-8s %-16s %-8c\n", pid_str, comm, state);
        }
        fclose(fp);
    }
}

int main() {
    DIR *dir;
    struct dirent *entry;

    printf("\033[1;32m--- 🌌 cosmic-top: System Processes ---\033[0m\n");
    printf("%-8s %-16s %-8s\n", "PID", "COMMAND", "STATE");
    printf("---------------------------------------\n");

    dir = opendir("/proc");
    if (!dir) {
        perror("opendir /proc");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Check if the directory name is a number (PID)
        if (isdigit(entry->d_name[0])) {
            print_process_info(entry->d_name);
        }
    }

    closedir(dir);
    printf("---------------------------------------\n");
    return 0;
}
