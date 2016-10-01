NAME=statobar
CFLAGS=-Iincludes $(shell pkg-config --libs --cflags gio-2.0) -g -Wall -std=c++11 -o bin/$(NAME)
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

deploy:
	rm ~/.bin/$(NAME)
	cp bin/$(NAME) ~/.bin/$(NAME)
	i3-msg restart
