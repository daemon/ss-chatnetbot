CC = g++
CFLAGS = -O3 -Wall -std=c++11
OBJECTS = Observer.o ChatnetBot.o MarkovChainBot.o main.o
EXEC = chatnetbot

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o