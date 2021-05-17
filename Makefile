CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = CUps

all: main.o command_parser.o fetch_process.o
	$(CC) -o $(EXE) main.o command_parser.o fetch_process.o

main.o: main.c command_parser.h fetch_process.h
	$(CC) $(WARNING_FLAGS) -c main.c

command_parser.o: command_parser.c command_parser.h 
	$(CC) $(WARNING_FLAGS) -c command_parser.c

fetch_process.o: fetch_process.c fetch_process.h
	$(CC) $(WARNING_FLAGS) -c fetch_process.c

clean:
	rm -f $(EXE) *.o
	
	