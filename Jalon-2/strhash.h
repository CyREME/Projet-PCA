/* -------------------------------------------------------------------
   LACROIX & CELLIER
   -------------------------------------------------------------------
   Test unitaire du module de table de hashage - Fonctions utilitaires
   -------------------------------------------------------------------
   05/11/26 SR creation
  -------------------------------------------------------------------
*/


#ifndef TEST_HASH_HELPERS_H
#define TEST_HASH_HELPERS_H


/* ---------------------------------------------------------
   Structure d'un nœud de la liste
   ---------------------------------------------------------
*/
struct _list_node {
    void * donnee;
    struct _list_node * next;
};

typedef struct _list_node s_node;



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
int freeTab(table_hash * tab);

/*Libération donnée table*/
int freeData(table_hash * tab);

/*Ajout mot (pas de doublon)*/
int tableAppendWord(table_hash * tab, char * mot);

/*Suppression d'un mot dans la table*/
int tableDeleteWord(table_hash * tab, char * mot);

/*Affichage stat table*/
void printStatTable(table_hash * tab);








#endif