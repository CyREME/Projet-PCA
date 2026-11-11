/* -------------------------------------------------------------------
   LACROIX & CELLIER
   -------------------------------------------------------------------
   Test unitaire du module de table de hashage - Fonctions utilitaires
   -------------------------------------------------------------------
   10/11/26 SR creation
  -------------------------------------------------------------------
*/


#ifndef STRHASH_H
#define STRHASH_H

#include "strhash.h"

/* ---------------------------------------------------------
   Structure d'une table de hachage
   ---------------------------------------------------------
*/

typedef struct {
   enum { WORD, SHORT_SPACE, SPACE, ERASE, INSERT, REPLACE, EMPTY} type;
   int textOffset;
   union {
    char * word;
    char space[4];
   } data;
}token;

// creation token
token * creation_token(int type, int textOffset);

// Ajout data token




// creation token



#endif