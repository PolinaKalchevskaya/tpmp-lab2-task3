# Makefile for Cinema project
# Author: Kalchevskaya Polina, group 10

CC = gcc
CFLAGS = -I./include -Wall -Wextra
TARGET = bin/cinema
OBJDIR = obj
SRCDIR = src
INCDIR = include

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@
	@echo "Build complete: $(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR) 

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
	@echo "Clean complete"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
