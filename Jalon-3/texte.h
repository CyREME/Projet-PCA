/* -------------------------------------------------------------------
   LACROIX & CELLIER
   -------------------------------------------------------------------
   Test unitaire du module de table de hashage - Fonctions utilitaires
   -------------------------------------------------------------------
   10/11/26 SR creation
   -------------------------------------------------------------------
*/


#ifndef TEXTE_H
#define TEXTE_H

#include "strhash.h"

/* ---------------------------------------------------------
   Structure d'un jeton
   ---------------------------------------------------------
*/

typedef struct {
   enum {WORD, SHORT_SPACE, SPACE, ERASE, INSERT, REPLACE, EMPTY} type;
   int textOffset;
   union {
      char * word;
      char space[4];
   } data;
}token;



/* ---------------------------------------------------------
   Structure d'un texte
   ---------------------------------------------------------
*/

typedef struct {
   token ** jetons;
   int cptJetons;
   int capacity;
}texte;




// creation token
token * creation_token(int type, int textOffset, char * str);

// Ajout data token




// creation token



#endif