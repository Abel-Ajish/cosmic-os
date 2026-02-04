#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_fetch() {
    printf(" \033[1;36m        .          \033[1;35m  _         _ \033[0m\n");
    printf(" \033[1;36m      .o88o.       \033[1;35m | |       (_) \033[0m\n");
    printf(" \033[1;36m    .88888888.     \033[1;35m | | _____  _ _ __ ___\033[0m\n");
    printf(" \033[1;36m   .8888888888.    \033[1;35m | |/ / _ \\| | '__/ _ \\\033[0m\n");
    printf(" \033[1;36m    '88888888'     \033[1;35m |   < (_) | | | |  __/\033[0m\n");
    printf(" \033[1;36m      'o88o'       \033[1;35m |_|\\_\\___/|_|_|  \\___|\033[0m\n");
    printf(" \033[1;36m        '          \033[1;35m                      \033[0m\n");
    
    printf("\033[1;33m OS:      \033[0m cosmic-os Stage 3+\n");
    printf("\033[1;33m KERNEL:  \033[0m 6.6.15-cosmic\n");
    printf("\033[1;33m SHELL:   \033[0m cosmic-shell (Pro)\n");
    printf("\033[1;33m APPS:    \033[0m hello, top, edit, fetch\n");
    printf("\033[1;33m IDENTITY:\033[0m cosmic user\n");
    
    // Quick memory summary
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "MemTotal:", 9) == 0) {
                printf("\033[1;33m MEMORY:  \033[0m %s", strchr(line, ':') + 2);
            }
        }
        fclose(fp);
    }
}

int main() {
    print_fetch();
    return 0;
}
