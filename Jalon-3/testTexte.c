#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "texte.h"

int main(void) {
    // 1. PRÉPARATION
    table_hash * tab1 = createTableHash(10);
    table_hash * tab2 = createTableHash(10);
    table_hash * tab3 = createTableHash(10);
    table_hash * tab4 = createTableHash(10);

    texte * texte1 = creation_texte();
    texte * texte2 = creation_texte();
    texte * texte3 = creation_texte();
    texte * txtHier = creation_texte();

    // Creation des fichiers .txt
    FILE *ptrFile1, *ptrFile2, *ptrFile3;
    ptrFile1 = fopen("test1.txt", "w");
    fprintf(ptrFile1, " ");
    fclose(ptrFile1);

    ptrFile2 = fopen("test2.txt", "w");
    fprintf(ptrFile2, "Bonjour je suis un --jedi provenant\t\t\nde tatouine");
    fclose(ptrFile2);

    ptrFile3 = fopen("test3.txt", "w");
    fprintf(ptrFile3, " --Yo, je suis en y o \n\n\t-lol                           ");
    fclose(ptrFile3);
    
    // 2. Texte vers tokken
    
    char * txt1 = charger_fichier("test1.txt");
    char * txt2 = charger_fichier("test2.txt");
    char * txt3 = charger_fichier("test3.txt");
    char * hierEncore = charger_fichier("Hier_Encore.txt");
    
    textToToken(tab1, texte1, txt1);
    textToToken(tab2, texte2, txt2);
    textToToken(tab3, texte3, txt3);
    textToToken(tab4, txtHier, hierEncore);

    // 3. VÉRIFICATIONS (Asserts)
    // Vérificaion textes non NULL
    assert(texte1 != NULL);
    assert(texte2 != NULL);
    assert(texte3 != NULL);
    assert(hierEncore != NULL);
    
    // Vérification du nombre total de jetons pour chaque texte
    assert(texte1->cptJetons == 1);
    assert(texte2->cptJetons == 15);
    assert(texte3->cptJetons == 15);
    assert(txtHier->cptJetons == 443);

    // --- VÉRIFICATION DU TEXTE 1 ---
    assert(strcmp(texte1->jetons[0]->data.space, " ") == 0);
    assert(texte1->jetons[0]->textOffset == 0);
    assert(texte1->capacity == 50);
    
    // --- VÉRIFICATION DU TEXTE 2 ---
    assert(strcmp(texte2->jetons[0]->data.word, "Bonjour") == 0);
    assert(texte2->jetons[0]->textOffset == 0);

    assert(strcmp(texte2->jetons[3]->data.space, " ") == 0);
    assert(texte2->jetons[7]->textOffset == 18);

    assert(texte2->capacity == 50);

    // --- VÉRIFICATION DU TEXTE 3 ---

    // Teste d'un SHORT_SPACE
    assert(strcmp(texte3->jetons[12]->data.space, " \n\n\t") == 0);
    assert(texte3->jetons[12]->textOffset == 21);
    
    // Teste d'un SPACE
    assert(texte3->jetons[14]->type == SPACE);
    assert(texte3->jetons[14]->textOffset == 29);
    assert(texte3->capacity == 50);

    // --- VÉRIFICATION DU TEXTE 4 ---

    // Premier jeton ("Hier")
    assert(txtHier->jetons[0]->type == WORD);
    assert(txtHier->jetons[0]->textOffset == 0);
    assert(strcmp(txtHier->jetons[0]->data.word, "Hier") == 0);

    // Deuxième jeton (espace court)
    assert(txtHier->jetons[1]->type == SHORT_SPACE);
    assert(strcmp(txtHier->jetons[1]->data.space, " ") == 0);

    // Dernier jeton ("ans")
    assert(txtHier->jetons[442]->type == WORD);
    assert(strcmp(txtHier->jetons[442]->data.word, "ans") == 0);

    // 4. NETTOYAGE
    liberer_texte(texte1);
    liberer_texte(texte2);
    liberer_texte(texte3);

    freeData(tab1);
    freeData(tab2);
    freeData(tab3);

    freeTable(tab1);
    freeTable(tab2);
    freeTable(tab3);

    return 0;
}