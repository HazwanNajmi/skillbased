#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#define S_PORT 8443

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in s_addr, c_addr;
    socklen_t c_addr_len = sizeof(c_addr);
    char buffer[4]; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Failed to create socket");
        return 1;
    }
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_port = htons(S_PORT);

    if (bind(sockfd, (struct sockaddr*)&s_addr, sizeof(s_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    if (listen(sockfd, 1) < 0) {
        perror("Failed to listen ");
        close(sockfd);
        return 1;
    }

    printf("Server is listening for incoming connections...\n");

    newsockfd = accept(sockfd, (struct sockaddr*)&c_addr, &c_addr_len);
    if (newsockfd < 0) {
        perror("Failed to accept");
        close(sockfd);
        return 1;
    }

    srand(time(NULL));
    int random_num = rand() % 900 + 100;

    printf("The server generated random number of : %d\n", random_num);

    snprintf(buffer, sizeof(buffer), "%d", random_num);

    if (send(newsockfd, buffer, strlen(buffer), 0) < 0) {
        perror("Failed to send data");
        close(newsockfd);
        close(sockfd);
        return 1;
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
