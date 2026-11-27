/* -------------------------------------------------------------------
   LACROIX & CELLIER
   -------------------------------------------------------------------
   Module de gestion et d'analyse des textes - Fichier d'en-tête
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




// Création d'un jeton
token * creation_token(int type, int textOffset, char * str);

// Création d'une structure texte vide
texte * creation_texte();

// Analyse du buffer pour découper en jetons
int textToToken(table_hash * tableHash, texte * txt, char * buffer);

// Ajout d'un jeton dans le tableau dynamique du texte
int addTokken(texte * t, token * tk);

// Chargement d'un fichier complet dans une chaîne char *
char * charger_fichier(const char * nomFichier);

// Libération complète de la mémoire d'un texte et de ses jetons
void liberer_texte(texte * t);
#endif