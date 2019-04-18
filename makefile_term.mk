#project name
TARGET = Othello_terminal_ed

CC=gcc


#compiling flags

CFLAGS   = -std=c99 -Wall -I.

LINKER   = gcc

# linking flags 
LFLAGS   = -Wall -I. -lm

#directories where each file should be
SRCDIR   = src/jeu_terminal
OBJDIR   = obj
BINDIR   = bin


DIRS	 = $(OBJDIR) $(BINDIR) 

.PHONY: DIRS
all: $(DIRS) $(BINDIR)/$(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

src/jeu_terminal  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f



$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"


