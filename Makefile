# Declaring/Filling directories to compile
BINARY := ./bin
SRCDIRS := ./src/ ./src/data/ ./src/presentation/
CLDIRS := ./src/data/ ./src/presentation/

# Declaring/Filling compiler variables
CC := gcc
DEPENDENCYFLAGS := -MD -MP
CFLAGS := -Wall -Wextra -g -pedantic -Wattributes -Wimplicit-int \
	-Wimplicit-function-declaration -Wincompatible-pointer-types \
	-Wint-conversion -Wmain -Wpointer-arith -Wpointer-sign \
	$(foreach DIRECTORY, $(INCLDIRS), -I $(DIRECTORY)) $(DEPENDENCYFLAGS)

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
