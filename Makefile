# Makefile for Advanced Dictionary System

CC = gcc
CFLAGS = -Wall -O2 -std=c99
CLI_TARGET = dictionary_app.exe
GUI_TARGET = dictionary_gui.exe

.PHONY: all cli gui clean run

# Default: build CLI version
all: cli

# Build CLI version
cli:
	$(CC) $(CFLAGS) -o $(CLI_TARGET) dictionary.c spellchecker.c main.c

# Build GUI version (requires GTK3)
gui:
	compile_gui.bat

# Run CLI version
run: cli
	./$(CLI_TARGET)

# Clean all compiled files
clean:
	del /f $(CLI_TARGET) $(GUI_TARGET) *.o 2>nul || echo Cleaned
