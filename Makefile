# Options de compilation
CC = gcc
# Options de compilation enrichies avec les avertissements recommandés (-Wpedantic, -Wshadow)
CFLAGS = -Wall -Wextra -Wpedantic -Wshadow -g -IJalon-1 -IJalon-2 -IJalon-3
LDFLAGS = -lm

# Options de débogage mémoire (AddressSanitizer + UndefinedBehaviorSanitizer)
SANFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

# Nom des exécutables
EXEC_J1 = test_list
EXEC_J2 = test_hash
EXEC_J3 = test_text

# Règle par défaut : compile tous les jalons
all: $(EXEC_J1) $(EXEC_J2) $(EXEC_J3)

# --- Exécutable Jalon 1 ---
$(EXEC_J1): Jalon-1/list.o Jalon-1/testList.o
	$(CC) $(CFLAGS) -o $@ $^

# --- Exécutable Jalon 2 ---
$(EXEC_J2): Jalon-1/list.o Jalon-2/strhash.o Jalon-2/testHash.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# --- Exécutable Jalon 3 ---
$(EXEC_J3): Jalon-1/list.o Jalon-2/strhash.o Jalon-3/texte.o Jalon-3/testTexte.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Règle spéciale de débogage avec AddressSanitizer (detecte fuites et erreurs mémoire)
debug: CFLAGS += $(SANFLAGS)
debug: LDFLAGS += $(SANFLAGS)
debug: re

# Règle de compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Recompilation complète
re: clean all

# Nettoyage des fichiers objets et des exécutables
clean:
	rm -f Jalon-1/*.o Jalon-2/*.o Jalon-3/*.o $(EXEC_J1) $(EXEC_J2) $(EXEC_J3)

.PHONY: all clean debug re