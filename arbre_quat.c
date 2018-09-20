#include "arbre_quat.h"

void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax)
{
  double minx, miny, maxx, maxy;
  minx=C->chaines->points->x;
  maxx=minx;
  miny=C->chaines->points->y;
  maxy=miny;
  CellChaine *cc;
  cc=C->chaines;
  while(cc){
    CellPoint *cp;
    cp=cc->points;
    while(cp){
      if (cp->x<minx) minx=cp->x;
      if (cp->x>maxx) maxx=cp->x;
      if (cp->y<miny) miny=cp->y;
      if (cp->y>maxy) maxy=cp->y;
      cp=cp->suiv;
    }
    cc=cc->suiv;
  }
  *xmin=minx;
  *ymin=miny;
  *xmax=maxx;
  *ymax=maxy;
  return;
}

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY)
{
  ArbreQuat *arbre;
  arbre=(ArbreQuat *)malloc(sizeof(ArbreQuat));
  arbre->xc=xc;
  arbre->yc=yc;
  arbre->coteX=coteX;
  arbre->coteY=coteY;
  arbre->noeud=creer_Noeud(1, xc, yc);
  arbre->so=NULL;
  arbre->se=NULL;
  arbre->no=NULL;
  arbre->ne=NULL;
  return arbre;
}

ArbreQuat* insererNoeudArbre(Noeud* n, ArbreQuat* a, ArbreQuat* parent)
{
  if (a==NULL){
    a=creerArbreQuat(n->x,n->y,parent->coteX/2,parent->coteY/2);
    a->noeud=n;
    if (a->noeud->x<parent->xc){
      if (a->noeud->y<parent->yc){
	parent->so=a;
      }
      else {
	parent->no=a;
      }
    }
    else {
      if (a->noeud->y<parent->yc){
	parent->se=a;
      }
      else {
	parent->ne=a;
      }
    }
    return a;
  }
  if (a->noeud!=NULL){
    if (n->x<a->noeud->x){
      if (n->y<a->noeud->y){
	a->so=insererNoeudArbre(n,a->so,a);
	a->ne=insererNoeudArbre(a->noeud,a->ne,a);
	a->noeud=NULL;
	a->xc=(a->so->noeud->x+a->ne->noeud->x)/2;
	a->yc=(a->so->noeud->y+a->ne->noeud->y)/2;
	return a;
      }
      else {
	a->no=insererNoeudArbre(n,a->no,a);
	a->se=insererNoeudArbre(a->noeud,a->se,a);
	a->noeud=NULL;
	a->xc=(a->no->noeud->x+a->se->noeud->x)/2;
	a->yc=(a->no->noeud->y+a->se->noeud->y)/2;
	return a;
      }
    }
    else {
      if (n->y<a->noeud->y){
	a->se=insererNoeudArbre(n,a->se,a);
	a->no=insererNoeudArbre(a->noeud,a->no,a);
	a->noeud=NULL;
	a->xc=(a->se->noeud->x+a->no->noeud->x)/2;
	a->yc=(a->se->noeud->y+a->no->noeud->y)/2;
	return a;
      }
      else {
	a->ne=insererNoeudArbre(n,a->ne,a);
	a->so=insererNoeudArbre(a->noeud,a->so,a);
	a->noeud=NULL;
	a->xc=(a->so->noeud->x+a->ne->noeud->x)/2;
	a->yc=(a->so->noeud->y+a->ne->noeud->y)/2;
	return a;
      }
    }
  }
  else {
    printf("Je passe jamais ici %f %f\n",n->x,n->y);
    if (n->x<a->xc){
      if (n->y<a->yc){
	return insererNoeudArbre(n,a->so,a);
      }
      else {
	return insererNoeudArbre(n,a->no,a);
      }
    }
    else {
      if (n->y<a->yc){
	return insererNoeudArbre(n,a->se,a);
      }
      else {
	return insererNoeudArbre(n,a->ne,a);
      }
    }
  }
  printf("Erreur lors de l'insertion!!!!!!!!!!!!!!!!!!!!!!\n");
  return NULL;
}

Noeud* chercherNoeudArbre(CellPoint* pt, Reseau* R, ArbreQuat** aptr, ArbreQuat* parent)
{
  if (*aptr==NULL){
    Noeud *noeud=creer_Noeud(++R->nbNoeuds,pt->x,pt->y);
    *aptr=insererNoeudArbre(noeud,*aptr,parent);
    CellNoeud *cn=creer_CellNoeud(noeud);
    cn->suiv=R->noeuds;
    R->noeuds=cn;
    return noeud;
  }
  if ((*aptr)->noeud!=NULL){
    if ((*aptr)->noeud->x==pt->x && (*aptr)->noeud->y==pt->y){
      return (*aptr)->noeud;
    }
    Noeud *noeud=creer_Noeud(++R->nbNoeuds,pt->x,pt->y);
    *aptr=insererNoeudArbre(noeud,*aptr,parent);
    CellNoeud *cn=creer_CellNoeud(noeud);
    cn->suiv=R->noeuds;
    R->noeuds=cn;
    return noeud;
  }
  else {
    if (pt->x<(*aptr)->xc){
      if (pt->y<(*aptr)->yc){
	return chercherNoeudArbre(pt,R,&((*aptr)->so),*aptr);
      }
      else {
	return chercherNoeudArbre(pt,R,&((*aptr)->no),*aptr);
      }
    }
    else {
      if (pt->y<(*aptr)->yc){
	return chercherNoeudArbre(pt,R,&((*aptr)->se),*aptr);
      }
      else {
	return chercherNoeudArbre(pt,R,&((*aptr)->ne),*aptr);
      }
    }
  }
  printf("Erreur lors de la recherche!!!!!!!!!!!!!!!!!!!!!!\n");
  return NULL;
}

Reseau* recreeReseauArbre(Chaines* C)
{
  if (!C) return NULL;
  int nbNoeuds=0;
  int gamma=C->gamma;
  Reseau *reseau;
  reseau=creer_Reseau(nbNoeuds,gamma);
  CellChaine *cc;
  cc=C->chaines;
  int i=0,j=0;
  double xmin,ymin,xmax,ymax;
  chaineCoordMinMax(C,&xmin,&ymin,&xmax,&ymax);
  ArbreQuat *parent=creerArbreQuat((xmin+xmax)/2,(ymin+ymax)/2,(xmax-xmin),(ymax-ymin));
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
      noeud=chercherNoeudArbre(cp,reseau,&parent,parent);
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
