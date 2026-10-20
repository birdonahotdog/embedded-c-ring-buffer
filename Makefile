.RECIPEPREFIX := >
CC = gcc
CPPFLAGS = -Iinclude
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -g

TARGET = build/test_ring_buffer
SOURCES = src/ring_buffer.c tests/test_ring_buffer.c

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SOURCES) include/ring_buffer.h
>@mkdir -p build
>$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@

test: $(TARGET)
>./$(TARGET)

clean:
>rm -rf build
