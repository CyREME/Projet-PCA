/* ---------------------------------------------------------
   Test unitaire du module liste - Fonctions utilitaires
   ---------------------------------------------------------
   20/10/21 SR creation
   ---------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* Taille maximum de la chaîne représentant la liste complète */
#define LIST_AS_A_STRING_MAX_SIZE 1024

/* Taille maximum de la chaîne représentant un seul nœud */
#define NODE_AS_A_STRING_MAX_SIZE 100


/* =================================================================
   1. FONCTIONS UTILITAIRES POUR LES TESTS
   ================================================================= */

/* -----------------------------------------------------------------
   Convertit la donnée entière d'un nœud en chaîne de caractères
   -----------------------------------------------------------------
   node   : pointeur sur le nœud contenant un entier
   buffer : zone mémoire de destination pour la chaîne
   size   : taille maximale du tampon d'accueil
   -----------------------------------------------------------------
   retourne : 1 si la chaîne dépasse la taille du tampon, 0 sinon
   -----------------------------------------------------------------
*/
int node_int_to_string(s_node * node, char *buffer, int size) {
    int * value;
    int str_length;

    value = (int *)list_get_data(node);
    str_length = snprintf(buffer, size, "%d", *value);
    return (str_length >= size);
}

/* -----------------------------------------------------------------
   Formate l'ensemble de la liste sous forme de chaîne (ex: "1 -> 2 -> null")
   -----------------------------------------------------------------
   head           : pointeur vers la tête de la liste
   node_to_string : pointeur de fonction pour convertir un nœud en texte
   -----------------------------------------------------------------
   retourne : pointeur vers la chaîne de caractères représentant la liste
   -----------------------------------------------------------------
*/
char * list_to_string(s_node * head, 
                      int (*node_to_string)(s_node * node, char * buffer, int buffer_size)) {

    static char list_as_a_string[LIST_AS_A_STRING_MAX_SIZE];
    static char buffer[NODE_AS_A_STRING_MAX_SIZE];
    int length = 0;
    int max_length = LIST_AS_A_STRING_MAX_SIZE - 5; 

    while (head && length < max_length - 1) {
        int append;
        (void)(*node_to_string)(head, buffer, NODE_AS_A_STRING_MAX_SIZE - 1); 

        append = snprintf(list_as_a_string + length, 
                          max_length - length, "%s", buffer); 
        if (append >= max_length - length) length = max_length - 1;
        else                               length += append;    

        append = snprintf(list_as_a_string + length, 
                          max_length - length, " -> "); 
        if (append >= max_length - length) length = max_length - 1;
        else                               length += append;    

        head = list_next(head);
    }

    if (length == max_length - 1)
        sprintf(list_as_a_string + length, " ...");  
    else
        sprintf(list_as_a_string + length, "null"); 
        
    return list_as_a_string;
}

/* -----------------------------------------------------------------
   Vérifie si la représentation de la liste correspond au résultat attendu
   -----------------------------------------------------------------
   head           : pointeur vers la tête de la liste
   node_to_string : fonction de conversion d'un nœud en texte
   waited         : chaîne de caractères attendue
   -----------------------------------------------------------------
   retourne : 1 si le contenu est conforme, 0 en cas de différence
   -----------------------------------------------------------------
*/
int check_list_state(s_node * head, 
                     int (*node_to_string)(s_node * node, char * buffer, int size),
                     const char * waited) {
    char * obtained = list_to_string(head, node_to_string);
    if (strcmp(waited, obtained) != 0) {
        fprintf(stderr, "Attendu : %s \n Obtenu : %s\n", waited, obtained);
        return 0;
    }
    return 1;
}


/* =================================================================
   2. FONCTIONS DE MANIPULATION DE LA LISTE
   ================================================================= */

/* -----------------------------------------------------------------
   Initialise une nouvelle liste
   -----------------------------------------------------------------
   Aucun paramètre
   -----------------------------------------------------------------
   retourne : NULL (représentant une liste initialement vide)
   -----------------------------------------------------------------
*/
s_node * list_create(void) {
    return NULL;
}

/* -----------------------------------------------------------------
   Extrait le pointeur de donnée stocké dans un nœud
   -----------------------------------------------------------------
   node : pointeur vers le nœud à consulter
   -----------------------------------------------------------------
   retourne : le pointeur générique (void *) vers la donnée
   -----------------------------------------------------------------
*/
void * list_get_data(s_node * node) {
    return node->donnee;
}

/* -----------------------------------------------------------------
   Met à jour la donnée stockée dans un nœud existant
   -----------------------------------------------------------------
   node : pointeur vers le nœud à modifier
   data : pointeur vers la nouvelle donnée
   -----------------------------------------------------------------
*/
void list_set_data(s_node * node, void * data) {
    node->donnee = data;
}

/* -----------------------------------------------------------------
   Accède au nœud suivant dans la liste
   -----------------------------------------------------------------
   head : pointeur vers le nœud courant
   -----------------------------------------------------------------
   retourne : le pointeur vers le nœud suivant (ou NULL si fin de liste)
   -----------------------------------------------------------------
*/
s_node * list_next(s_node * head) {
    return head->next;
}

/* -----------------------------------------------------------------
   Crée un nœud et l'insère en tête de liste
   -----------------------------------------------------------------
   head : tête actuelle de la liste
   data : pointeur vers la donnée à stocker
   -----------------------------------------------------------------
   retourne : la nouvelle tête de liste
   -----------------------------------------------------------------
*/
s_node * list_insert(s_node * head, void * data) {
    s_node * new_node = malloc(sizeof(s_node));
    if (new_node == NULL) return head;

    new_node->donnee = data;
    new_node->next = head;

    return new_node;
}

/* -----------------------------------------------------------------
   Crée un nœud et l'ajoute à la toute fin (queue) de la liste
   -----------------------------------------------------------------
   head : tête de la liste
   data : pointeur vers la donnée à ajouter
   -----------------------------------------------------------------
   retourne : la tête de liste
   -----------------------------------------------------------------
*/
s_node * list_append(s_node * head, void * data) {
    s_node * new_node = malloc(sizeof(s_node));
    if (new_node == NULL) return head;

    new_node->donnee = data;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    }

    s_node * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;

    return head;
}

/* -----------------------------------------------------------------
   Supprime le premier nœud (la tête) de la liste
   -----------------------------------------------------------------
   head : pointeur vers la tête de liste actuelle
   -----------------------------------------------------------------
   retourne : la nouvelle tête de liste après suppression
   -----------------------------------------------------------------
*/
s_node * list_headRemove(s_node * head) {
    if (head == NULL) return NULL;

    s_node * next_node = head->next;
    free(head);
    return next_node;
}

/* -----------------------------------------------------------------
   Supprime la première instance d'une donnée spécifique dans la liste
   -----------------------------------------------------------------
   head : pointeur vers la tête de liste
   data : pointeur vers la donnée à rechercher et retirer
   -----------------------------------------------------------------
   retourne : la tête de liste (mise à jour si l'élément était en tête)
   -----------------------------------------------------------------
*/
s_node * list_remove(s_node * head, void * data) {
    if (head == NULL) return NULL;

    if (head->donnee == data) {
        return list_headRemove(head);
    }

    s_node * current = head;
    while (current->next != NULL && current->next->donnee != data) {
        current = current->next;
    }

    if (current->next != NULL) {
        s_node * temp = current->next;
        current->next = temp->next;
        free(temp);
    }

    return head;
}

/* -----------------------------------------------------------------
   Insère une donnée dans une liste ordonnée (sans doublon)
   -----------------------------------------------------------------
   head    : pointeur vers la tête de liste
   compare : fonction de comparaison renvoyant <0, 0 ou >0
   param   : donnée à insérer
   -----------------------------------------------------------------
   retourne : la tête de liste mise à jour
   -----------------------------------------------------------------
*/
s_node * list_orderedAppend(s_node * head, int (*compare)(s_node *, void *), void * param) {
    /* À implémenter */
    return head;
}