#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include <math.h>
#include "Reseau.h"

typedef struct tablehachage{
  int taille;
  CellNoeud **tab;  
} TableHachage;

double clef(double x, double y);
int fct_Hachage(double k, int M);

Noeud* rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x, double y);
Reseau* recreeReseauHachage(Chaines *C);

#endif
