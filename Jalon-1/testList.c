#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

int main(void) {
    
    /* =================================================================
       SECTION 1 : TESTS DE list_create()
       Objectif : Vérifier qu'une nouvelle liste est bien représentée par
       le pointeur NULL et que les utilitaires réagissent correctement.
       ================================================================= */
    
    // 1.1 : La création doit retourner NULL
    s_node * list = list_create();
    assert(list == NULL);

    // 1.2 : Formatage textuel d'une liste vide (doit afficher "null")
    assert(check_list_state(list, node_int_to_string, "null") == 1);

    // 1.3 : Sécurité des suppressions sur liste vide (ne doivent pas planter)
    assert(list_headRemove(list) == NULL);
    assert(list_remove(list, NULL) == NULL);
    


    /* =================================================================
       SECTION 2 : TESTS DE list_insert()
       Objectif : Valider l'insertion en TÊTE de liste (ordre LIFO) et
       s'assurer que les doublons sont autorisés.
       ================================================================= */
    
    list = list_create();

    // 2.1 : Premier élément inséré dans une liste vide
    int val1 = 42;
    list = list_insert(list, &val1);
    assert(list != NULL);
    assert(list_get_data(list) == &val1);
    assert(list_next(list) == NULL);
    assert(check_list_state(list, node_int_to_string, "42 -> null") == 1);

    // 2.2 : Empilement d'un second élément (devient la nouvelle tête)
    int val2 = 43;
    list = list_insert(list, &val2);
    assert(list_get_data(list) == &val2);
    assert(list_next(list) != NULL);
    assert(list_get_data(list_next(list)) == &val1);
    assert(check_list_state(list, node_int_to_string, "43 -> 42 -> null") == 1);

    // 2.3 : Insertion d'une valeur identique (doublon autorisé en tête)
    int val3 = 42;
    list = list_insert(list, &val3);
    assert(check_list_state(list, node_int_to_string, "42 -> 43 -> 42 -> null") == 1);

    // 2.4 : Insertion d'un pointeur générique NULL
    s_node * null_list = list_create();
    null_list = list_insert(null_list, NULL);
    assert(null_list != NULL);
    assert(list_get_data(null_list) == NULL);
    free(null_list); // Nettoyage local du nœud
    


    /* =================================================================
       SECTION 3 : TESTS DE list_append()
       Objectif : Valider l'ajout en QUEUE de liste (ordre FIFO) et
       s'assurer que la tête d'origine est bien conservée.
       ================================================================= */
    
    list = list_create();
    int v1 = 10;

    // 3.1 : Premier ajout en queue sur liste vide (crée la tête)
    s_node * head = list_append(list, &v1);
    assert(head != NULL);
    assert(list_get_data(head) == &v1);
    assert(list_next(head) == NULL);
    assert(check_list_state(head, node_int_to_string, "10 -> null") == 1);

    // 3.2 : Ajouts successifs en queue (la tête ne doit pas changer)
    int v2 = 20, v3 = 30;
    s_node * ret = list_append(head, &v2);
    assert(ret == head); // Le pointeur de tête reste le même
    assert(check_list_state(head, node_int_to_string, "10 -> 20 -> null") == 1);

    ret = list_append(head, &v3);
    assert(ret == head);
    assert(check_list_state(head, node_int_to_string, "10 -> 20 -> 30 -> null") == 1);

    // 3.3 : Ajout d'un doublon en queue (autorisé)
    int v_doublon = 10;
    list_append(head, &v_doublon);
    assert(check_list_state(head, node_int_to_string, "10 -> 20 -> 30 -> 10 -> null") == 1);
    


    /* =================================================================
       SECTION 4 : TESTS DE list_get_data() ET list_set_data()
       Objectif : Vérifier la lecture et la mise à jour sélective des
       données sans altérer les liens de la chaîne.
       ================================================================= */
    
    v1 = 1, v2 = 2, v3 = 3;
    list = list_create();
    list = list_append(list, &v1);
    list = list_append(list, &v2);
    list = list_append(list, &v3);

    // 4.1 : Lecture via list_get_data() sur chaque nœud
    assert(list_get_data(list) == &v1);
    assert(list_get_data(list_next(list)) == &v2);

    // 4.2 : Modification de la donnée du premier nœud (Tête)
    int new_v1 = 10;
    list_set_data(list, &new_v1);
    assert(list_get_data(list) == &new_v1);
    assert(check_list_state(list, node_int_to_string, "10 -> 2 -> 3 -> null") == 1);

    // 4.3 : Modification de la donnée du second nœud (Milieu)
    s_node * milieu = list_next(list);
    int new_v2 = 20;
    list_set_data(milieu, &new_v2);
    assert(check_list_state(list, node_int_to_string, "10 -> 20 -> 3 -> null") == 1);

    // 4.4 : Affectation d'un pointeur NULL comme donnée
    list_set_data(milieu, NULL);
    assert(list_get_data(milieu) == NULL);
    


    /* =================================================================
       SECTION 5 : TESTS DE list_headRemove()
       Objectif : Valider la suppression du premier nœud et la libération
       mémoire associée.
       ================================================================= */
    
    // 5.1 : Suppression sur liste à un seul élément -> devient NULL
    v1 = 100;
    s_node * single = list_create();
    single = list_insert(single, &v1);
    single = list_headRemove(single);
    assert(single == NULL);
    assert(check_list_state(single, node_int_to_string, "null") == 1);

    // 5.2 : Suppressions successives jusqu'à vider la liste
    int a = 1, b = 2, c = 3;
    list = list_create();
    list = list_append(list, &a);
    list = list_append(list, &b);
    list = list_append(list, &c); // "1 -> 2 -> 3 -> null"

    list = list_headRemove(list); // Supprime 1
    assert(check_list_state(list, node_int_to_string, "2 -> 3 -> null") == 1);

    list = list_headRemove(list); // Supprime 2
    assert(check_list_state(list, node_int_to_string, "3 -> null") == 1);

    list = list_headRemove(list); // Supprime 3
    assert(list == NULL);
    


    /* =================================================================
       SECTION 6 : TESTS DE list_remove()
       Objectif : Valider le retrait de la 1ère instance d'une donnée
       (en tête, au milieu, en queue, et cas des données absentes).
       ================================================================= */
    
    v1 = 10, v2 = 20, v3 = 30;
    list = list_create();
    list = list_append(list, &v1);
    list = list_append(list, &v2);
    list = list_append(list, &v3); // "10 -> 20 -> 30 -> null"

    // 6.1 : Suppression d'un élément situé au MILIEU
    list = list_remove(list, &v2);
    assert(check_list_state(list, node_int_to_string, "10 -> 30 -> null") == 1);

    // 6.2 : Suppression d'un élément situé en TÊTE
    list = list_remove(list, &v1);
    assert(check_list_state(list, node_int_to_string, "30 -> null") == 1);

    // 6.3 : Suppression d'un élément situé en QUEUE
    list = list_remove(list, &v3);
    assert(list == NULL);

    // 6.4 : Recherche d'une donnée ABSENTE (la liste reste inchangée)
    s_node * list2 = list_create();
    list2 = list_append(list2, &v1);
    int unknown = 999;
    ret = list_remove(list2, &unknown);
    assert(ret == list2);
    assert(check_list_state(list2, node_int_to_string, "10 -> null") == 1);

    // 6.5 : Cas des DOUBLONS (retire uniquement la première occurrence)
    int dup = 50;
    s_node * dup_list = list_create();
    dup_list = list_append(dup_list, &dup);
    dup_list = list_append(dup_list, &v1);
    dup_list = list_append(dup_list, &dup); // "50 -> 10 -> 50 -> null"

    dup_list = list_remove(dup_list, &dup);
    assert(check_list_state(dup_list, node_int_to_string, "10 -> 50 -> null") == 1);
    


    /* =================================================================
       SECTION 7 : TESTS DE list_orderedAppend()
       Objectif : Vérifier le tri automatique lors de l'insertion et
       le REJET STRICT des doublons[cite: 4].
       ================================================================= */
    
    s_node * ord_list = list_create();
    int v10 = 10, v20 = 20, v15 = 15, v5 = 5;

    // 7.1 : Premier élément dans liste vide
    list_orderedAppend(&ord_list, compare_int_node, &v10);
    assert(check_list_state(ord_list, node_int_to_string, "10 -> null") == 1);

    // 7.2 : Insertion en QUEUE (20 > 10)
    list_orderedAppend(&ord_list, compare_int_node, &v20);
    assert(check_list_state(ord_list, node_int_to_string, "10 -> 20 -> null") == 1);

    // 7.3 : Insertion au MILIEU (10 < 15 < 20)
    list_orderedAppend(&ord_list, compare_int_node, &v15);
    assert(check_list_state(ord_list, node_int_to_string, "10 -> 15 -> 20 -> null") == 1);

    // 7.4 : Insertion en TÊTE (5 < 10)
    list_orderedAppend(&ord_list, compare_int_node, &v5);
    assert(check_list_state(ord_list, node_int_to_string, "5 -> 10 -> 15 -> 20 -> null") == 1);

    // 7.5 : Tentative d'insertion d'un DOUBLON (doit être refusée)
    int v_dup = 15; // Déjà présent dans la liste
    list_orderedAppend(&ord_list, compare_int_node, &v_dup);
    // La liste doit être strictement identique à l'étape précédente
    assert(check_list_state(ord_list, node_int_to_string, "5 -> 10 -> 15 -> 20 -> null") == 1);
    


    /* =================================================================
       SECTION 8 : TESTS DE list_destroy()
       Objectif : Vérifier que la destruction libère l'intégralité des
       nœuds sans provoquer de comportement indéterminé.
       ================================================================= */
    
    // 8.1 : Destruction d'une liste vide
    s_node * empty = list_create();
    list_destroy(empty); // Ne doit pas planter

    // 8.2 : Destruction d'une liste peuplée
    a = 1, b = 2, c = 3;
    s_node * full_list = list_create();
    full_list = list_append(full_list, &a);
    full_list = list_append(full_list, &b);
    full_list = list_append(full_list, &c);

    list_destroy(full_list);

    return 0;
}