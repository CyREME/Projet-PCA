#include "strhash.h"
#include <string.h>

/*Creation d'une table*/
table_hash * createTableHash(int size){
    if (size<0) return NULL;

    table_hash * tab = malloc(sizeof(table_hash));
    tab->size=size;

    
    s_node ** adresses = malloc(size * sizeof(s_node *));
    if (adresses == NULL) return NULL;
    tab->adresses = adresses;
    return tab;

}

/*Destruction d'une table*/
int freeTable(table_hash * tab){
    for (int i=0; i=tab->size; i++) {
        
        s_node * current = tab->adresses[i];

        while (current->next != NULL)
        {
            s_node * temp = current;
            current = temp->next;
            free(temp);
        }
        
    }
}

/*Libération donnée table*/
int freeData(table_hash * tab){}

/*Ajout mot (pas de doublon)*/
int tableAppendWord(table_hash * tab, char * mot){}

/*Suppression d'un mot dans la table*/
int tableDeleteWord(table_hash * tab, char * mot){}

/*Affichage stat table*/
void printStatTable(table_hash * tab){}

/*Calcul clé*/
int calculCle(table_hash * tab, char * mot) {

    int cle = 0;

    for (int i = 0; i < strlen(mot); i++) {
        cle *= 2;
        cle += (int)mot[i];
    }

    return cle % tab->size;

}.
