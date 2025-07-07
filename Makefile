# Makefile for the Physical Activities Management System
# Compatible with macOS ARM64 and x86_64

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = activities
SOURCE = imperative-c/Source.c
DATA_FILES = imperative-c/customer.txt imperative-c/activity.txt imperative-c/plan.txt

# Detect operating system
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS
    CFLAGS += -D__MACOS__
endif

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Compilation completed! Executable: ./$(TARGET)"
	@echo "Architecture: $(shell uname -m)"

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

install-deps:
	@echo "Checking dependencies..."
	@which gcc > /dev/null || (echo "GCC not found. Install with: xcode-select --install" && exit 1)
	@echo "Dependencies OK!"

debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

release: CFLAGS += -DNDEBUG
release: $(TARGET)

help:
	@echo "Available commands:"
	@echo "  make           - Compile the program"
	@echo "  make run       - Compile and run"
	@echo "  make clean     - Remove compiled files"
	@echo "  make debug     - Compile debug version"
	@echo "  make release   - Compile optimized version"
	@echo "  make install-deps - Check dependencies"

.PHONY: all run clean install-deps debug release help 