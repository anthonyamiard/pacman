# Variables generales
EXEC		= pacman
TARGETS		= pacman test_lab test_IA test_objets test_evenement
CC		= gcc
CFLAGS		= -Wall -g
LINKER		= gcc
LFLAGS		= -Wall

# Repertoires
OBJDIR		= obj
BINDIR		= bin
SRCDIR		= src
INCDIR		= include
GUIDIR		= gui
TESTDIR		= test

# SDL
SDL_DIR		= $(HOME)/SDL2
SDLLIB_DIR	= $(SDL_DIR)/lib
SDLINC_DIR	= $(SDL_DIR)/include
DIRS		= $(OBJDIR) $(BINDIR)

# Bibliotheques
LIBS		= -L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES	= -I$(SDLINC_DIR)

# Fichiers
SOURCES		:= $(wildcard $(SRCDIR)/*.c)
SRCTESTS	:= $(wildcard $(TESTDIR)/*.c)
SRCGUI		:= $(wildcard $(GUIDIR)/*.c)
OBJECTS		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS		:= $(TARGETS:%=$(OBJDIR)/%.o)
# Fichiers .o sans main
OBJS		:= $(filter-out $(MAINS),$(OBJECTS))
OBJGUI		:= $(SRCGUI:$(GUIDIR)/%.c=$(OBJDIR)/%.o)
OBJTESTS	:= $(SRCTESTS:$(TESTDIR)/%.c=$(OBJDIR)/%.o)
TRGS		:= $(TARGETS:%=$(BINDIR)/%)
rm		= rm -f

.PHONY: DIRS

# default: $(DIRS) $(BINDIR)/$(EXEC)

all: $(DIRS) $(TRGS)

# Creation des repertoires de compilation
$(OBJDIR):
	@mkdir -p $(OBJDIR)
$(BINDIR):
	@mkdir -p $(BINDIR)

# Edition de liens
$(TRGS): $(OBJECTS) $(OBJGUI) $(OBJTESTS)
	@$(LINKER) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(OBJGUI) $(LFLAGS) -o $@ $(LIBS) $(LFLAGS)
	@echo "Edition de liens pour "$@" terminee !"

# Compilation
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@echo "Compilation de "$<" terminee !"

$(OBJGUI): $(OBJDIR)/%.o: $(GUIDIR)/%.c
	@$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@echo "Compilation de "$<" terminee !"
	
$(OBJTESTS): $(OBJDIR)/%.o: $(TESTDIR)/%.c
	@$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@echo "Compilation de "$<" terminee !"

# Nettoyage et suppression des executables
.PHONY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@echo "Nettoyage termine !"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGETS)
	@echo "Executables supprimes !"
