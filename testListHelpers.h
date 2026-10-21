/* ---------------------------------------------------------
   Test unitaire du module liste - Fonctions utilitaires
   ---------------------------------------------------------
   20/10/21 SR creation
   ---------------------------------------------------------
*/

#ifndef TEST_LIST_HELPERS_H
#define TEST_LIST_HELPERS_H

/* ---------------------------------------------------------
   Structure d'un nœud de la liste
   ---------------------------------------------------------
*/
struct _list_node {
   void * donnee;
   struct _list_node * next;
};

typedef struct _list_node s_node;


/* --- Fonctions de test et d'affichage --- */

/* -----------------------------------------------------------------
   Conversion d'un noeud pointant sur une donnée de type int
   en chaine de caracteres
   -----------------------------------------------------------------
   node   : pointeur sur le noeud à convertir
   buffer : tampon contenant la chaine obtenue
   size   : taille maximum de la chaine
   -----------------------------------------------------------------
   retourne 1 si la chaine convertie est trop longue pour le tampon,
            0 sinon
   -----------------------------------------------------------------
*/
int node_int_to_string(s_node * node, char * buffer, int size);

/* -----------------------------------------------------------------
   Conversion des données d'une liste en chaine de caracteres
   Les données sont séparées par " -> "
   -----------------------------------------------------------------
   head           : pointeur sur la tête de liste
   node_to_string : fonction pour convertir la valeur d'un nœud
   -----------------------------------------------------------------
   retourne la chaine de caractères représentant la liste
   -----------------------------------------------------------------
*/
char * list_to_string(s_node * head,  
                      int (*node_to_string)(s_node * node, char * buffer, int buffer_size));

/* -----------------------------------------------------------------
   Compare la chaine représentant une liste à une chaine attendue
   -----------------------------------------------------------------
   head           : pointeur sur la tête de liste
   node_to_string : fonction pour convertir la valeur d'un nœud
   waited         : chaine de caractères attendue
   -----------------------------------------------------------------
   retourne 1 si le résultat reçu est celui attendu,
            0 sinon
   -----------------------------------------------------------------
*/
int check_list_state(s_node * head,  
                     int (*node_to_string)(s_node * node, char * buffer, int size),
                     const char * waited);


/* --- Fonctions de manipulation de la liste --- */

/* -----------------------------------------------------------------
   Création d'une nouvelle liste vide
   -----------------------------------------------------------------
   Aucun paramètre
   -----------------------------------------------------------------
   retourne NULL (liste vide)
   -----------------------------------------------------------------
*/
s_node * list_create(void);

/* -----------------------------------------------------------------
   Lecture de la donnée contenue dans un nœud
   -----------------------------------------------------------------
   node : pointeur sur le nœud à lire
   -----------------------------------------------------------------
   retourne un pointeur générique (void *) vers la donnée
   -----------------------------------------------------------------
*/
void * list_get_data(s_node * node);

/* -----------------------------------------------------------------
   Écriture de la donnée contenue dans un nœud
   -----------------------------------------------------------------
   node : pointeur sur le nœud à modifier
   data : pointeur vers la nouvelle donnée
   -----------------------------------------------------------------
*/
void list_set_data(s_node * node, void * data);

/* -----------------------------------------------------------------
   Obtention du nœud suivant
   -----------------------------------------------------------------
   head : pointeur sur le nœud courant
   -----------------------------------------------------------------
   retourne le pointeur vers le nœud suivant
   -----------------------------------------------------------------
*/
s_node * list_next(s_node * head);

/* -----------------------------------------------------------------
   Création et insertion d'un nouveau nœud en tête de liste
   -----------------------------------------------------------------
   head : pointeur sur la tête actuelle de la liste
   data : donnée à insérer dans le nouveau nœud
   -----------------------------------------------------------------
   retourne la nouvelle tête de liste
   -----------------------------------------------------------------
*/
s_node * list_insert(s_node * head, void * data);

/* -----------------------------------------------------------------
   Création et ajout d'un nouveau nœud en queue de liste
   -----------------------------------------------------------------
   head : pointeur sur la tête de liste
   data : donnée à insérer
   -----------------------------------------------------------------
   retourne la tête de liste
   -----------------------------------------------------------------
*/
s_node * list_append(s_node * head, void * data);

/* -----------------------------------------------------------------
   Ajout d'un nœud dans une liste ordonnée
   -----------------------------------------------------------------
   head    : adresse du pointeur sur la tête de liste
   compare : fonction de comparaison de deux données
   param   : donnée à insérer
   -----------------------------------------------------------------
   retourne la tête de liste
   -----------------------------------------------------------------
*/
s_node * list_orderedAppend(s_node ** head,
                            int (*compare)(s_node *, void *), 
                            void * param);

#endif