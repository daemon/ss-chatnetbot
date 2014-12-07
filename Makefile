CC = g++
CFLAGS = -Iinclude -O3 -Wall -std=c++11
DEPENDS = depends
SRC = src
LDFLAGS = -L$(DEPENDS)/sqlite3 -lws2_32 -lwsock32 -pthread -lsqlite3 -static-libstdc++ -static-libgcc
OBJECTS = $(SRC)/BasicCommandSet.o $(SRC)/ChatnetBot.o $(SRC)/main.o $(SRC)/Command.o $(SRC)/AboutCommand.o $(SRC)/ChatnetConnection.o $(SRC)/Common.o $(SRC)/CommandSet.o $(SRC)/HelpCommand.o $(SRC)/Message.o $(SRC)/OwnerCommand.o $(SRC)/Player.o $(SRC)/ShutdownCommand.o $(SRC)/ThreadPool.o 
EXEC = bin/chatnetbot

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(SRC)/*.o