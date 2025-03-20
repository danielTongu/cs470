CC = gcc
CFLAGS = -Wall -pthread
SERVER_EXEC = server
CLIENT_EXEC = client

all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): server.c tictactoe.c
	$(CC) $(CFLAGS) server.c tictactoe.c -o $(SERVER_EXEC)

$(CLIENT_EXEC): client.c tictactoe.c
	$(CC) $(CFLAGS) client.c tictactoe.c -o $(CLIENT_EXEC)

run-server: $(SERVER_EXEC)
	./$(SERVER_EXEC)

run-client: $(CLIENT_EXEC)
	@echo "Enter server IP:"
	@read SERVER_IP && ./$(CLIENT_EXEC) $$SERVER_IP

clean:
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC)