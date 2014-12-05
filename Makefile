CC = g++
CFLAGS = -O3 -Wall -std=c++11 -g
LDFLAGS = -lws2_32 -lwsock32
OBJECTS = Observer.o ChatnetBot.o main.o Command.o AboutCommand.o ChatnetConnection.o Common.o CommandSet.o HelpCommand.o Message.o Observable.o OwnerCommand.o Player.o ShutdownCommand.o ThreadPool.o 
EXEC = chatnetbot

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS) #order matters for windows

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o