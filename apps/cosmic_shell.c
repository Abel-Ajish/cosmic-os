#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void print_prompt() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        strcpy(cwd, "?");
    }
    printf("\033[1;36m🌌 cosmic\033[0m@\033[1;35mos\033[0m:\033[1;34m%s$ \033[0m", cwd);
    fflush(stdout);
}

void help() {
    printf("--- 🌌 cosmic-os Help ---\n");
    printf("Built-in commands:\n");
    printf("  help      - Show this help message\n");
    printf("  cd <dir>  - Change directory\n");
    printf("  pwd       - Print working directory\n");
    printf("  sysinfo   - Display system information\n");
    printf("  clear     - Clear the terminal screen\n");
    printf("  reboot    - Reboot the system\n");
    printf("  poweroff  - Power off the system\n");
    printf("  exit      - Exit the shell\n");
    printf("\nStage 3+ commands:\n");
    printf("  cosmic-top   - View running processes\n");
    printf("  cosmic-edit  - Simple text editor\n");
    printf("  whoami       - Show current user\n");
    printf("  cosmic-fetch - System summary (ASCII art)\n");
    printf("\nYou can also run standard Linux commands from BusyBox (ls, cat, mkdir, etc).\n");
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    printf("\033[1;36mStarting Cosmic Shell (Pro Edition)...\033[0m\n");
    printf("Type 'help' for a list of commands.\n\n");

    while (1) {
        print_prompt();

        if (!fgets(line, MAX_LINE, stdin)) {
            break;
        }

        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;

        // Tokenize input
        int i = 0;
        args[i] = strtok(line, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            args[++i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue;
        }

        // Built-in commands
        if (strcmp(args[0], "help") == 0) {
            help();
        } else if (strcmp(args[0], "exit") == 0) {
            break;
        } else if (strcmp(args[0], "clear") == 0) {
            printf("\033[H\033[J");
        } else if (strcmp(args[0], "reboot") == 0) {
            system("/bin/powerctl reboot");
        } else if (strcmp(args[0], "poweroff") == 0) {
            system("/bin/powerctl poweroff");
        } else if (strcmp(args[0], "sysinfo") == 0) {
            system("/bin/sysinfo");
        } else if (strcmp(args[0], "pwd") == 0) {
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            }
        } else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                chdir("/");
            } else if (chdir(args[1]) != 0) {
                perror("cd");
            }
        } else {
            // External commands
            pid_t pid = fork();
            if (pid == 0) {
                // Try as absolute path first
                if (args[0][0] == '/' || args[0][0] == '.') {
                    execv(args[0], args);
                } else {
                    // Search in /bin and /sbin
                    char path[MAX_LINE];
                    snprintf(path, sizeof(path), "/bin/%s", args[0]);
                    execv(path, args);
                    
                    snprintf(path, sizeof(path), "/sbin/%s", args[0]);
                    execv(path, args);
                }
                
                // If execution reach here, command not found
                printf("cosmic: %s: command not found\n", args[0]);
                exit(1);
            } else if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);
            } else {
                perror("fork");
            }
        }
    }

    return 0;
}
