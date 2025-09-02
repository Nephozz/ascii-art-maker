CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -g -MMD -MP $(shell pkg-config --cflags opencv4)
LDFLAGS = $(shell pkg-config --libs opencv4)

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
	$(CC) -o $(BIN)/ascii-viewer $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN)/ascii-viewer $(OBJ) $(DEP)

-include $(DEP)