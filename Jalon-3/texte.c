#include <stdlib.h>
#include "texte.h"


// creation token
token * creation_token(int type, int textOffset, char * str) {
    token * t = malloc(sizeof(token));
    if (t == NULL) return NULL;


    t->type = type;
    t->textOffset = textOffset;
    
    if (t->type == WORD)
    {
        // On passe un pointeur vers le mot dans la table de Hashage dans word
        t->data.word = str;
    } else if(t->type == SHORT_SPACE) {
        

        // Ajout de chaque caractère présent dans la chaine vers le délimiteur < 4
        int i = 0;
        while (i < 4 && str[i] != '\0') {
            t->data.space[i] = str[i];
            i++;
        }
        // Ajout d'une fin au bout d'une chaine de caractère
        if (i < 4) {
            t->data.space[i] = '\0';
        }

        // Dans le cas d'un SPACE on ne fait rien et data sera à NULL

    }
    
    return t;

}


int textToToken(table_hash * tableHash, texte * txt, char * buffer) {

    int c=0;
    while (buffer[c] != '\0') {
        char tempWord[512]; // Mot a insérer dans la table, et dans un token.
        int wordC=0; // Taille du mot
        int nbDelimiteur=0;
        while (buffer[c] != '\n' && buffer[c] != ' ' && buffer[c] != '\t' && buffer[c] != '\0') {
            tempWord[wordC++]=buffer[c++];
        }

        if(wordC > 0) {
            
            char * word = malloc((wordC + 1) * sizeof(char));
            
            for (int i = 0; i < wordC; i++){
                word[i]=tempWord[i];
            }
            
            word[wordC] = '\0';
            
            tableAppendWord(tableHash, word);
            char * new_word = tableGetWord(tableHash, word);
            token * tk = creation_token(WORD, c-wordC, new_word);
            addTokken(txt, tk);

            free(word);
            
            if (buffer[c]=='\0') {
                return 1;
            }
        }

        char tempSpaces[512];
        while ((buffer[c] == '\n' || buffer[c] == ' ' || buffer[c] == '\t') && buffer[c] != '\0') {
            tempSpaces[nbDelimiteur++]=buffer[c++];

        }
        tempSpaces[nbDelimiteur]='\0';
        if (nbDelimiteur > 0) {
            int type = SHORT_SPACE;
            if (nbDelimiteur > 4) type=SPACE;
            
            token * tk = creation_token(type, c-nbDelimiteur, tempSpaces);
            addTokken(txt, tk);
        }

        if (buffer[c]=='\0') {
                return 1;
        }
    }
    return 0;
}



texte * creation_texte() {
    texte * t = malloc(sizeof(texte));
    if (t == NULL) return NULL;

    t->cptJetons = 0;
    t->capacity = 50;
    
    token ** tk = malloc(t->capacity * sizeof(token *));
    if (tk == NULL) return NULL;
    t->jetons = tk;

    return t;
}



int addTokken(texte * t, token * tk) {

    if (t->cptJetons == t->capacity) {
        t->capacity += 50;
        token ** ntk = realloc(t->jetons, t->capacity * sizeof(token *));
        if (ntk == NULL) return 0;
        t->jetons = ntk;
    }

    t->jetons[t->cptJetons++] = tk;

    return 1;
}


char * charger_fichier(const char * nomFichier) {
    FILE * f = fopen(nomFichier, "r");
    if (f == NULL) return NULL; // Échec d'ouverture 🛡️

    // 1. Calcul de la taille du fichier
    fseek(f, 0, SEEK_END);
    long taille = ftell(f);
    fseek(f, 0, SEEK_SET);

    // 2. Allocation du tampon (taille + 1 pour le '\0')
    char * buffer = malloc(taille + 1);
    if (buffer == NULL) {
        fclose(f);
        return NULL;
    }

    // 3. Lecture du fichier et ajout du nul final
    size_t lu = fread(buffer, 1, taille, f);
    buffer[lu] = '\0'; // 🛑 Indispensable pour marquer la fin de la chaîne

    fclose(f);
    return buffer;
}

void liberer_texte(texte * t) {
    if (t == NULL) return;

    int i = 0;
    while(i < t->cptJetons) {
        free(t->jetons[i]);
        i++;
    }
    free(t->jetons);
    free(t);
}