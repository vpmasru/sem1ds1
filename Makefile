# Makefile for a C project with source files in the src directory

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source directory
SRC_DIR = src

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = queue_sort_list

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJS) $(TARGET)
