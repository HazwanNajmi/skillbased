#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define S_PORT 8443
#define MAX_BUFFER_SIZE 4 

int main() {
    int sockfd;
    struct sockaddr_in s_addr;
    char buffer[MAX_BUFFER_SIZE];
    char s_ip[16]; 

    printf("Please enter the server IP address: ");
    if (fgets(s_ip, sizeof(s_ip), stdin) == NULL) {
        perror("Failed to read server IP address");
        return 1;
    }

    s_ip[strcspn(s_ip, "\n")] = '\0';

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Failed to create socket");
        return 1;
    }

    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(S_PORT);
    if (inet_pton(AF_INET, s_ip, &s_addr.sin_addr) <= 0) {
        perror("Invalid server IP address");
        close(sockfd);
        return 1;
    }

   
    if (connect(sockfd, (struct sockaddr*)&s_addr, sizeof(s_addr)) < 0) {
        perror("Failed to connect");
        close(sockfd);
        return 1;
    }

    
    int bytes_received = recv(sockfd, buffer, MAX_BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("Failed to receive data");
        close(sockfd);
        return 1;
    }

    
    buffer[bytes_received] = '\0';

    int random_num = atoi(buffer);

    printf("The random number is received from server: %d\n", random_num);

    close(sockfd);
    return 0;
}
