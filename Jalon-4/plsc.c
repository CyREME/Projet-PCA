#include "plsc.h"



texte * plsc(texte * texteA, texte * texteB) {

    int tailleA = texteA->cptJetons;
    int tailleB = texteB->cptJetons;

    int M[tailleA + 1][tailleB + 1];

    for (int i = 0; i <=tailleA;i++) M[i][0];
    for (int j = 0; j <=tailleA;j++) M[0][j];
    
    for (int i = 1; i <= tailleA; i++) {
        for (int j = 1; j <= tailleB; j++) {
            token * jetonA = texteA->jetons[i - 1];
            token * jetonB = texteB->jetons[j - 1];

            if (jetonA->type == WORD && jetonB->type == WORD && jetonA->data.word == jetonB->data.word) {
                M[i][j] = M[i - 1][j - 1] + 1;
            } else {
                // max entre la case du dessus M[i-1][j] et la case de gauche M[i][j-1]
                int max_haut = M[i - 1][j];
                int max_gauche = M[i][j - 1];
                M[i][j] = (max_haut > max_gauche) ? max_haut : max_gauche;
            }
        }
    }
    // Chainage arrière.

/*  int m,n;
    m = tailleA;
    n = tailleB;
    while (m != 0 && n!=0) {
        int min[]
    }*/  
    
    return texteC;
}