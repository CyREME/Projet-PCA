#include "texte.h";


// creation token
token * creation_token(int type, int textOffset, char * str) {
    token * t = malloc(sizeof(token));

    t->type = type;
    t->textOffset = textOffset;
    
    if (t->type == 1)
    {
        t->data.word = str;
    } else if(t->type == 2) {
        for(int i = 0; i < 4; i++) {
            if(str[i] == '0') {
                for (int j = 0; j < 4 - i; j++) {
                    t->data.space[i] = ' ';
                }
            } else {
                t->data.space[i] = str[i];
            }
        }
    }
    
    return t;

}


int textToToken(char texte[]) {
    int c=0;
    while (texte[c]!= '\0') {
        char * word;
        int wordC=0;
        int nbDelimiteur=0;
        while (texte[c] != '\n' || texte[c]!=' ' || texte[c]!= '\t' || texte[c]!= '\0') {
            word[wordC++]=texte[c++];

        }

        if (texte[c]=='\0') {
            return 0;
        }
        creation_token(1, c, word);
        char * spaces;
        spaces[nbDelimiteur]=texte[c];
        nbDelimiteur++;
        while (texte[c] == '\n' || texte[c]==' ' || texte[c]== '\t' || texte[c]!= '\0') {
            spaces[nbDelimiteur++]=texte[c++];
        }
        int type = 2;
        if (nbDelimiteur > 4) type=3;
        
        creation_token(type, c, spaces);
    }
