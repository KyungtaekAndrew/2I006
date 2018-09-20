#include "Reseau.h"

CellNoeud *creer_CellNoeud(Noeud *n)
{
  CellNoeud *cellnoeud;
  cellnoeud=(CellNoeud *)malloc(sizeof(CellNoeud));
  cellnoeud->nd=n;
  cellnoeud->suiv=NULL;
  return cellnoeud;
}

Noeud *creer_Noeud(int num, double x, double y)
{
  Noeud *noeud;
  noeud=(Noeud *)malloc(sizeof(Noeud));
  noeud->num=num;
  noeud->x=x;
  noeud->y=y;
  noeud->voisins=NULL;
  return noeud;
}

CellCommodite *creer_CellCommodite(Noeud *nA,Noeud *nB)
{
  CellCommodite *cc;
  cc=(CellCommodite *)malloc(sizeof(CellCommodite));
  cc->extrA=nA;
  cc->extrB=nB;
  cc->suiv=NULL;
  return cc;
}

Reseau *creer_Reseau(int nbN,int gamma)
{
  Reseau *r;
  r=(Reseau *)malloc(sizeof(Reseau));
  r->nbNoeuds=nbN;
  r->gamma=gamma;
  r->noeuds=NULL;
  r->commodites=NULL;
  return r;
}

void ajouterVoisin(Noeud *origine, Noeud *voisin)
{
  if (origine->voisins==NULL){
    CellNoeud *cnvoisin=creer_CellNoeud(voisin);
    cnvoisin->suiv=origine->voisins;
    origine->voisins=cnvoisin;
    
    CellNoeud *cnorigine=creer_CellNoeud(origine);
    cnorigine->suiv=voisin->voisins;
    voisin->voisins=cnorigine;
    return;
  }
  CellNoeud *temp=origine->voisins;
  while (temp->suiv!=NULL && (temp->nd->x!=voisin->x || temp->nd->y!=voisin->y)){
    temp=temp->suiv;
  }
  if (temp->nd->x==voisin->x && temp->nd->y==voisin->y) return;
  CellNoeud *cnvoisin=creer_CellNoeud(voisin);
  cnvoisin->suiv=origine->voisins;
  origine->voisins=cnvoisin;
  
  CellNoeud *cnorigine=creer_CellNoeud(origine);
  cnorigine->suiv=voisin->voisins;
  voisin->voisins=cnorigine;
  return;
}

void ajouterCommodite(Reseau *R, Noeud *nA, Noeud *nB)
{
  if (R->commodites==NULL){
    R->commodites=creer_CellCommodite(nA,nB);
    return;
  }
  CellCommodite *cc=creer_CellCommodite(nA,nB);
  cc->suiv=R->commodites;
  R->commodites=cc;
  return;
}

void calculeminmaxReseau(Reseau *R, double *minx, double *maxx, double *miny, double *maxy)
{
  double lminx, lminy, lmaxx, lmaxy;
  lminx=R->noeuds->nd->x;
  lmaxx=lminx;
  lminy=R->noeuds->nd->y;
  lmaxy=lminy;
  CellNoeud *cn;
  cn=R->noeuds->suiv;
  while(cn){
    if (cn->nd->x<lminx) lminx=cn->nd->x;
    if (cn->nd->x>lmaxx) lmaxx=cn->nd->x;
    if (cn->nd->y<lminy) lminy=cn->nd->y;
    if (cn->nd->y>lmaxy) lmaxy=cn->nd->y;
    cn=cn->suiv;
  }
  *minx=lminx;
  *miny=lminy;
  *maxx=lmaxx;
  *maxy=lmaxy;
  return;
}

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y)
{
  if (R->noeuds==NULL){
    Noeud *noeud;
    noeud=creer_Noeud(++R->nbNoeuds,x,y);
    R->noeuds=creer_CellNoeud(noeud);
    return noeud;
  }
  CellNoeud *cn;
  cn=R->noeuds;
  while(cn->suiv!=NULL && (cn->nd->x!=x || cn->nd->y!=y)){
    cn=cn->suiv;
  }
  if (cn->nd->x==x && cn->nd->y==y) return cn->nd;
  Noeud *nouv_noeud=creer_Noeud(++R->nbNoeuds,x,y);
  CellNoeud *nouv_cell=creer_CellNoeud(nouv_noeud);
  nouv_cell->suiv=R->noeuds;
  R->noeuds=nouv_cell;
  return nouv_noeud;
}

Reseau* reconstitueReseauListe(Chaines *C)
{
  if (!C) return NULL;
  int nbNoeuds=0;
  int gamma=C->gamma;
  Reseau *reseau;
  reseau=creer_Reseau(nbNoeuds,gamma);
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
      noeud=rechercheCreeNoeudListe(reseau,cp->x,cp->y);
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

void ecrireReseauTxt(Reseau *R, FILE *f)
{
  fprintf(f,"NbNoeuds: %d\n",R->nbNoeuds);
  fprintf(f,"NbLiaison: %d\n",nbLiaison(R));
  fprintf(f,"NbCommodite: %d\n",nbCommodite(R));
  fprintf(f,"Gamma: %d\n\n",R->gamma);

  CellNoeud *cn=R->noeuds;
  while (cn){
    fprintf(f,"v %d %f %f\n",cn->nd->num,cn->nd->x,cn->nd->y);
    cn=cn->suiv;
  }

  fprintf(f,"\n");
  cn=R->noeuds;
  while (cn){
    CellNoeud *voisin=cn->nd->voisins;
    while(voisin){
      if (voisin->nd->num<cn->nd->num)
	fprintf(f,"l %d %d\n",voisin->nd->num,cn->nd->num);
      voisin=voisin->suiv;
    }
    cn=cn->suiv;
  }

  fprintf(f,"\n");
  CellCommodite *cc=R->commodites;
  while (cc){
    fprintf(f,"k %d %d\n",cc->extrA->num,cc->extrB->num);
    cc=cc->suiv;
  }
  
  return;
}

int nbLiaison(Reseau *R)
{
  int nb=0;
  CellNoeud *cn=R->noeuds;
  while (cn){
    Noeud *n=cn->nd;
    CellNoeud *voisins=n->voisins;
    while (voisins){
      nb++;
      voisins=voisins->suiv;
    }
    cn=cn->suiv;
  }
  return nb/2;
}

int nbCommodite(Reseau *R)
{
  int nb=0;
  CellCommodite *cc=R->commodites;
  while (cc){
    nb++;
    cc=cc->suiv;
  }
  return nb;
}

void afficheReseauSVG(Reseau *R, char* nomInstance)
{
  double minx,miny,maxx,maxy;
  calculeminmaxReseau(R,&minx,&maxx,&miny,&maxy);
  SVGwriter *svg=(SVGwriter *)malloc(sizeof(SVGwriter));
  SVGinit(svg,nomInstance,maxx-minx,maxy-miny);
  
  CellNoeud *cn=R->noeuds;
  while (cn){
    SVGpointRandColor(svg);
    SVGpoint(svg,cn->nd->x-minx,cn->nd->y-miny);
    CellNoeud *voisin= cn->nd->voisins;
    while (voisin){
      SVGlineRandColor(svg);
      SVGline(svg,cn->nd->x-minx,cn->nd->y-miny,voisin->nd->x-minx,voisin->nd->y-miny);
      voisin=voisin->suiv;
    }
    cn=cn->suiv;
  }
  SVGfinalize(svg);
  free(svg);
  return;
}

void liberer_reseau(Reseau *reseau)
{
  CellNoeud *cn,*cnprec;
  cn=reseau->noeuds;
  while (cn){
    Noeud *n=cn->nd;
    free(n);
    cnprec=cn;
    cn=cn->suiv;
    free(cnprec);
  }
  
  CellCommodite *cc,*ccprec;
  cc=reseau->commodites;
  while (cc){
    ccprec=cc;
    cc=cc->suiv;
    free(ccprec);
  }
  
  free(reseau);
  return;
}
