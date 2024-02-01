CC = gcc
CFLAGS = -Wall -Wextra -g

main: main.c
	$(CC) $(CFLAGS) main.c -o main

.PHONY: clean
clean:
	rm -f main
