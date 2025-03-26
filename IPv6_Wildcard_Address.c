#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in6 server_addr;
    char port_str[6];
    int port;

    // Prompt user for the port number
    printf("Enter the port number to bind the server (e.g., 8080): ");
    fgets(port_str, sizeof(port_str), stdin);
    port = atoi(port_str); // Convert the input string to integer

    if (port <= 0 || port > 65535) {
        printf("Invalid port number. Please enter a number between 1 and 65535.\n");
        return 1;
    }

    // Create a socket for IPv6
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    // Set up the sockaddr_in6 structure for IPv6
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(port);  // Use user-provided port
    server_addr.sin6_addr = in6addr_any;  // IPv6 wildcard address (any address)

    // Bind the socket to the wildcard address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind socket");
        close(sockfd);
        exit(1);
    }

    printf("Server is bound to IPv6 wildcard address (::) on port %d\n", port);

    // Listen for incoming connections
    if (listen(sockfd, 5) < 0) {
        perror("Failed to listen on socket");
        close(sockfd);
        exit(1);
    }

    printf("Server is listening for incoming connections...\n");

    // Accept incoming connections (this is just an example; we're not accepting yet)
    // int newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    // (Further code to handle client connection would go here)

    // Close the socket
    close(sockfd);

    return 0;
}
