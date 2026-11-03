#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

int main(void) {
    
    /* =================================================================
       SECTION 1 : TESTS DE list_create()
       ================================================================= */
    {
        s_node * l1 = list_create();
        assert(l1 == NULL);

        assert(check_list_state(l1, node_int_to_string, "null") == 1);

        assert(list_headRemove(l1) == NULL);
        assert(list_remove(l1, NULL) == NULL);
    }

    /* =================================================================
       SECTION 2 : TESTS DE list_insert()
       ================================================================= */
    {
        s_node * l1 = list_create();

        int val1 = 42;
        l1 = list_insert(l1, &val1);
        assert(l1 != NULL);
        assert(list_get_data(l1) == &val1);
        assert(list_next(l1) == NULL);
        assert(check_list_state(l1, node_int_to_string, "42 -> null") == 1);

        int val2 = 43;
        l1 = list_insert(l1, &val2);
        assert(list_get_data(l1) == &val2);
        assert(list_next(l1) != NULL);
        assert(list_get_data(list_next(l1)) == &val1);
        assert(check_list_state(l1, node_int_to_string, "43 -> 42 -> null") == 1);

        int val3 = 42;
        l1 = list_insert(l1, &val3);
        assert(check_list_state(l1, node_int_to_string, "42 -> 43 -> 42 -> null") == 1);

        s_node * l_null_test = list_create();
        l_null_test = list_insert(l_null_test, NULL);
        assert(l_null_test != NULL);
        assert(list_get_data(l_null_test) == NULL);
        free(l_null_test);
    }

    /* =================================================================
       SECTION 3 : TESTS DE list_append()
       ================================================================= */
    {
        s_node * list = list_create();
        int val1 = 10;
        
        s_node * new_head = list_append(list, &val1);
        assert(new_head != NULL);
        assert(list_get_data(new_head) == &val1);
        assert(list_next(new_head) == NULL);
        assert(check_list_state(new_head, node_int_to_string, "10 -> null") == 1);

        int val2 = 20;
        int val3 = 30;

        s_node * ret_head = list_append(new_head, &val2);
        assert(ret_head == new_head);
        assert(check_list_state(new_head, node_int_to_string, "10 -> 20 -> null") == 1);

        ret_head = list_append(new_head, &val3);
        assert(ret_head == new_head);
        assert(check_list_state(new_head, node_int_to_string, "10 -> 20 -> 30 -> null") == 1);

        int val_doublon = 10;
        list_append(new_head, &val_doublon);
        assert(check_list_state(new_head, node_int_to_string, "10 -> 20 -> 30 -> 10 -> null") == 1);

        int val_tete = 5;
        new_head = list_insert(new_head, &val_tete);
        assert(check_list_state(new_head, node_int_to_string, "5 -> 10 -> 20 -> 30 -> 10 -> null") == 1);

        int val_queue = 99;
        new_head = list_append(new_head, &val_queue);
        assert(check_list_state(new_head, node_int_to_string, "5 -> 10 -> 20 -> 30 -> 10 -> 99 -> null") == 1);
    }

    /* =================================================================
       SECTION 4 : TESTS DE list_set_data()
       ================================================================= */
    {
        int val_initiale = 100;
        s_node * list = list_create();
        list = list_insert(list, &val_initiale);

        assert(list_get_data(list) == &val_initiale);
        assert(check_list_state(list, node_int_to_string, "100 -> null") == 1);

        int val_nouvelle = 200;
        list_set_data(list, &val_nouvelle);

        assert(list_get_data(list) == &val_nouvelle);
        assert(check_list_state(list, node_int_to_string, "200 -> null") == 1);

        int v1 = 1, v2 = 2, v3 = 3;
        s_node * multi_list = list_create();
        multi_list = list_append(multi_list, &v1);
        multi_list = list_append(multi_list, &v2);
        multi_list = list_append(multi_list, &v3);

        int new_v1 = 10;
        list_set_data(multi_list, &new_v1);
        assert(check_list_state(multi_list, node_int_to_string, "10 -> 2 -> 3 -> null") == 1);

        s_node * node_milieu = list_next(multi_list);
        int new_v2 = 20;
        list_set_data(node_milieu, &new_v2);
        assert(check_list_state(multi_list, node_int_to_string, "10 -> 20 -> 3 -> null") == 1);

        s_node * node_queue = list_next(node_milieu);
        int new_v3 = 30;
        list_set_data(node_queue, &new_v3);
        assert(check_list_state(multi_list, node_int_to_string, "10 -> 20 -> 30 -> null") == 1);

        list_set_data(node_milieu, NULL);
        assert(list_get_data(node_milieu) == NULL);

        int val_a = 500, val_b = 600;
        list_set_data(list, &val_a);
        assert(list_get_data(list) == &val_a);
        list_set_data(list, &val_b);
        assert(list_get_data(list) == &val_b);
    }

    return 0;
}