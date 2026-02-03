#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/reboot.h>
#include <linux/reboot.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: powerctl [reboot|halt]\n");
        return 1;
    }

    if (strcmp(argv[1], "reboot") == 0) {
        printf("Rebooting...\n");
        sync();
        reboot(LINUX_REBOOT_CMD_RESTART);
    } else if (strcmp(argv[1], "halt") == 0) {
        printf("Halting...\n");
        sync();
        reboot(LINUX_REBOOT_CMD_POWER_OFF);
    } else {
        printf("Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
