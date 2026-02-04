#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

void print_interface(int sock, char *name) {
    struct ifreq ifr;
    strcpy(ifr.ifr_name, name);

    printf("\033[1;36m┌── %-10s ──────────────────────────────┐\033[0m\n", name);

    // Get IP Address
    if (ioctl(sock, SIOCGIFADDR, &ifr) == 0) {
        printf("\033[1;36m│\033[0m \033[1;33mIP Address:\033[0m %-30s \033[1;36m│\033[0m\n", 
               inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    } else {
        printf("\033[1;36m│\033[0m \033[1;33mIP Address:\033[0m %-30s \033[1;36m│\033[0m\n", "Not Assigned");
    }

    // Get MAC Address
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
        unsigned char *hw = (unsigned char *)ifr.ifr_hwaddr.sa_data;
        printf("\033[1;36m│\033[0m \033[1;33mMAC Address:\033[0m %02x:%02x:%02x:%02x:%02x:%02x                \033[1;36m│\033[0m\n",
               hw[0], hw[1], hw[2], hw[3], hw[4], hw[5]);
    }

    // Get Status (Flags)
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
        char *status = (ifr.ifr_flags & IFF_UP) ? "UP" : "DOWN";
        char *link = (ifr.ifr_flags & IFF_RUNNING) ? "CONNECTED" : "DISCONNECTED";
        printf("\033[1;36m│\033[0m \033[1;33mStatus:\033[0m %s / %-22s \033[1;36m│\033[0m\n", status, link);
    }

    printf("\033[1;36m└────────────────────────────────────────────┘\033[0m\n");
}

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket error");
        return 1;
    }

    char buf[1024];
    struct ifconf ifc;
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;

    if (ioctl(sock, SIOCGIFCONF, &ifc) < 0) {
        perror("SIOCGIFCONF error");
        return 1;
    }

    printf("\n\033[1;35m📡 Cosmic Network Interface Summary\033[0m\n");
    struct ifreq *it = ifc.ifc_req;
    struct ifreq *end = it + (ifc.ifc_len / sizeof(struct ifreq));

    for (; it < end; ++it) {
        print_interface(sock, it->ifr_name);
    }

    close(sock);
    return 0;
}
