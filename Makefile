CC=gcc
CFLAGS=-Wall -Wextra -Iinclude
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
TARGET=sudokuc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	del $(TARGET).exe 2>nul || true
