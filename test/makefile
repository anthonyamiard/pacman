# Variables generales
TARGET = test_lab

# Repertoires
OBJDIR	= ../obj
BINDIR	= ../bin
SRCDIR	= ../src
INCDIR	= ../include
TESTDIR	= .
DIRS	= $(OBJDIR) $(BINDIR)

# Fichiers
SOURCES	:= $(wildcard $(SRCDIR)/*.c)
INCLUDES:= $(wildcard $(INCDIR)/*.h)
OBJECTS	:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: DIRS
all: $(DIRS) $(BINDIR)/$(TARGET)

# Creation des repertoires de compilation
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
	
# Edition de liens
$(BINDIR)/%: $(TESTDIR)/%.o $(OBJECTS)
	@$(LINKER) $^ -o $@ $(LFLAGS)
	@echo "Edition de liens de "$@" terminée !"

# Dependances de chaque fichier
taille_lab_h: $(INCDIR)/taille_lab.h

objets_h: $(INCDIR)/objets.h taille_lab_h

labyrinthe_h: $(INCDIR)/labyrinthe.h taille_lab_h

IA_h: $(INCDIR)/IA.h taille_lab_h objets_h

test_lab.o: labyrinthe_h

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
