# Declaring/Filling directories to compile
BINARY := ./bin
SRCDIRS := ./src/ ./src/data/
CLDIRS := ./src/data/

# Declaring/Filling compiler variables
CC := gcc
DEPENDENCYFLAGS := -MD -MP
CFLAGS := -Wall -Wextra -g -pedantic $(foreach DIRECTORY, $(INCLDIRS), -I $(DIRECTORY)) $(DEPENDENCYFLAGS)

# Declaring/Filling file variables
CFILES := $(foreach DIRECTORY, $(SRCDIRS), $(wildcard $(DIRECTORY)*.c))
OBJECTFILES := $(patsubst %.c, %.o, $(CFILES))
DEPENDENCYFILES := $(patsubst %.c, %.d, $(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTFILES)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

.PHONY: clean
clean:
	rm -rf $(BINARY) $(OBJECTFILES) $(DEPENDENCYFILES)
