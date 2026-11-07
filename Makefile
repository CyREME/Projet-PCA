# Options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g -IJalon-1 -IJalon-2
LDFLAGS = -lm

# Nom des exécutables
EXEC_J1 = test_list
EXEC_J2 = test_hash

# Règle par défaut : compile tout
all: $(EXEC_J1) $(EXEC_J2)

# --- Exécutable Jalon 1 ---
$(EXEC_J1): Jalon-1/list.o Jalon-1/testList.o
	$(CC) $(CFLAGS) -o $@ $^

# --- Exécutable Jalon 2 ---
$(EXEC_J2): Jalon-1/list.o Jalon-2/strhash.o Jalon-2/testHash.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Règle de compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et des exécutables
clean:
	rm -f Jalon-1/*.o Jalon-2/*.o $(EXEC_J1) $(EXEC_J2)

.PHONY: all clean