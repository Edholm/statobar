NAME=status-to-json
CFLAGS=-Iincludes -g -Wall -std=c++11 -o bin/$(NAME)
SRCS=src/*.cc
LIBS=-lasound -liw
CC=g++

# Do all
all: main

# Compile
main: $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) $(SRCS)

# Clean
clean:
	rm -f bin/$(NAME)
	rm -f *.h~
	rm -f *.cc~
	rm -f Makefile~
