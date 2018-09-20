#include "Chaine.h"

#define STR_BUFFER_SIZE 256

CellPoint *creer_CellPoint(double x, double y)
{
  CellPoint *cellPoint = (CellPoint *)malloc(sizeof(CellPoint));
  if (!cellPoint) return NULL;
  cellPoint->x = x;
  cellPoint->y = y;
  cellPoint->suiv = NULL;
  return cellPoint;
}

CellChaine *creer_CellChaine(int numero)
{
  CellChaine *cellChaine = (CellChaine *)malloc(sizeof(CellChaine));
  if (!cellChaine) return NULL;
  cellChaine->numero = numero;
  cellChaine->points = NULL;
  cellChaine->suiv = NULL;
  return cellChaine;
}

Chaines *creer_Chaines(int nbChaines, int gamma)
{
  Chaines *chaine=(Chaines *)malloc(sizeof(Chaines));
  if (!chaine) return NULL;
  chaine->gamma=gamma;
  chaine->nbChaines=nbChaines;
  chaine->chaines=NULL;
  return chaine;
}

void ajouter_CellPoint(CellChaine *cc, CellPoint *cp)
{
  if (!cc->points){
    cc->points=cp;
    return;
  }
  /*
  CellPoint *temp;
  temp=cc->points;
  while (temp->suiv!=NULL)
    temp=temp->suiv;
  temp->suiv=cp;
  */
  cp->suiv=cc->points;
  cc->points=cp;
  return;
}

void ajouter_CellChaine(Chaines *c,CellChaine *cc)
{
  if (!c->chaines){
    c->chaines=cc;
    return;
  }
  /*
  CellChaine *temp;
  temp=c->chaines;
  while (temp->suiv!=NULL)
    temp=temp->suiv;
  temp->suiv=cc;
  */
  cc->suiv=c->chaines;
  c->chaines=cc;
  return;
}

int comptePoints(CellChaine *cc)
{
  CellPoint *cp;
  cp=cc->points;
  int cpt=0;
  while(cp){
    cpt++;
    cp=cp->suiv;
  }
  return cpt;
}

void calculeminmax(Chaines *C, double *minx, double *maxx, double *miny, double *maxy)
{
  double lminx, lminy, lmaxx, lmaxy;
  lminx=C->chaines->points->x;
  lmaxx=lminx;
  lminy=C->chaines->points->y;
  lmaxy=lminy;
  CellChaine *cc;
  cc=C->chaines;
  while(cc){
    CellPoint *cp;
      cp=cc->points;
      while(cp){
	if (cp->x<lminx) lminx=cp->x;
	if (cp->x>lmaxx) lmaxx=cp->x;
	if (cp->y<lminy) lminy=cp->y;
	if (cp->y>lmaxy) lmaxy=cp->y;
	cp=cp->suiv;
      }
      cc=cc->suiv;
  }
  *minx=lminx;
  *miny=lminy;
  *maxx=lmaxx;
  *maxy=lmaxy;
  return;
}

Chaines* lectureChaine(FILE *f)
{

  char temp[STR_BUFFER_SIZE];
  GetChaine(f, STR_BUFFER_SIZE, temp);
  int nbChain=GetEntier(f);
  SkipLine(f);
  
  GetChaine(f, STR_BUFFER_SIZE, temp);
  int Gamma=GetEntier(f);
  SkipLine(f);
  
  Chaines *chaine=creer_Chaines(nbChain,Gamma);

  int i, numero, nbPoints;
  double x, y;
  CellChaine *cellchaine;
  CellPoint *cellpoint;
  
  do{
    SkipLine(f);
    numero = GetEntier(f);
    cellchaine=creer_CellChaine(numero);
    Skip(f);
    nbPoints = GetEntier(f);
    for (i=0;i<nbPoints;i++){
      Skip(f);
      x=GetReel(f);
      Skip(f);
      y=GetReel(f);
      cellpoint=creer_CellPoint(x, y);
      ajouter_CellPoint(cellchaine,cellpoint);
    }
    ajouter_CellChaine(chaine,cellchaine);
  } while (numero<chaine->nbChaines-1);
  return chaine;
}

void ecrireChaineTxt(Chaines *c, FILE *f)
{
  fprintf(f,"NbChain: %i\n",c->nbChaines);
  fprintf(f,"Gamma: %i\n\n",c->gamma);

  CellChaine *cellchaine;
  cellchaine=c->chaines;
  CellPoint *cellpoint;
  
  while (cellchaine){
    fprintf(f,"%d ",cellchaine->numero);
    cellpoint=cellchaine->points;
    fprintf(f,"%d ",comptePoints(cellchaine));
    while (cellpoint){
      fprintf(f,"%.2f %.2f ",cellpoint->x,cellpoint->y);
      cellpoint=cellpoint->suiv;
    }
    cellchaine=cellchaine->suiv;
    fprintf(f,"\n");
  }
  return;
}

void afficheChaineSVG(Chaines *C, char* nomInstance)
{
  double minx,miny,maxx,maxy;
  calculeminmax(C,&minx,&maxx,&miny,&maxy);
  SVGwriter *svg=(SVGwriter *)malloc(sizeof(SVGwriter));
  SVGinit(svg,nomInstance,maxx-minx,maxy-miny);
  CellPoint *cp;
  CellChaine *cc;
  cc=C->chaines;
  while(cc){
    SVGlineRandColor(svg);
    SVGpointRandColor(svg);
    cp=cc->points;
    CellPoint *prec=NULL;
    while(cp){
      SVGpoint(svg,cp->x-minx,cp->y-miny);
      if (prec!=NULL)
	SVGline(svg,prec->x-minx,prec->y-miny,cp->x-minx,cp->y-miny);
      prec=cp;
      cp=cp->suiv;
    }
    cc=cc->suiv;
  }
  SVGfinalize(svg);
  free(svg);
  return;
}

double longueurChaine(CellChaine *c)
{
  double longueur=0;
  CellPoint *point;
  point=c->points;
  while (point->suiv){
    longueur+=sqrt(pow(point->suiv->x-point->x,2)+pow(point->suiv->y-point->y,2));
    point=point->suiv;
  }
  return longueur;
}

double longueurTotale(Chaines *C)
{
  double longueur=0;
  CellChaine *cc;
  cc=C->chaines;
  while(cc){
    longueur+=longueurChaine(cc);
    cc=cc->suiv;
  }
  return longueur;
}

int comptePointsTotal(Chaines *C)
{
  int cpt=0;
  CellChaine *cc;
  cc=C->chaines;
  while(cc){
    cpt+=comptePoints(cc);
    cc=cc->suiv;
  }
  return cpt;
}

void liberer_chaine(Chaines *chaine)
{
  CellPoint *cp,*cpprec;
  CellChaine *cc,*ccprec;
  cc=chaine->chaines;
  while (cc)
    {
      cp=cc->points;
      while(cp){
	cpprec=cp;
	cp=cp->suiv;
	free(cpprec);
      }
      ccprec=cc;
      cc=cc->suiv;
      free(ccprec);
    }
  free(chaine);
  return;
}
