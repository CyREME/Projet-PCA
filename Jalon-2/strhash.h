/* -------------------------------------------------------------------
   LACROIX & CELLIER
   -------------------------------------------------------------------
   Test unitaire du module de table de hashage - Fonctions utilitaires
   -------------------------------------------------------------------
   05/11/26 SR creation
  -------------------------------------------------------------------
*/


#ifndef STRHASH_H
#define STRHASH_H

#include <math.h>
#include <stdio.h>
#include "list.h"

/* ---------------------------------------------------------
   Structure d'une table de hachage
   ---------------------------------------------------------
*/

typedef struct {
   int size;
  s_node ** adresses;
} table_hash;


/*Creation d'une table*/
table_hash * createTableHash(int size);

/*Destruction d'une table*/
int freeTable(table_hash * tab);

/*Libération donnée table*/
int freeData(table_hash * tab);

/*Ajout mot (pas de doublon)*/
int tableAppendWord(table_hash * tab, char * mot);

/*Suppression d'un mot dans la table*/
int tableDeleteWord(table_hash * tab, char * mot);

/*Affichage stat table*/
void printStatTable(table_hash * tab);

int calculCle(table_hash * tab, char * mot);

void minMaxTotElNode(table_hash * tab, int * min, int * max, int * tot);

float ecartType(table_hash * tab, float moyenne);

int nbElAdresses ( s_node * node);

#endif