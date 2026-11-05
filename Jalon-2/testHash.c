#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strhash.h"

int main() {

    /* Création Table Hash */
    table_hash tab = createTableHash(10);
    assert(0==0);

    
    /* Ajout mot dans table Hash */
    
    // 1 Vérification d'un ajout simple.
    assert(tableAppendWord(tab, "aba") == 1);
    tableAppendWord(tab, "aba");
    
    // 2. mot vide
    assert(tableAppendWord(tab, "") == 0);
    
    // 3. mot deja existant
    
    assert(tableAppendWord(tab, "aba") == 0);

    
    /* Libération donnée d'une table Hash*/
    
    //3.1 Libération réussi
    assert(freeData(tab)==1);

    
    
    /* Destruction d'une table Hash*/
    
    //2.1 Table vide

    assert(destroy(tab)==0);

    //2.2 Table non vide
    assert(destroy(tab)==1);

    
    /* Suppresion d'un mot dans table Hash*/

    //5.1

    tableAppendWord(tab, "bonsoir");
    assert(tableDeleteWord(tab, "salut") == 0);
    assert(tableDeleteWord(tab, "bonsoir")== 1);
    /* Affiche Stat*/

    //6.1 Affichage
    
    printStatTable(tab);

    return 1;
}