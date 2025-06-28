#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

#define PORT 41234  // Port number for UDP communication
#define MAX_BUFFER 1024
#define MAX_CLIENTS 5

// Function to initialize Winsock
void initWinsock() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        exit(1);
    }
}

// Function to generate a random target number between 1 and 100
int generateRandomNumber() {
    return rand() % 100 + 1; // Random number between 1 and 100
}

// Function to handle a single client request
void handleClient(SOCKET serverSocket, struct sockaddr_in clientAddr, int clientAddrSize, int *currentTarget, struct sockaddr_in clients[], int *clientCount) {
    char buffer[MAX_BUFFER];
    int guess;
    int targetNumber = generateRandomNumber();  // Generate random number for each game

    // Notify all clients about the new target number
    char response[MAX_BUFFER];
    sprintf(response, "New target number is being guessed now. Guess the number (1-100).");
    for (int i = 0; i < *clientCount; i++) {
        sendto(serverSocket, response, strlen(response), 0, (struct sockaddr*)&clients[i], clientAddrSize);
    }

    // Handle guessing
    while (1) {
        // Receive data from client
        int bytesReceived = recvfrom(serverSocket, buffer, MAX_BUFFER, 0, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (bytesReceived == SOCKET_ERROR) {
            printf("Error receiving data: %d\n", WSAGetLastError());
            continue;
        }

        buffer[bytesReceived] = '\0';
        guess = atoi(buffer);  // Convert the guess to an integer

        printf("Received guess: %d\n", guess);

        // Basic input validation
        if (guess < 1 || guess > 100) {
            char response[] = "Invalid input! Please guess a number between 1 and 100.";
            sendto(serverSocket, response, strlen(response), 0, (struct sockaddr*)&clientAddr, clientAddrSize);
            continue;
        }

        // Compare guess with the target number
        if (guess == *currentTarget) {
            // Client has guessed correctly
            strcpy(response, "Correct! You guessed the number.");
            *currentTarget = generateRandomNumber();  // New number after the correct guess

            // Notify all clients about the new number
            char newTargetMessage[MAX_BUFFER];
            sprintf(newTargetMessage, "Target number has been guessed! New number is being generated. Keep guessing!");
            for (int i = 0; i < *clientCount; i++) {
                // Send to all clients except the one who guessed correctly
                if (memcmp(&clientAddr, &clients[i], sizeof(clientAddr)) != 0) {
                    sendto(serverSocket, newTargetMessage, strlen(newTargetMessage), 0, (struct sockaddr*)&clients[i], clientAddrSize);
                }
            }

            // Send correct message to the guessing client
            sendto(serverSocket, response, strlen(response), 0, (struct sockaddr*)&clientAddr, clientAddrSize);

            // Terminate client session (client that guessed correctly)
            printf("Client guessed correctly and terminated.\n");
            break;
        } else if (guess < *currentTarget) {
            strcpy(response, "Higher! Try again.");
        } else {
            strcpy(response, "Lower! Try again.");
        }

        // Send response to the client
        sendto(serverSocket, response, strlen(response), 0, (struct sockaddr*)&clientAddr, clientAddrSize);
    }
}

// Function to add client to the clients list
void addClient(struct sockaddr_in *clients, struct sockaddr_in clientAddr, int *clientCount) {
    if (*clientCount < MAX_CLIENTS) {
        clients[*clientCount] = clientAddr;
        (*clientCount)++;
        printf("New client added. Total clients: %d\n", *clientCount);
    } else {
        printf("Max clients reached!\n");
    }
}

int main() {
    initWinsock();

    SOCKET serverSocket;
    struct sockaddr_in serverAddr, clientAddr, clients[MAX_CLIENTS];
    int clientAddrSize = sizeof(clientAddr);
    char buffer[MAX_BUFFER];
    int currentTarget = generateRandomNumber();  // Global target number for the game
    int clientCount = 0;  // Track number of clients

    // Seed the random number generator to get different values each time the server runs
    srand(time(NULL));

    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket == INVALID_SOCKET) {
        printf("Error creating socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Listen on all network interfaces
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Server is listening on port %d\n", PORT);

    // Start receiving guesses from any client
    while (1) {
        // Wait for incoming client messages
        int bytesReceived = recvfrom(serverSocket, buffer, MAX_BUFFER, 0, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (bytesReceived == SOCKET_ERROR) {
            printf("Error receiving data: %d\n", WSAGetLastError());
            continue;
        }

        buffer[bytesReceived] = '\0';  // Null-terminate the received message

        // Add the new client to the list
        addClient(clients, clientAddr, &clientCount);

        printf("Received guess from client: %s\n", buffer);

        // Handle the client communication
        handleClient(serverSocket, clientAddr, clientAddrSize, &currentTarget, clients, &clientCount);
    }

    // Cleanup
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}