NAME=status-to-json
CFLAGS=-g -Wall -std=c++11 -o $(NAME)
SRCS=*.cc
CC=g++

# Do all
all: main

# Compile
main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)

# Clean
clean:
	rm -f $(NAME)
	rm -f *.h~
	rm -f *.cc~
	rm -f Makefile~
