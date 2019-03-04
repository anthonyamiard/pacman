# Variables generales
TARGET	=
export CC	= gcc
export CFLAGS	= -Wall -g
export LINKER	= gcc
export LFLAGS	=

# Repertoires
OBJDIR	= obj
BINDIR	= bin
SRCDIR	= src
INCDIR	= include
TESTDIR	= test
DIRS	= $(OBJDIR) $(BINDIR)

# Fichiers
SOURCES	:= $(wildcard $(SRCDIR)/*.c)
INCLUDES:= $(wildcard $(INCDIR)/*.h)
OBJECTS	:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
export rm	= rm -f

.PHONY: DIRS
all: $(DIRS) $(BINDIR)/$(TARGET)

# Creation des repertoires de compilation
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

# Edition de liens
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $^ -o $@ $(LFLAGS)
	@echo "Edition de liens terminee !"
	
# Dependances de chaque fichier
taille_lab_h: $(INCDIR)/taille_lab.h

objets_h: $(INCDIR)/objets.h taille_lab_h

labyrinthe_h: $(INCDIR)/labyrinthe.h taille_lab_h

IA_h: $(INCDIR)/IA.h taille_lab_h objets_h

# Compilation des .c en .o
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compilation de "$<" terminee !"

# Test
.PHONY: test
test:
	@(cd $(TESTDIR) && $(MAKE))
	
# Nettoyage et suppression des executables
.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Nettoyage termine !"

.PHONY: remove
remove: clean
	@(cd $(TESTDIR) && $(MAKE) $@)
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executables supprimes !"
