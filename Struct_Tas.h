#ifndef _STRUCT_TAS_H
#define _STRUCT_TAS_H

#include "Graphe.h"

typedef struct{
  int n;
  int *tab;
  int *M;
  double *f;
} Tas;

// Renvoie 0 s'il n'a pas de père (i=1) sinon renvoie le numero du pere de i
int pere(int i);
// Renvoie 0 s'il n'a pas de fils gauche sinon renvoie le numero du fils gauche de i
int filsGauche(Tas *t, int i);
// Renvoie 0 s'il n'a pas de fils droit sinon renvoie le numero du fils droit de i
int filsDroit(Tas *t, int i);
int plusPetitFils(Tas *t, int i);

void init_Tas(Tas *t,int N);
void echanger(Tas *t,int j,int k);
void monter(Tas *t,int j);
void descendre(Tas *t,int j);

//Acces au couple (f,i) de valeur f minimun:
//(f,i)=(t->f[t->tab[1]],t->tab[1])

void insert(Tas *t,double f,int i);

//Test de présence d'un élément:
//Si M[i]=0 -> élément absent
//Sinon élément présent

void supp(Tas *t,int i);

//Pour supprimer l'élément de plus petite valeur f du tas t:
//supp(t,t->tab[1]);

void maj_Tas(Tas *t,double f,int i);

#endif
  
