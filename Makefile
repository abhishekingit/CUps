CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = CUps

all: main.o command_parser.o
	$(CC) -o $(EXE) main.o command_parser.o

main.o: main.c command_parser.h
	$(CC) $(WARNING_FLAGS) -c main.c

command_parser.o: command_parser.c command_parser.h 
	$(CC) $(WARNING_FLAGS) -c command_parser.c

clean:
	rm -f $(EXE) *.o
	
	