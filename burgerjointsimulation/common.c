/**
 * @file common.c
 * @brief Common utility functions for socket communication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "common.h"

/**
 * @brief Sets up a server socket.
 * @param port Port number to bind the server.
 * @return Server socket file descriptor.
 */
int setup_server(int port) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);
    return server_socket;
}

/**
 * @brief Accepts a client connection.
 * @param server_socket Server socket file descriptor.
 * @return Client socket file descriptor.
 */
int accept_client(int server_socket) {
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket < 0) {
        perror("Client accept failed");
        return -1;
    }
    printf("Client connected.\n");
    return client_socket;
}

/**
 * @brief Sets up a client socket and connects to the server.
 * @param ip Server IP address.
 * @param port Server port number.
 * @return Client socket file descriptor.
 */
int setup_client(const char *ip, int port) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return -1;
    }

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }
    printf("Connected to server at %s:%d\n", ip, port);
    return client_socket;
}