#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "plsc.h"

int main() {
    // 1. Initialisation de la table de hachage global/strhash si besoin
    table_hash * th = createTableHash(100);

    // 2. Chargement des deux textes à comparer
    texte * texteA = creation_texte();
    textToToken(th, texteA, charger_fichier("Hier_Encore.txt"));
    
    texte * texteB = creation_texte();
    textToToken(th, texteB, charger_fichier("Hier_Encore_2.txt"));

    assert(texteA != NULL);
    assert(texteB != NULL);

    // 3. Calcul de l'alignement PLSC
    texte * texteC = plsc(texteA, texteB);
    assert(texteC != NULL);

    // 5. Assertions globales


    // "Hier" remplacer par "Aujourd'hui"
    assert(strcmp(texteC->jetons[1]->data.word, "Aujourd'hui") == 0);
    assert(texteC->jetons[1]->type == 5);
    
    // "encore" insérer
    assert(strcmp(texteC->jetons[7]->data.word, "encore") == 0);
    assert(texteC->jetons[7]->type == 4);  // Insertion de "encore"
    
    // "encore" supprimer
    assert(strcmp(texteC->jetons[256]->data.word, "encore") == 0);
    assert(texteC->jetons[256]->type == 3);   // Suppression de "encore"

    // un espace
    assert(texteC->jetons[8]->data.space[0]== ' ');
    assert(texteC->jetons[8]->type == 1);   // Suppression de "encore"

    return 0;
}