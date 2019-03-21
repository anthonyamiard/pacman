# Variables generales
TARGET			= pacman
export CC		= gcc
export CFLAGS	= -Wall -g
export LINKER	= gcc
export LFLAGS	=

# Repertoires
OBJDIR				= obj
BINDIR				= bin
SRCDIR				= src
INCDIR				= include
GUIDIR				= gui
TESTDIR				= test
export SDL_DIR		= $(HOME)/SDL2
export SDLLIB_DIR	= $(SDL_DIR)/lib
export SDLINC_DIR	= $(SDL_DIR)/include
DIRS				= $(OBJDIR) $(BINDIR)

# Bibliotheques
export LIBS		= -L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image
export INCLUDES	= -I$(SDLINC_DIR)

# Fichiers
SOURCES		:= $(wildcard $(SRCDIR)/*.c)
SRCGUI		:= $(wildcard $(GUIDIR)/*.c)
# INCLUDES	:= $(wildcard $(INCDIR)/*.h)
OBJECTS		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJGUI		:= $(SRCGUI:$(GUIDIR)/%.c=$(OBJDIR)/%.o)
export rm	= rm -f

.PHONY: DIRS
all: $(DIRS) $(BINDIR)/$(TARGET)

# Creation des repertoires de compilation
$(OBJDIR):
	@mkdir -p $(OBJDIR)
$(BINDIR):
	@mkdir -p $(BINDIR)

# Edition de liens
$(BINDIR)/$(TARGET): $(OBJECTS) $(OBJGUI)
	@$(LINKER) $^ -o $@ $(LIBS) $(LFLAGS)
	@echo "Edition de liens terminee !"

# Dependances de chaque fichier
# fichier_h: $(INCDIR)/fichier.h dependance_h
# $(OBJDIR)/fichier.o: dependance_h
taille_lab_h: $(INCDIR)/taille_lab.h

objets_h: $(INCDIR)/objets.h taille_lab_h

labyrinthe_h: $(INCDIR)/labyrinthe.h taille_lab_h

IA_h: $(INCDIR)/IA.h taille_lab_h objets_h

gui_lab_h: $(GUIDIR)/gui_lab.h taille_lab_h

$(OBJDIR)/labyrinthe.o: labyrinthe_h

$(OBJDIR)/IA.o: IA_h labyrinthe_h objets_h

$(OBJDIR)/objets.o: objets_h

$(OBJDIR)/gui_lab.o: gui_lab_h

# Compilation des .c en .o
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@echo "Compilation de "$<" terminee !"

$(OBJGUI): $(OBJDIR)/%.o: $(GUIDIR)/%.c
	@$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@echo "Compilation de "$<" terminee !"

# Test
.PHONY: test
test:
	@(cd $(TESTDIR) && $(MAKE))

# Nettoyage et suppression des executables
.PHONY: clean
clean:
	@(cd $(TESTDIR) && $(MAKE) $@)
	@$(rm) $(OBJDIR)/*.o
	@echo "Nettoyage termine !"

.PHONY: remove
remove: clean
	@(cd $(TESTDIR) && $(MAKE) $@)
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executables supprimes !"
