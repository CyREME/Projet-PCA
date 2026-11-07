#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strhash.h"

int main(void) {
    /* 1. Création */
    table_hash * tab = createTableHash(10);
    assert(tab != NULL);
    assert(tab->size == 10);

    /* 2. Ajout de mots et gestion des doublons */
    assert(tableAppendWord(tab, "aba") == 1);
    assert(tableAppendWord(tab, "aba") == 0); // Refus du doublon
    assert(tableAppendWord(tab, "bonsoir") == 1);
    assert(tableAppendWord(tab, "salut") == 1);
    assert(tableAppendWord(tab, "bonjour") == 1);
    assert(tableAppendWord(tab, "bye") == 1);
    assert(tableAppendWord(tab, "mario") == 1);
    assert(tableAppendWord(tab, "figue") == 1);

    /* 3. Suppression de mots */
    assert(tableDeleteWord(tab, "absent") == 0); // Mot non présent
    assert(tableDeleteWord(tab, "salut") == 1);  // Suppression réussie
    assert(tableDeleteWord(tab, "salut") == 0);  // Déjà supprimé

    /* 4. Statistiques */
    printStatTable(tab);

    /* 5. Libération et Destruction (en toute fin !) */
    assert(freeData(tab) == 1);
    assert(freeTable(tab) == 1);

    return 0;
}