#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_SIZE 3        /**< Standard Tic-Tac-Toe board size */
#define PORT 8080         /**< Default networking port */
#define MAX_PLAYERS 10    /**< Maximum number of players */

/* ================== GAME STRUCTURES ================== */

/**
 * @struct Player
 * @brief Represents a player in the game.
 */
typedef struct {
 int socket;  /**< Player's network socket */
 int id;      /**< Unique Player ID */
 int active;  /**< 1 = Available, 0 = Playing */
} Player;

/**
 * @struct Game
 * @brief Represents an active game session.
 */
typedef struct {
 int game_id;            /**< Unique game identifier */
 int player_x_socket;    /**< Socket for Player X */
 int player_o_socket;    /**< Socket for Player O */
 char board[MAX_SIZE][MAX_SIZE]; /**< Game board state */
 int current_turn;       /**< 0 = Player X, 1 = Player O */
 int active;             /**< 1 = In Progress, 0 = Completed */
} Game;

/* ================== FUNCTION PROTOTYPES ================== */

/* Game Logic */
void initializeBoard(Game *game);
void displayBoard(Game *game);
int checkWin(Game *game, char symbol);
int makeMove(Game *game, int position, char symbol);

/* Server & Client Networking */
int isServerRunning();
void promoteNewHost();

#endif