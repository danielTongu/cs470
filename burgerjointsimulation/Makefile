# Makefile for Burger Joint Simulation

CC = gcc
CFLAGS = -Wall -pthread

all: server client

server: server.c common.c common.h
	$(CC) $(CFLAGS) server.c common.c -o server

client: client.c common.c common.h
	$(CC) $(CFLAGS) client.c common.c -o client

run-server:
	./server 25 2

run-client:
	./client 127.0.0.1 54321 10

clean:
	rm -f server client
