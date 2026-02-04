#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <sys/time.h>

#define PACKET_SIZE 64

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;
    for (sum = 0; len > 1; len -= 2) sum += *buf++;
    if (len == 1) sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cosmic-ping <host>\n");
        return 1;
    }

    struct hostent *host = gethostbyname(argv[1]);
    if (!host) {
        printf("Unknown host: %s\n", argv[1]);
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    memcpy(&addr.sin_addr, host->h_addr, host->h_length);

    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        perror("Socket error (Need root/cap_net_raw)");
        return 1;
    }

    struct timeval tv_out;
    tv_out.tv_sec = 1;
    tv_out.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out));

    printf("\033[1;36m📡 Cosmic Ping: Pinging %s [%s]...\033[0m\n", argv[1], inet_ntoa(addr.sin_addr));

    for (int i = 0; i < 4; i++) {
        struct icmp pckt;
        memset(&pckt, 0, sizeof(pckt));
        pckt.icmp_type = ICMP_ECHO;
        pckt.icmp_code = 0;
        pckt.icmp_id = getpid();
        pckt.icmp_seq = i;
        pckt.icmp_cksum = checksum(&pckt, sizeof(pckt));

        struct timeval start, end;
        gettimeofday(&start, NULL);

        if (sendto(sock, &pckt, sizeof(pckt), 0, (struct sockaddr *)&addr, sizeof(addr)) <= 0) {
            perror("Send error");
            continue;
        }

        char buffer[PACKET_SIZE + 100];
        struct sockaddr_in from;
        socklen_t len = sizeof(from);
        if (recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&from, &len) > 0) {
            gettimeofday(&end, NULL);
            double rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            printf("\033[1;32mReply from %s: bytes=64 time=%.2fms seq=%d\033[0m\n", inet_ntoa(from.sin_addr), rtt, i);
        } else {
            printf("\033[1;31mRequest timed out.\033[0m\n");
        }
        sleep(1);
    }

    close(sock);
    return 0;
}
