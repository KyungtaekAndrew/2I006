#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include <stdio.h>
#include <math.h>
#include "entree_sortie.h"
#include "SVGwriter.h"

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

/* Initialise et cree des CellPoint/CellChaine/Chaines */
CellPoint *creer_CellPoint(double x, double y);
CellChaine *creer_CellChaine(int numero);
Chaines *creer_Chaines(int nbChaines, int gamma);

/* Ajoute un CellPoint à la fin de la liste de points de la CellChaine */
void ajouter_CellPoint(CellChaine *cc, CellPoint *cp);

/* Ajoute une CellChaine à la fin de la liste de chaines de la Chaines */
void ajouter_CellChaine(Chaines *c,CellChaine *cc);

/* Compte le nombre de points d'une CellChaine */
/* Cette fonction sert principalement pour ecrireChaineTxt */
/* pour pouvoir écrire le nombre de points qui va suivre */
int comptePoints(CellChaine *cc);

/* Permet de récuperer le min et max de x et y */
void calculeminmax(Chaines *C, double *minx, double *maxx, double *miny, double *maxy);

/* Cree une Chaines depuis un fichier */
Chaines* lectureChaine(FILE *f);

/* Cree un fichier depuis une Chaines */
void ecrireChaineTxt(Chaines *C, FILE *f);

/* Cree un fichier SVG "nomInstance" depuis une Chaine */
void afficheChaineSVG(Chaines *C, char* nomInstance);

/* Calcule la longueur d'une CellChaine */
double longueurChaine(CellChaine *c);

/* Calcule la longueur totale d'une Chaines */
double longueurTotale(Chaines *C);

/* Compte le nombre de points d'une Chaines */
int comptePointsTotal(Chaines *C);

/* Libere la structure de Chaines */
void liberer_chaine(Chaines *chaine);

#endif	
