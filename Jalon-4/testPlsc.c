#include <stdio.h>
#include <stdlib.h>
#include "strhash.h"
#include "texte.h"
#include "plsc.h"

// Fonction d'affichage de la matrice M
void afficher_matrice(int ** M, int nbrA, int nbrB) {
    printf("\n--- Matrice PLSC M [%d x %d] ---\n", nbrA + 1, nbrB + 1);
    for (int i = 0; i <= nbrA; i++) {
        for (int j = 0; j <= nbrB; j++) {
            printf("%2d ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char * argv[]) {
    // 1. Définition de deux fichiers de test ou création de textes simples
    if (argc < 3) {
        printf("Usage: %s <fichier_ref> <fichier_nouveau>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 2. Création de la table de hachage partagée
    table_hash * ht = createTableHash(100);

    // 3. Chargement des deux textes
    char * texteA = charger_fichier("Hier_Encore.txt");
    texte * textA = creation_texte();
    textToToken(ht, textA, texteA);

    
    char * texteB = charger_fichier("Hier_Encore.txt");
    texte * textB = creation_texte();
    textToToken(ht, textB, texteB);

    if (!textA || !textB) {
        fprintf(stderr, "Erreur lors du chargement des fichiers.\n");
        return EXIT_FAILURE;
    }

    // 4. Exécution du calcul de la PLSC et récupération du résultat
    printf("Text A : %d jetons\n", textA->cptJetons);
    printf("Text B : %d jetons\n", textB->cptJetons);

   texte * textAligned = plsc(textA, textB);

    // 5. Libération de la mémoire
    // (Pense à libérer textA, textB, textAligned et la table ht)

    return EXIT_SUCCESS;
}