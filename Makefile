NAME=status-to-json
CFLAGS=-g -Wall -std=c++11 -o bin/$(NAME)
SRCS=*.cc
LIBS=-l asound
CC=g++

# Do all
all: main

# Compile
main: $(SRCS)
	$(CC) $(CFLAGS) $(LIBS) $(SRCS)

# Clean
clean:
	rm -f $(NAME)
	rm -f *.h~
	rm -f *.cc~
	rm -f Makefile~
