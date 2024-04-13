#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h> // For errno

#define PORT 8080
#define PING_MESSAGE "ping"
#define PONG_MESSAGE "pong"
#define EXIT_FAILURE -1

int main() {
    int sock;
    char buffer[1024];
    struct sockaddr_in addr, cli;

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    memset(&cli, 0, sizeof(cli));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY; // Listen on any interface

    // Bind the socket with the server address
    if (bind(sock, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("Bind failed\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Receive ping or any other message from any address
        int len = sizeof(cli);
        if (recvfrom(sock, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&cli, &len) < 0) {
            printf("Recvfrom failed\n");
            exit(EXIT_FAILURE);
        }

        printf("Received: %s\n", buffer);

        sleep(1);

        // Send pong back to the sender
        if (sendto(sock, (const char *)PONG_MESSAGE, strlen(PONG_MESSAGE), 0, (const struct sockaddr *)&cli, len) < 0) {
            printf("Sendto failed\n");
            exit(EXIT_FAILURE);
        }
    }

    close(sock);
    return 0;
}
