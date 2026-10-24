# Nom de l'exécutable final
EXEC = test_list

# Fichiers sources et objets
SRC = list.c testList.c
OBJ = $(SRC:.c=.o)

# Règle par défaut (compilation de l'exécutable)
all: $(EXEC)

# Création de l'exécutable à partir des fichiers objets
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation de chaque fichier .c en fichier .o
%.o: %.c list.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean