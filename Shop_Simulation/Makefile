# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -IHeaders

# Directories
SRC_DIR = src_code
BIN_DIR = App

# Source files and target
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/input.c $(SRC_DIR)/inventory.c $(SRC_DIR)/utils.c
TARGET = $(BIN_DIR)/shop

# Default target
all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean build
clean:
	rm -f $(BIN_DIR)/shop $(BIN_DIR)/shop.exe

# Run the app
run: all
	./$(TARGET)
