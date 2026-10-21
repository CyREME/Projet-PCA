/* ---------------------------------------------------------
   Test unitaire du module liste
	fonctions utilitaires
   ---------------------------------------------------------
   20/10/21	SR	creation
   ---------------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include "testListHelpers.h"

/* taille maximum de la chaine representant les valeurs dans la liste */
#define LIST_AS_A_STRING_MAX_SIZE 1024
/* taille maximum de la chaine representant la valeur d'un noeud de la liste */
#define NODE_AS_A_STRING_MAX_SIZE 100

/* -----------------------------------------------------------------
   Conversion d'un noeud pointant sur une donnée de type int
	en chaine de caracteres
   -----------------------------------------------------------------
   node		: pointeur sur le noeud à convertir
   buffer (PS) 	: tampon contenant la chaine obtenue
   size		: taille maximum de la chaine
   -----------------------------------------------------------------
   retourne 1 si la chaine converti est trop longue pour le tampon
	    0 sinon
   -----------------------------------------------------------------
*/
int node_int_to_string(s_node * node, char *buffer, int size) {
	int * value;
	int str_length;

	value=(int *)list_get_data(node);
	str_length=snprintf(buffer, size, "%d", *value);
	return (str_length >= size);  // voir man snprintf (return value)
}


/* -----------------------------------------------------------------
   Conversion des données d'une liste en chaine de caracteres
	Les donnéees sont separees par ->
   -----------------------------------------------------------------
   head		 : pointeur sur la tete de liste
   node_to_string: fonction pour convertir la valeur d'un noeud
   -----------------------------------------------------------------
   retourne  la chaine de caractères representant la liste
   -----------------------------------------------------------------
*/
char *  list_to_string (s_node * head,  
		       int (*node_to_string)(s_node * node, char * buffer, int buffer_size))  {

	static char list_as_a_string[LIST_AS_A_STRING_MAX_SIZE];
	static char buffer[NODE_AS_A_STRING_MAX_SIZE];
	int length = 0;

	int max_length = LIST_AS_A_STRING_MAX_SIZE - 5;	
		// 5 : reserve pour la fin de chaine (null ou ...)

	while( head && length<max_length-1 ) {
		int append;
	 	(void)(*node_to_string)(head, buffer, NODE_AS_A_STRING_MAX_SIZE-1);	

		append = snprintf( list_as_a_string+length , 
			            max_length - length, "%s", buffer); 
		if ( append >= max_length-length ) length = max_length-1;
		else			           length += append;	

		append = snprintf( list_as_a_string+length , 
			            max_length - length, " -> "); 
		if ( append >= max_length-length ) length = max_length-1;
		else			           length += append;	

		head=list_next(head);
	}
	if (length==max_length-1)
		sprintf( list_as_a_string+length , " ...");  
			// incomplet, tampon trop petit
	else
		sprintf( list_as_a_string+length , "null"); 
		
	return list_as_a_string;
}

/* -----------------------------------------------------------------
   Compare la chaine representant une liste a une chaine attendu 
   -----------------------------------------------------------------
   head		 : pointeur sur la tete de liste
   node_to_string: fonction pour convertir la valeur d'un noeud
   waited	 : chaine de caractère attendue
   -----------------------------------------------------------------
   retourne 1 si le résultat recu est celui attendu
            0 sinon
   -----------------------------------------------------------------
*/
int check_list_state(s_node * head,  int (*node_to_string)(s_node * node, char * buffer, int size),
		 const char * waited) {
	char * obtained=list_to_string(head, node_to_string);
	if ( strcmp(waited, obtained) != 0 ) {
		fprintf(stderr, "Attendu : %s \n Obtenu : %s\n", waited, obtained);
		return 0;
	}
	return 1;
}






















/* -----------------------------------------------------------------
   Création d'une nouvelle liste vide
   -----------------------------------------------------------------
   Aucun Paramètres
   -----------------------------------------------------------------
   retourne une liste vide
   -----------------------------------------------------------------
*/

s_node * list_create() {
	return NULL;
}



/* -----------------------------------------------------------------
   Création d'une nouvelle liste vide
   -----------------------------------------------------------------
   node : Une node
   -----------------------------------------------------------------
   retourne rien ( modifie uniquement le head)
   -----------------------------------------------------------------
*/
s_node * list_insert(s_node * head, void * data) {
	head->donnee = data;
	head->next = NULL;

	return head;
}

 
s_node * list_next(s_node * head) {
	head->next;
}

s_node * list_remove(s_node * head, void * data) {
	s_node * headIfNotFoundData = head;
	s_node * nodeActuelle=head;
	while (nodeActuelle->donnee != data || nodeActuelle->next == NULL) {
		s_node * pastNode=nodeActuelle;
		nodeActuelle=nodeActuelle->next;
	}

	if (nodeActuelle->donnee==data) {
		return list_HeadRemove(nodeActuelle);
	}
	return headIfNotFoundData;


}
s_node * list_headRemove(s_node * head) {
	head = head->next;
	return head;
}

void * list_get_data(s_node * node){
	return node->donnee;
}

s_node * list_remove(s_node * head, void * data) {
	s_node * nodeActuelle=head;
	s_node * pastNode;
	if (head->donnee==data) return list_headRemove(head);
	while (nodeActuelle->donnee != data || nodeActuelle->next != NULL) {
		pastNode=nodeActuelle;
		nodeActuelle=nodeActuelle->next;
	}

	if (nodeActuelle->donnee==data) {
		pastNode->next=headlist_HeadRemove(nodeActuelle);
	}
	return head;
}