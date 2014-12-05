CC = g++
CFLAGS = -O3 -Wall -std=c++11 -g
LDFLAGS = -lws2_32 -lwsock32 -pthread
OBJECTS = BasicCommandSet.o ChatnetBot.o main.o Command.o AboutCommand.o ChatnetConnection.o Common.o CommandSet.o HelpCommand.o Message.o OwnerCommand.o Player.o ShutdownCommand.o ThreadPool.o 
EXEC = chatnetbot

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o