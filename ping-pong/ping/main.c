#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h> // For fcntl
#include <errno.h> // For errno

#define PORT 8080
#define PING_MESSAGE "ping"
#define PONG_MESSAGE "pong"
#define EXIT_FAILURE -1

int main() {
    int sock;
    char buffer[1024];
    struct sockaddr_in addr;
    int rc;

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Socket creation failed\n");
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_BROADCAST; // Broadcast address

    // Enable broadcasting
    int broadcastEnable = 1;
    if ((rc = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable))) < 0) {
        printf("Setsockopt failed\n");
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in cli;

    // Make the socket non-blocking
    if (fcntl(sock, F_SETFL, O_NONBLOCK) < 0) {
        printf("Failed to set socket to non-blocking\n");
        exit(EXIT_FAILURE);
    }

    int len = sizeof(cli);
    int ret;

    while (1) {
        // Send ping to broadcast address
        if (sendto(sock, (const char *)PING_MESSAGE, strlen(PING_MESSAGE), 0, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
            printf("Sendto failed\n"); 
            printf("Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        sleep(0.1);

        ret = recvfrom(sock, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&cli, &len);
        
        if (ret == 0 || (ret < 0 && errno == EWOULDBLOCK)) {
		// Timeout
        } else {
            if (ret < 0 && errno != EWOULDBLOCK) {
                printf("Recvfrom failed\n");
                exit(EXIT_FAILURE);
            }

            if (ret > 0) {
                break;
            }
        }
    }

    // Make the socket blocking
    if (fcntl(sock, F_SETFL, 0) < 0) {
        printf("Failed to set socket to blocking\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Send ping to broadcast address
        if (sendto(sock, (const char *)PING_MESSAGE, strlen(PING_MESSAGE), 0, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
            printf("Sendto failed\n");
            exit(EXIT_FAILURE);
        }

        
        ret = recvfrom(sock, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&cli, &len);
        if (ret < 0) {
            printf("Recvfrom failed\n");
            exit(EXIT_FAILURE);
        }

        printf("Received: %s\n", buffer);
        sleep(1);
    }

    close(sock);
    return 0;
}
