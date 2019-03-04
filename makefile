# Variables generales
TARGET	=
CC	= gcc
CFLAGS	= -Wall -g
LINKER	= gcc
LFLAGS	=

# Repertoires
OBJDIR	= obj
BINDIR	= bin
SRCDIR	= src
INCDIR	= include
DIRS	= $(OBJDIR) $(BINDIR)

# Fichiers
SOURCES	:= $(wildcard $(SRCDIR)/*.c)
INCLUDES:= $(wildcard $(INCDIR)/*.h)
OBJECTS	:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm	= rm -f

.PHONY: DIRS
all: $(DIRS) $(BINDIR)/$(TARGET)

# Creation des repertoires de compilation
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

# Edition de lien
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $^ -o $@ $(LFLAGS)
	@echo "Edition de liens terminee !"

# Compilation des .c en .o
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compilation de "$<" terminee !"
	
# Nettoyage et suppression des executables
.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Nettoyage termine !"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executables supprimes !"
