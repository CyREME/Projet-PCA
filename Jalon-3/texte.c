#include "texte.h";


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


int textToToken(table_hash * tableHash, char * buffer) {

    int c=0;
    while (buffer[c] != '/0') {
        char * word = malloc(sizeof(char)); // Mot a insérer dans la table, et dans un token.
        int wordC=0; // Taille du mot
        int nbDelimiteur=0;
        while ((buffer[c] != '\n' && buffer[c] != ' ' && c != '\t') && buffer[c] != EOF) {
            word[wordC++]=buffer[c++];
        }

        if (buffer[c]=='\0') {
            return 0;
        }
    
        tableAppendWord(tableHash, word);
        creation_token(1, c-wordC, word);

        char * spaces = malloc(sizeof(char));
        spaces[nbDelimiteur++]=buffer[c];
        while ((buffer[c] == '\n' && buffer[c]==' ' && buffer[c]== '\t')  && c != '\0') {
            spaces[nbDelimiteur++]=buffer[c++];

        }
        spaces[nbDelimiteur]='\0';
        int type = SHORT_SPACE;
        if (nbDelimiteur > 4) type=SPACE;
        
        creation_token(type, c-nbDelimiteur-1, spaces);
    }
    return 1;
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


// A revoir plus tard
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