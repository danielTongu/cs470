/**
 * @file client.c
 * @brief Burger Joint Client - Connects to the server, orders burgers, and eats them.
 *
 * This client program connects to the restaurant server, requests a specified number
 * of burgers, and simulates eating them with a random delay.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "common.h"

#define DEFAULT_IP "127.0.0.1"  // Default server IP
#define SERVER_PORT 54321  // Server port number
#define DEFAULT_MAX_BURGERS 5  // Default number of burgers to order
#define EAT_TIMES {1, 3, 5}  // Possible times to eat each burger in seconds

/**
 * @brief Attempts to connect to the restaurant server.
 * @param server_ip The server's IP address.
 * @param port The server's port number.
 * @return The client socket file descriptor.
 */
int connect_to_server(const char *server_ip, int port) {
    int client_socket = setup_client(server_ip, port);
    if (client_socket < 0) {
        printf("Restaurant is closed.\n");
        exit(EXIT_FAILURE);
    }
    return client_socket;
}

int main(int argc, char *argv[]) {
    // Read server IP, port, and number of burgers from command-line arguments
    const char *server_ip = (argc > 1) ? argv[1] : DEFAULT_IP;
    int port = (argc > 2) ? atoi(argv[2]) : SERVER_PORT;
    int max_burgers = (argc > 3) ? atoi(argv[3]) : DEFAULT_MAX_BURGERS;

    if (max_burgers <= 0) {
        printf("Invalid number of burgers requested.\n");
        return EXIT_FAILURE;
    }

    // Connect to the restaurant server
    int client_socket = connect_to_server(server_ip, port);
    send(client_socket, &max_burgers, sizeof(int), 0);
    printf("Ordered %d burgers from the restaurant...\n", max_burgers);

    int burgers_received = 0;
    int eat_times[] = EAT_TIMES;
    while (burgers_received < max_burgers) {
        int served_burger;
        if (recv(client_socket, &served_burger, sizeof(int), 0) <= 0) {
            printf("Not enough burgers available.\n");
            break;
        }

        // Handle case where the restaurant informs the client that there are no more burgers
        if (served_burger == -1) {
            printf("The restaurant cannot fulfill the order.\n");
            break;
        }

        // Simulate eating the burger with a random delay
        burgers_received++;
        int eat_time = eat_times[rand() % 3];
        printf("Received burger %d. Eating (%d sec)\n", burgers_received, eat_time);
        sleep(eat_time);
    }

    // Inform the user when all ordered burgers are eaten
    printf("Finished eating %d burgers.\n", burgers_received);

    // Close the connection
    close(client_socket);
    return 0;
}