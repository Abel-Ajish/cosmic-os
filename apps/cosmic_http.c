#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cosmic-http <host> [path]\n");
        printf("Example: cosmic-http google.com /\n");
        return 1;
    }

    char *host = argv[1];
    char *path = (argc > 2) ? argv[2] : "/";

    struct hostent *server = gethostbyname(host);
    if (!server) {
        printf("Error: Could not resolve host %s\n", host);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    memcpy(&addr.sin_addr.s_addr, server->h_addr, server->h_length);

    printf("\033[1;36m🌍 Connecting to %s...\033[0m\n", host);
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connect error");
        return 1;
    }

    char request[512];
    snprintf(request, sizeof(request), 
             "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", 
             path, host);

    send(sock, request, strlen(request), 0);

    printf("\033[1;32m[+] Request sent. Waiting for response...\033[0m\n\n");

    char buffer[BUFFER_SIZE];
    int bytes;
    while ((bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes] = 0;
        printf("%s", buffer);
    }

    close(sock);
    printf("\n\n\033[1;36m--- Cosmic HTTP: Transmission Complete ---\033[0m\n");
    return 0;
}
