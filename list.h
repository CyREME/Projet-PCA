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


/* =================================================================
   1. FONCTIONS UTILITAIRES DE TEST ET D'AFFICHAGE
   ================================================================= */

/* -----------------------------------------------------------------
   Conversion d'un nœud pointant sur un int en chaîne de caractères
   -----------------------------------------------------------------
   node   : pointeur sur le nœud à convertir
   buffer : tampon d'accueil pour la chaîne obtenue
   size   : taille maximale du tampon
   -----------------------------------------------------------------
   retourne : 1 si la chaîne convertie dépasse le tampon, 0 sinon
   -----------------------------------------------------------------
*/
int node_int_to_string(s_node * node, char * buffer, int size);

/* -----------------------------------------------------------------
   Conversion de l'ensemble de la liste en chaîne de caractères
   (Exemple de format généré : "1 -> 2 -> null")
   -----------------------------------------------------------------
   head           : pointeur sur la tête de liste
   node_to_string : fonction de conversion d'un nœud en texte
   -----------------------------------------------------------------
   retourne : la chaîne de caractères représentant la liste
   -----------------------------------------------------------------
*/
char * list_to_string(s_node * head,  
                      int (*node_to_string)(s_node * node, char * buffer, int buffer_size));

/* -----------------------------------------------------------------
   Compare le contenu affiché d'une liste à une chaîne attendue
   -----------------------------------------------------------------
   head           : pointeur sur la tête de liste
   node_to_string : fonction de conversion d'un nœud en texte
   waited         : chaîne de caractères attendue
   -----------------------------------------------------------------
   retourne : 1 si le résultat reçu est celui attendu, 0 sinon
   -----------------------------------------------------------------
*/
int check_list_state(s_node * head,  
                     int (*node_to_string)(s_node * node, char * buffer, int size),
                     const char * waited);


/* =================================================================
   2. INTERFACE PUBLIQUE DU MODULE LISTE
   ================================================================= */

/* -----------------------------------------------------------------
   Création d'une nouvelle liste vide
   -----------------------------------------------------------------
   Aucun paramètre
   -----------------------------------------------------------------
   retourne : NULL (représentant la liste vide)
   -----------------------------------------------------------------
*/
s_node * list_create(void);

/* -----------------------------------------------------------------
   Lecture de la donnée contenue dans un nœud
   -----------------------------------------------------------------
   node : pointeur sur le nœud à consulter
   -----------------------------------------------------------------
   retourne : un pointeur générique (void *) vers la donnée
   -----------------------------------------------------------------
*/
void * list_get_data(s_node * node);

/* -----------------------------------------------------------------
   Écriture / modification de la donnée d'un nœud
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
   retourne : le pointeur vers le nœud suivant (ou NULL si fin)
   -----------------------------------------------------------------
*/
s_node * list_next(s_node * head);

/* -----------------------------------------------------------------
   Création et insertion d'un nouveau nœud en tête de liste
   -----------------------------------------------------------------
   head : pointeur sur la tête actuelle de la liste
   data : donnée à insérer dans le nouveau nœud
   -----------------------------------------------------------------
   retourne : la nouvelle tête de liste
   -----------------------------------------------------------------
*/
s_node * list_insert(s_node * head, void * data);

/* -----------------------------------------------------------------
   Création et ajout d'un nouveau nœud en queue de liste
   -----------------------------------------------------------------
   head : pointeur sur la tête de liste
   data : donnée à insérer
   -----------------------------------------------------------------
   retourne : la tête de liste
   -----------------------------------------------------------------
*/
s_node * list_append(s_node * head, void * data);

/* -----------------------------------------------------------------
   Suppression du nœud en tête de liste
   -----------------------------------------------------------------
   head : pointeur sur la tête de liste actuelle
   -----------------------------------------------------------------
   retourne : la nouvelle tête de liste après suppression
   -----------------------------------------------------------------
*/
s_node * list_headRemove(s_node * head);

/* -----------------------------------------------------------------
   Suppression de la première instance d'une donnée dans la liste
   -----------------------------------------------------------------
   head : pointeur sur la tête de liste
   data : donnée à rechercher et supprimer
   -----------------------------------------------------------------
   retourne : la tête de liste mise à jour
   -----------------------------------------------------------------
*/
s_node * list_remove(s_node * head, void * data);

/* -----------------------------------------------------------------
   Insertion d'une donnée dans une liste ordonnée (sans doublon)
   -----------------------------------------------------------------
   head    : adresse du pointeur sur la tête de liste
   compare : fonction de comparaison renvoyant <0, 0 ou >0
   param   : donnée à insérer
   -----------------------------------------------------------------
   retourne : la tête de liste mise à jour
   -----------------------------------------------------------------
*/
s_node * list_orderedAppend(s_node ** head,
                            int (*compare)(s_node *, void *),
                            void * param);

/* -----------------------------------------------------------------
   Destruction complète d'une liste (libération des nœuds)
   -----------------------------------------------------------------
   head : pointeur sur la tête de liste à détruire
   -----------------------------------------------------------------
*/
void list_destroy(s_node * head);

#endif