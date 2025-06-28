#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

#define SERVER_IP "127.0.0.1"  // Server IP (localhost)
#define PORT 41234  // Port number for UDP communication
#define MAX_BUFFER 1024

// Function to initialize Winsock
void initWinsock() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        exit(1);
    }
}

int main() {
    initWinsock();

    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[MAX_BUFFER];

    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket == INVALID_SOCKET) {
        printf("Error creating socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Game logic
    printf("Welcome to 'Guess the Number' Game!\n");
    while (1) {
        printf("Enter your guess: ");
        fgets(buffer, MAX_BUFFER, stdin);

        // Send guess to the server
        sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        // Receive feedback from server
        int bytesReceived = recvfrom(clientSocket, buffer, MAX_BUFFER, 0, NULL, NULL);
        buffer[bytesReceived] = '\0';

        printf("Server: %s\n", buffer);

        // End game if guessed correctly
        if (strcmp(buffer, "Correct! You guessed the number.") == 0) {
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
