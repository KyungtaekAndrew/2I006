#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include<stdlib.h>
#include<stdio.h>
#include "Struct_Liste.h"

typedef struct{
  int u,v;        /* Numeros des sommets extremité */
  double longueur;    /* longueur de l arete */

 /**************************************************/
 /* Emplacement des donnees utiles aux algorithmes */

  int calc_gamma; 

 /**************************************************/

} Arete;


typedef struct cellule_arete{
  Arete *a;     /* pointeur sur l'arete */
  struct cellule_arete *suiv;
} Cellule_arete;


typedef struct {
  int num;                 /* Numero du sommet (le meme que dans T_som) */
  double x, y;
  Cellule_arete* L_voisin;  /* Liste chainee des voisins */

 /**************************************************/
 /* Emplacement des donnees utiles aux algorithmes */

 

 /**************************************************/

} Sommet;


typedef struct{
  int e1,e2;    /* Les deux extremites de la commodite */
} Commod;


typedef struct{
  int nbsom;        /* Nombre de sommets */
  Sommet* *T_som;    /* Tableau de pointeurs sur sommets */
  int gamma;     

  int nbcommod;     /* Nombre de commodites */
  Commod *T_commod; /* Tableau des commodites */
} Graphe;


void ajout_voisin(Graphe* G, int u, int v);

/* retourne un pointeur sur l'arete uv si elle existe
   et NULL sinon */
Arete* acces_arete(Graphe* G, int u, int v);

void lecture_graphe(Graphe *G, FILE * f);

void affichageGrapheSVG(Graphe *G, char* nomInstance);





#endif
