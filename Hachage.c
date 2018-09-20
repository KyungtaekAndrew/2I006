#include "Hachage.h"

double clef(double x, double y)
{
  double clef=y+(x+y)*(x+y+1)/2;
  return clef;
}

int fct_Hachage(double k, int M)
{
  double A=(sqrt(5)-1)/2;
  long h=(long)(M*(k*A-(long)(k*A)));
  return (int)h;
}


Noeud* rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x, double y)
{
  int hash=fct_Hachage(clef(x,y),H->taille);
  CellNoeud *cell=H->tab[hash];
  while(cell){
    if (cell->nd->x==x && cell->nd->y==y)
      return cell->nd;
    cell=cell->suiv;
  }
  Noeud *noeud=creer_Noeud(++R->nbNoeuds,x,y);
  CellNoeud *cellR=creer_CellNoeud(noeud);
  cellR->suiv=R->noeuds;
  R->noeuds=cellR;
  CellNoeud *cellH=creer_CellNoeud(noeud);
  cellH->suiv=H->tab[hash];
  H->tab[hash]=cellH;
  return cellH->nd;
}

Reseau* recreeReseauHachage(Chaines *C)
{
  if (!C) return NULL;
  int nbNoeuds=0;
  int gamma=C->gamma;
  Reseau *reseau;
  reseau=creer_Reseau(nbNoeuds,gamma);
  TableHachage *tabhash;
  tabhash=(TableHachage *)malloc(sizeof(TableHachage));
  tabhash->taille=100;
  tabhash->tab=(CellNoeud **)malloc(sizeof(CellNoeud *)*tabhash->taille);
  int k;
  for (k=0;k<tabhash->taille;k++) tabhash->tab[k]=NULL;
  CellChaine *cc;
  cc=C->chaines;
  int i=0,j=0;
  while (cc){
    i++;
    CellPoint *cp;
    cp=cc->points;
    Noeud *noeudextrA=NULL;
    Noeud *noeudextrB=NULL;
    Noeud *noeud=NULL;
    Noeud *noeudprec=NULL;
    while(cp){
      j++;
      noeudprec=noeud;
      noeud=rechercheCreeNoeudHachage(reseau,tabhash,cp->x,cp->y);
      if (noeudprec!=NULL){
	ajouterVoisin(noeudprec,noeud);
      }
      if (noeudextrA==NULL) noeudextrA=noeud;
      if (cp->suiv==NULL) noeudextrB=noeud;
      cp=cp->suiv;
    }
    ajouterCommodite(reseau,noeudextrA,noeudextrB);
    cc=cc->suiv;
  }
  return reseau;
}
