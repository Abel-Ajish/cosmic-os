#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname buffer;

    if (uname(&buffer) != 0) {
        perror("uname");
        return 1;
    }

    printf("🌌 Welcome to cosmic-os\n");
    printf("Kernel Name:    %s\n", buffer.sysname);
    printf("Node Name:      %s\n", buffer.nodename);
    printf("Kernel Release: %s\n", buffer.release);
    printf("Version:        %s\n", buffer.version);
    printf("Machine:        %s\n", buffer.machine);

    return 0;
}
