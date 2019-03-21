# Repertoires
OBJDIR	= ../obj
BINDIR	= ../bin
SRCDIR	= ../src
INCDIR	= ../include
TESTDIR	= .
DIRS	= $(OBJDIR) $(BINDIR)

TARGETS= $(BINDIR)/test_lab $(BINDIR)/test_IA $(BINDIR)/test_objets $(BINDIR)/test_evenement

# Fichiers
SOURCES	:= $(wildcard $(SRCDIR)/*[^main].c)
# INCLUDES:= $(wildcard $(INCDIR)/*.h)
OBJECTS	:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: DIRS
all: $(DIRS) $(TARGETS)

# Creation des repertoires de compilation
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

# Edition de liens
$(BINDIR)/%: $(OBJDIR)/%.o $(OBJECTS)
	@$(LINKER) $^ -o $@ $(LIBS) $(LFLAGS)
	@echo "Edition de liens de "$@" terminée !"

# Dependances de chaque fichier
# fichier_h: $(INCDIR)/fichier.h dependance_h
# $(OBJDIR)/fichier.o: dependance_h
taille_lab_h: $(INCDIR)/taille_lab.h

objets_h: $(INCDIR)/objets.h taille_lab_h

labyrinthe_h: $(INCDIR)/labyrinthe.h taille_lab_h

IA_h: $(INCDIR)/IA.h taille_lab_h objets_h

dessin_h: $(GUIDIR)/dessin.h

gui_lab_h: $(GUIDIR)/gui_lab.h taille_lab_h

$(OBJDIR)/labyrinthe.o: labyrinthe_h

$(OBJDIR)/IA.o: IA_h labyrinthe_h objets_h

$(OBJDIR)/objets.o: objets_h

$(OBJDIR)/test_lab.o: labyrinthe_h

$(OBJDIR)/test_IA.o: IA_h labyrinthe_h objets_h

$(OBJDIR)/test_objets.o: objets_h IA_h

$(OBJDIR)/gui_lab.o: gui_lab_h dessin_h

$(OBJDIR)/dessin.o: dessin_h

# Compilation des .c en .o
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@echo "Compilation de "$<" terminee !"

$(OBJDIR)/%.o : $(TESTDIR)/%.c
	@$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@echo "Compilation de "$<" terminee !"

# Nettoyage et suppression des executables
.PHONY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@echo "Nettoyage termine !"

.PHONY: remove
remove: clean
	@$(rm) $(TARGETS)
	@echo "Executables supprimes !"
