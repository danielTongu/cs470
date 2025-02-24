/**
 * @file server.c
 * @brief Burger Joint Server - Handles client connections, manages dynamic burger production, and assigns waitresses.
 *
 * This server listens for incoming client connections and processes burger orders dynamically.
 * The restaurant will only produce burgers on request and stop once the maximum limit is reached.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "common.h"


#define DEFAULT_MAX_BURGERS 50  // Maximum number of burgers before restaurant closes
#define DEFAULT_CHEFS 2  // Initial number of chefs working in the restaurant
#define MAX_CHEFS 10  // Maximum allowed chefs
#define SERVER_PORT 54321  // Server port number


// Global variables
int total_burgers;  // Total burgers the restaurant can make before closing
int remaining_burgers;  // Burgers ready to be served
int num_chefs;  // Number of chefs actively cooking
int client_counter = 0;  // Track clients by assigning IDs
int pending_orders = 0;  // Tracks burgers requested but not yet cooked
pthread_mutex_t burger_mutex;  // Mutex to protect shared resources
pthread_cond_t order_cond;  // Condition variable for order requests
pthread_cond_t cook_cond;  // Condition variable for burger completion


/**
 * @brief Chef thread function - Waits for burger orders and only cooks on demand.
 * @param arg Chef ID
 */
void *chef_function(void *arg) {
    int chef_id = *(int *)arg;
    free(arg);
    while (1) {
        pthread_mutex_lock(&burger_mutex);

        // Wait until an order is placed
        while (pending_orders <= 0 && total_burgers > 0) {
            pthread_cond_wait(&order_cond, &burger_mutex);
        }

        // Stop cooking if all burgers have been made
        if (total_burgers <= 0) {
            pthread_mutex_unlock(&burger_mutex);
            break;
        }

        // If there are pending orders, prepare a burger
        if (pending_orders > 0) {
            pending_orders--;
            total_burgers--;
            pthread_mutex_unlock(&burger_mutex);

            // Simulate cooking time (either 2 or 4 seconds randomly)
            int cook_time = (rand() % 2 == 0) ? 2 : 4;
            printf("Chef %d is cooking a burger (%d sec)\n", chef_id, cook_time);
            sleep(cook_time);

            // Notify waitresses that a burger is ready to be served
            pthread_mutex_lock(&burger_mutex);
            remaining_burgers++;
            pthread_cond_signal(&cook_cond);
            pthread_mutex_unlock(&burger_mutex);
        } else {
            pthread_mutex_unlock(&burger_mutex);
        }
    }
    printf("Chef %d has stopped cooking. No more burgers left.\n", chef_id);
    return NULL;
}


/**
 * @brief Waitress thread function - Takes orders from clients and serves burgers.
 * @param arg Client socket descriptor.
 */
void *waitress_function(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);
    int burgers_requested;
    recv(client_socket, &burgers_requested, sizeof(int), 0);
    pthread_mutex_lock(&burger_mutex);
    client_counter++;
    int client_id = client_counter;
    printf("Client %d ordered %d burgers.\n", client_id, burgers_requested);

    // Check if the request exceeds the available burgers
    if (burgers_requested > total_burgers) {
        int response = -1;
        send(client_socket, &response, sizeof(int), 0);
        printf("Sorry, Client %d. We only have %d burgers left.\n", client_id, total_burgers);
        pthread_mutex_unlock(&burger_mutex);
        close(client_socket);
        return NULL;
    }

    // Add order to pending queue and notify chefs
    pending_orders += burgers_requested;
    pthread_cond_broadcast(&order_cond);
    pthread_mutex_unlock(&burger_mutex);

    for (int i = 1; i <= burgers_requested; i++) {
        pthread_mutex_lock(&burger_mutex);
        while (remaining_burgers <= 0) {
            pthread_cond_wait(&cook_cond, &burger_mutex);
        }
        remaining_burgers--;
        pthread_mutex_unlock(&burger_mutex);

        int served_burger = i;
        send(client_socket, &served_burger, sizeof(int), 0);
        printf("Waitress served burger %d to Client %d.\n", served_burger, client_id);
    }

    printf("Client %d has been served %d burgers.\n", client_id, burgers_requested);
    close(client_socket);
    return NULL;
}


/**
 * @brief Main function - Initializes server, creates chefs, and listens for clients.
 */
int main(int argc, char *argv[]) {
    num_chefs = (argc > 2) ? atoi(argv[2]) : DEFAULT_CHEFS;
    total_burgers = (argc > 1) ? atoi(argv[1]) : DEFAULT_MAX_BURGERS;
    remaining_burgers = 0;
    pending_orders = 0;

    if (total_burgers <= 0 || num_chefs <= 0 || num_chefs > MAX_CHEFS) {
        printf("Invalid input values. Please provide valid numbers for max burgers and chefs.\n");
        return EXIT_FAILURE;
    }

    pthread_mutex_init(&burger_mutex, NULL);
    pthread_cond_init(&order_cond, NULL);
    pthread_cond_init(&cook_cond, NULL);

    // Create chef threads
    pthread_t chefs[num_chefs];
    for (int i = 0; i < num_chefs; i++) {
        int *chef_id = malloc(sizeof(int));
        *chef_id = i + 1;
        pthread_create(&chefs[i], NULL, chef_function, chef_id);
    }

    // Start the restaurant server
    int server_socket = setup_server(SERVER_PORT);
    if (server_socket < 0) {
        printf("Restaurant is closed.\n");
        exit(EXIT_FAILURE);
    }

    while (total_burgers > 0) {
        int client_socket = accept_client(server_socket);
        if (client_socket < 0) continue;
        pthread_t waitress_thread;
        int *pclient = malloc(sizeof(int));
        *pclient = client_socket;
        pthread_create(&waitress_thread, NULL, waitress_function, pclient);
    }

    // Shutdown restaurant when all burgers are served
    printf("Restaurant has served all burgers and is closing.\n");
    for (int i = 0; i < num_chefs; i++) {
        pthread_join(chefs[i], NULL);
    }
    pthread_mutex_destroy(&burger_mutex);
    pthread_cond_destroy(&order_cond);
    pthread_cond_destroy(&cook_cond);
    close(server_socket);
    return 0;
}