CC = gcc
CFLAGS = -Wall -Wextra -IHeaders
LDFLAGS = -lncurses

SRC_DIR = src_code
BIN_DIR = App

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/input.c $(SRC_DIR)/inventory.c $(SRC_DIR)/utils.c $(SRC_DIR)/ui.c
TARGET = $(BIN_DIR)/shop

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(BIN_DIR)/shop.exe
	rm -rf $(BIN_DIR)
run: all
	./$(TARGET)
