#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*LIT LE PROCHAIN CARACTERE NON VIDE */
char ReadChar(FILE *f);
 
/* SAUT DES ESPACES LORS DE LA LECTURE DANS UN FICHIER POINTE PAR f */
void Skip(FILE *f); 

/* LECTURE DES CARACTERES JUSQU'A LA FIN DU FICHIER OU DE LA LIGNE */
void SkipLine(FILE *f); 
 
/* LECTURE DE CHAINE DE CARACTERES JUSQU'A UN ESPACE, LA FIN DE LA LIGNE 
OU LA FIN DE FICHIER ; taille_max est la taille maximale de la chaine
de caractere contenu dans le fichier */
void GetChaine(FILE *f,int taille_max, char *s);

/* LECTURE ET TRANSFORMATION DE CARACTERES EN ENTIERS */
int GetEntier(FILE *f);

/* LECTURE ET TRANSFORMATION DE CARACTERES EN ENTIERS REELS */
double GetReel(FILE *f);

