#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_IP "203.106.71.185"
#define S_PORT 8443
#define BUFFER_SIZE 1024

int main() {
    int c_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (c_socket == -1) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    struct sockaddr_in s_address;
    memset(&s_address, 0, sizeof(s_address));
    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(S_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &s_address.sin_addr) <= 0) {
        perror("Invalid address ");
        close(c_socket);
        return EXIT_FAILURE;
    }

    if (connect(c_socket, (struct sockaddr*)&s_address, sizeof(s_address)) == -1) {
        perror("Failed to connect");
        close(c_socket);
        return EXIT_FAILURE;
    }

    char student_id[20];
    printf("Enter UiTM Student ID: ");
    scanf("%s", student_id);

    
    if (send(c_socket, student_id, strlen(student_id), 0) == -1) {
        perror("Send failed");
        close(c_socket);
        return EXIT_FAILURE;
    }
    char buffer[BUFFER_SIZE] = {0};
    if (recv(c_socket, buffer, BUFFER_SIZE, 0) == -1) {
        perror("Failed to receive");
        close(c_socket);
        return EXIT_FAILURE;
    }

    printf("Server Response: %s\n", buffer);

    close(c_socket);
    return EXIT_SUCCESS;
}
