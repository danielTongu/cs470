/**
* @file common.h
 * @brief Header file for common networking utilities.
 */

#ifndef COMMON_H
#define COMMON_H

#include <arpa/inet.h>

/**
 * @brief Sets up a server socket.
 * @param port Port number to bind the server.
 * @return Server socket file descriptor.
 */
int setup_server(int port);

/**
 * @brief Accepts a client connection.
 * @param server_socket Server socket file descriptor.
 * @return Client socket file descriptor.
 */
int accept_client(int server_socket);

/**
 * @brief Sets up a client socket and connects to the server.
 * @param ip Server IP address.
 * @param port Server port number.
 * @return Client socket file descriptor.
 */
int setup_client(const char *ip, int port);

#endif // COMMON_H