#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

int main(void) {

    // Tests pout list_create
    /* -----------------------------------------------------------------
       TEST 1 : Vérification de la valeur de retour brute
       Une liste créée doit retourner strictement un pointeur NULL.
       ----------------------------------------------------------------- */
    s_node * l1 = list_create();
    assert(l1 == NULL);

    /* -----------------------------------------------------------------
       TEST 2 : Vérification du comportement avec list_to_string
       La représentation textuelle d'une liste vide doit être "null".
       ----------------------------------------------------------------- */
    char * str_representation = list_to_string(l1, node_int_to_string);
    assert(str_representation != NULL);
    assert(strcmp(str_representation, "null") == 0);

    /* -----------------------------------------------------------------
       TEST 3 : Utilisation du helper check_list_state
       Vérification directe que l'état correspond exactement à "null".
       ----------------------------------------------------------------- */
    int is_valid_state = check_list_state(l1, node_int_to_string, "null");
    assert(is_valid_state == 1);

    /* -----------------------------------------------------------------
       TEST 4 : Créations multiples et indépendance
       Vérifier qu'appeler list_create() plusieurs fois de suite
       produit toujours des listes vides sans effets de bord.
       ----------------------------------------------------------------- */
    s_node * l2 = list_create();
    s_node * l3 = list_create();
    assert(l2 == NULL);
    assert(l3 == NULL);
    assert(l1 == l2 && l2 == l3); // Toutes pointent de manière cohérente vers NULL

    /* -----------------------------------------------------------------
       TEST 5 : Comportement des fonctions de suppression sur liste vide
       Sur une liste vide, les fonctions de suppression doivent être sûres
       et retourner NULL sans planter.
       ----------------------------------------------------------------- */
    assert(list_headRemove(l1) == NULL);
    assert(list_remove(l1, NULL) == NULL);

    printf("✅ Tous les tests de list_create() ont réussi avec succès !\n");
    return 0;
}