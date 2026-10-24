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



    // tests list_insert
    /* -----------------------------------------------------------------
       TEST 1 : Insertion d'un élément dans une liste vide
       S'assurer que l'insertion dans une liste vide retourne une nouvelle tête non NULL.
      ----------------------------------------------------------------- */
      assert(list_insert(l1, (void *)42) != NULL);
      assert(list_insert(l1, (void *)42)->donnee == (void *)42);
      l1 = list_insert(l1, (void *)42); // Mettre à jour l1 pour refléter la nouvelle tête
   
   /* -----------------------------------------------------------------
      TEST 2 : Insertion d'un élément dans une liste non vide
      Vérifier que l'insertion d'un nouvel élément dans une liste existante
      met correctement à jour la tête de liste et que l'élément est bien inséré
      ----------------------------------------------------------------- */
      assert(list_insert(l1, (void *)43) != NULL);
      assert(list_insert(l1, (void *)43)->donnee == (void *)43);
      assert(list_insert(l1, (void *)43)->next->donnee == (void *)42);



    return 0;
}