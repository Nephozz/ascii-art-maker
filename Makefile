CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -MMD -MP

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
BIN = bin

.PHONY: all clean run dirs

all: dirs ascii-viewer

dirs:
	mkdir -p $(BIN)

run: all
	./$(BIN)/ascii-viewer

ascii-viewer: $(OBJ)
	$(CC) -o $(BIN)/ascii-viewer $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Deleting files and directories..."
	rm -f $(BIN)/ascii-viewer $(OBJ) $(DEP)
	@echo "Cleanup complete."

-include $(DEP)