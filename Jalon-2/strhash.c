#include "strhash.h"
#include <stdlib.h>
#include <string.h>

/*Creation d'une table*/
table_hash * createTableHash(int size){
    if (size<0) return NULL;

    table_hash * tab = malloc(sizeof(table_hash));
    tab->size=size;

    
    s_node ** adresses = malloc(size * sizeof(s_node *));
    if (adresses == NULL) {
        free(tab);
        return NULL;
    }
    tab->adresses = adresses;

    // utiliser create de list

    for(int i=0;i<tab->size;i++) {
        tab->adresses[i] = list_create();
    }
   

    return tab;

}

/*Destruction d'une table*/
int freeTable(table_hash * tab){
    for (int i=0; i < tab->size; i++) { // pour chaque entrée
        list_destroy(tab->adresses[i]);
    }
    free(tab->adresses);
    free(tab);
    
    return 1;
}

/*Libération donnée table*/
int freeData(table_hash * tab){
    for (int i=0; i < tab->size; i++) {
        s_node * current = tab->adresses[i]; // pour chaque entrée
        while(current!=NULL) { // tant qu'il y a un noeud suivant
            free(current->donnee);
            current = list_next(current);
             // on libere la donnée du noeud de la liste chainée
        }
    }

    return 1;
}

/*Ajout mot (pas de doublon)*/
int tableAppendWord(table_hash * tab, char * mot){

    int cle = calculCle(tab, mot);

    s_node * current = tab->adresses[cle];

    while(current!=NULL) {
        if (strcmp((char *)current->donnee, mot) == 0) return 0;
        current = list_next(current);
    }

    char * mot_copie = strdup(mot);

    tab->adresses[cle] = list_orderedAppend(&(tab->adresses[cle]), compare_string_node, mot_copie);
    
    return 1;
}

/*Suppression d'un mot dans la table*/
int tableDeleteWord(table_hash * tab, char * mot){
    int cle = calculCle(tab, mot);

    s_node * current = tab->adresses[cle];
    
    if (current == NULL) return 0;

    while(current!=NULL) {
        if (strcmp((char *)current->donnee, mot) == 0) {
            char * donneFree = (char *) list_get_data(current);
            tab->adresses[cle] = list_remove(tab->adresses[cle], donneFree);
            
            free(donneFree);

            return 1;
        }
        current = list_next(current);
    }

    return 0;

}

/*Affichage stat table*/
void printStatTable(table_hash * tab){
    int min;
    int max;
    int tot;

    minMaxTotElNode(tab, &min, &max, &tot);
    printf("Nombre total d'éléments : %d\nNombre minimum d'élément  : %d\nNombre Maximum d'éléments : %d\nEcart type : %lf\n",tot , min, max, ecartType(tab, (float)tot / tab->size));
        
}


/*Calcul clé*/
int calculCle(table_hash * tab, char * mot) {

    int cle = 0;

    for (size_t i = 0; i < strlen(mot); i++) {
        cle *= 2;
        cle += (int)mot[i];
    }

    return cle % tab->size;

}

void minMaxTotElNode(table_hash * tab, int * min, int * max, int * tot) {
    int sizeAdresses=nbElAdresses(tab->adresses[0]);
    *(min) = sizeAdresses;
    *(max) = sizeAdresses;
    *(tot) = sizeAdresses;
    
    for (int i=1; i < tab->size; i++) {
        int sizeAdresses=nbElAdresses(tab->adresses[i]);
        if (sizeAdresses<*(min)) {
            *(min)=sizeAdresses;
        }
        
        if (sizeAdresses>*(max)) {
            *(max)=sizeAdresses;
        }
        
        *(tot)+=sizeAdresses;
    }
    
}

int nbElAdresses ( s_node * node) {
    int c=0;
    while (node != NULL) {
        c++;
        node = list_next(node);
    }
    return c;
}

float ecartType(table_hash * tab, float moyenne) {
    float sumSquaredDeviations = 0;
    for (int i = 0; i < tab->size; i++) {
        float deviation = nbElAdresses(tab->adresses[i]) - moyenne;
        sumSquaredDeviations += deviation * deviation;
    }
    float variation = sumSquaredDeviations / tab->size;
    return sqrt(variation);
}