/* ---------------------------------------------------------
   Test unitaire du module liste
	fonctions utilitaires
   ---------------------------------------------------------
   20/10/21	SR	creation
   ---------------------------------------------------------
*/

struct _list_node {
  void * donnee;
   struct _list_node * next;
};

typedef struct _list_node s_node;


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
int node_int_to_string(s_node * node,
		       char *buffer, 
		       int size);


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
		        int (*node_to_string)(s_node * node, char * buffer, 
			int buffer_size));

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
int check_list_state (s_node * head,  
		      int (*node_to_string)(s_node * node, char * buffer, int size),
		      const char * waited);






























/* -----------------------------------------------------------------
   Création d'une nouvelle liste vide
   -----------------------------------------------------------------
   Aucun Paramètres
   -----------------------------------------------------------------
   retourne une liste vide
   -----------------------------------------------------------------
*/
s_node * list_create(void);


/* -----------------------------------------------------------------
   Création d'une nouvelle liste vide
   -----------------------------------------------------------------
   node : Une node
   -----------------------------------------------------------------
   retourne un ointeur vers une donnée
   -----------------------------------------------------------------
*/
void * list_get_data(void s_node * node);


/* -----------------------------------------------------------------
   Création d'une nouvelle liste vide
   -----------------------------------------------------------------
   node : Une node
   -----------------------------------------------------------------
   retourne un ointeur vers une donnée
   -----------------------------------------------------------------
*/
void * list_set_data(void s_node * node);


/* -----------------------------------------------------------------
   Création d'une nouvelle liste vide
   -----------------------------------------------------------------
   node : Une node
   -----------------------------------------------------------------
   retourne un ointeur vers une donnée
   -----------------------------------------------------------------
*/
s_node * list_insert(s_node * head, void * data);