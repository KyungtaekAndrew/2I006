#ifndef __RESEAU_H__
#define __RESEAU_H__

#include "Chaine.h"

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
}; /* Noeud */

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

CellNoeud *creer_CellNoeud(Noeud *n);
Noeud *creer_Noeud(int num, double x, double y);
CellCommodite *creer_CellCommodite(Noeud *nA,Noeud *nB);
Reseau *creer_Reseau(int nbN,int gamma);
void ajouterVoisin(Noeud *origine, Noeud *voisin);
void ajouterCommodite(Reseau *R, Noeud *nA, Noeud *nB);
void calculeminmaxReseau(Reseau *R, double *minx, double *maxx, double *miny, double *maxy);

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
void ecrireReseauTxt(Reseau *R, FILE *f);
int nbLiaison(Reseau *R);
int nbCommodite(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);

void liberer_reseau(Reseau *reseau);

#endif
