#include "plsc.h"
#include <stdlib.h>

texte * plsc(texte * texteA, texte * texteB) {

    int tailleA = texteA->cptJetons;
    int tailleB = texteB->cptJetons;

    texte * texteC = creation_texte();

    int m=0,n=0;
    
    //Création du tableau de * token, pour la matrice.
    token ** tabA=malloc(tailleA * (sizeof(token *)));
    for (int k = 0; k<tailleA; k++) {
        if (texteA->jetons[k]->type==WORD) {
            tabA[m++] = texteA->jetons[k];
        }
    }
    

    token ** tabB=malloc(tailleB * (sizeof(token *)));
    for (int k = 0; k<tailleB; k++) {
        if (texteB->jetons[k]->type==WORD) {
            tabB[n++] = texteB->jetons[k];
        }
    }


    int M[m + 1][n + 1];

    for (int i = 0; i <=m;i++) M[i][0]=0;
    for (int j = 0; j <=n;j++) M[0][j]=0;
    

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (tabA[i-1]->data.word == tabB[j-1]->data.word) {
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

    tailleB--;
    
    while (m != 0 && n!=0) {
        
        if (tailleB >= 0 && (texteB->jetons[tailleB]->type == SPACE || texteB->jetons[tailleB]->type == SHORT_SPACE)) {
            addTokken(texteC, texteB->jetons[tailleB--]);
            
        } else {
            token * tk = malloc(sizeof(token));
            if (tk == NULL) return NULL;
            if (tabA[m-1]->data.word == tabB[n-1]->data.word) {
                // Diagonale si égalité
                    n--;
                    *tk = *tabB[n];
                    m--;
                
            } else if (M[m-1][n] > M[m][n-1]) {
                // Haut > Gauche -> Suppression !
                    m--;
                    *tk = *tabA[m];
                    tk->type = ERASE;
                    tailleB++;

            } else if(M[m][n-1] > M[m-1][n]) {
                // Gauche > Haut -> Insertion !
                    n--;
                    *tk = *tabB[n];
                    tk->type = INSERT;
            } else {
                // Haut == Gauche -> Remplacement !
                    n--;
                    *tk = *tabB[n];
                    tk->type = REPLACE;
            }
            tailleB--;
            addTokken(texteC, tk);
        }
    }

    while (m > 0) {

        if (tailleB >= 0 && (texteB->jetons[tailleB]->type == SPACE || texteB->jetons[tailleB]->type == SHORT_SPACE)) {
            addTokken(texteC, texteB->jetons[tailleB--]);
        }else {
    token * tk = malloc(sizeof(token));
    if (tk == NULL) return NULL;
    m--;
    *tk = *tabA[m];
    tk->type = ERASE;
    addTokken(texteC, tk);
}
    }
        
    while (n > 0) {

        if (tailleB >= 0 && (texteB->jetons[tailleB]->type == SPACE || texteB->jetons[tailleB]->type == SHORT_SPACE)) {
            addTokken(texteC, texteB->jetons[tailleB--]);
        } else {
            token * tk = malloc(sizeof(token));
            if (tk == NULL) return NULL;
            n--;
            *tk = *tabB[n];
            tk->type = INSERT;
            tailleB--;
            addTokken(texteC, tk);
        }
    }

    reverse_array(texteC->jetons, texteC->cptJetons);

    free(tabA);
    free(tabB);

    return texteC;
}


void reverse_array(token ** tab, int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        // Echange de l'élément du début avec la fin
        token * temp = tab[start];
        tab[start] = tab[end];
        tab[end] = temp;

        // Move pointers inward
        // Avance le pointeur début et recule celui de fin
        start++;
        end--;
    }
}