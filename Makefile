# Compiler
CC = gcc

CFLAGS = -Wall -g -I$(INCDIR)
LDLIBS = -lncurses

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Name/path of the executable
TARGET = $(BINDIR)/game-of-life

SOURCES = $(wildcard $(SRCDIR)/*.c)

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# --- Compilation rules ---

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDLIBS)
	@echo "The program has been successfully compiled: $(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


# --- Cleaning rules ---

.PHONY: clean
clean:
	@echo "Cleaning archives..."	
	rm -rf $(OBJDIR) $(BINDIR)
