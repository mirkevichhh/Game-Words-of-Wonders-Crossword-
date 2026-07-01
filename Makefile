CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lncurses -lm

SRC = program.c
TARGET = program

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
