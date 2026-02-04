#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return 1;
    }

    long uptime = info.uptime;
    int days = uptime / 86400;
    int hours = (uptime % 86400) / 3600;
    int minutes = (uptime % 3600) / 60;
    int seconds = uptime % 60;

    printf("\033[1;36m✨ Cosmic Uptime:\033[0m ");
    if (days > 0) printf("%d days, ", days);
    printf("%02d:%02d:%02d\n", hours, minutes, seconds);

    return 0;
}
