CC = gcc
CFLAGS = -g -O3 -Wall -Wextra -pedantic -std=c99
SRC_DIR = ./src
BUILD_DIR = .

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET = create

.PHONY: all clean

all: $(TARGET) clean 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o 
