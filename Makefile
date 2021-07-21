OBJS	= markov.o main.o
SOURCE	= markov.cpp main.cpp
HEADER	= markov.h
OUT	= markov
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

markov.o: markov.cpp
	$(CC) $(FLAGS) markov.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)
