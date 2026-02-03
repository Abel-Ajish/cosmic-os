#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void mount_fs() {
    printf("[INIT] Mounting virtual filesystems...\n");
    if (mount("proc", "/proc", "proc", 0, NULL) != 0) perror("mount proc");
    if (mount("sysfs", "/sys", "sysfs", 0, NULL) != 0) perror("mount sys");
    if (mount("devtmpfs", "/dev", "devtmpfs", 0, NULL) != 0) perror("mount dev");
}

int main() {
    printf("[INIT] cosmic-os Init System (PID 1) started.\n");

    mount_fs();

    sethostname("cosmic-os", 9);

    printf("[INIT] Starting shell...\n");
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char *args[] = {"/bin/sh", NULL};
        execv("/bin/sh", args);
        // If execv returns, it failed
        perror("execv");
        exit(1);
    } else if (pid > 0) {
        // Parent process (PID 1)
        while (1) {
            int status;
            pid_t done = wait(&status);
            if (done == -1) {
                // No children left or error
                break;
            }
            printf("[INIT] Child process %d exited with status %d. Restarting...\n", done, status);
            // In a real init, we'd restart the shell or handle it
            pid = fork();
            if (pid == 0) {
                char *args[] = {"/bin/sh", NULL};
                execv("/bin/sh", args);
                exit(1);
            }
        }
    } else {
        perror("fork");
    }

    printf("[INIT] System halting.\n");
    return 0;
}
