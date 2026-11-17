#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "texte.h"

int main(void) {
    // 1. PRÉPARATION
    table_hash * tab = createTableHash(10);
    texte * monTexte = creation_texte();
    
    // On simule le contenu d'un fichier directement en RAM
    char bufferTest[] = "A  B\n";

    // 2. EXÉCUTION
    textToToken(tab, monTexte, bufferTest);

    // 3. VÉRIFICATIONS (Asserts)
    // Vérification du nombre total de jetons
    assert(monTexte->cptJetons == 4);

    // --- VÉRIFICATION DU JETON 0 ("A") ---
    // À COMPLÉTER

    // --- VÉRIFICATION DU JETON 1 ("  ") ---
    // À COMPLÉTER

    // 4. NETTOYAGE
    liberer_texte(monTexte);
    freeData(tab);
    freeTable(tab);

    return 0;
}