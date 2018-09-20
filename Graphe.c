#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"Graphe.h"
#include"SVGwriter.h"
#include"entree_sortie.h"
#include"Struct_Liste.h"



void ajout_voisin(Graphe* G, int u, int v){
  Cellule_arete *pca;
  Arete *pa;

  pa=(Arete *) malloc(sizeof(Arete));
  pa->u=u;
  pa->v=v;
  pa->longueur=sqrt( (G->T_som[u]->x - G->T_som[v]->x)*(G->T_som[u]->x - G->T_som[v]->x) + (G->T_som[u]->y - G->T_som[v]->y)*(G->T_som[u]->y - G->T_som[v]->y));

  pca=(Cellule_arete*) malloc(sizeof(Cellule_arete));
  pca->a=pa;
  pca->suiv=G->T_som[u]->L_voisin;
  G->T_som[u]->L_voisin=pca;

  pca=(Cellule_arete*) malloc(sizeof(Cellule_arete));
  pca->a=pa;
  pca->suiv=G->T_som[v]->L_voisin;
  G->T_som[v]->L_voisin=pca;

}

Arete* acces_arete(Graphe* G, int u, int v){
  Cellule_arete *coura;

  coura=G->T_som[u]->L_voisin;
  while ( (coura!=NULL)&&(coura->a->u!=v)&&(coura->a->v!=v))
    coura=coura->suiv;

  if (coura==NULL) return NULL;
            else  return coura->a;
}

void lecture_graphe(Graphe *G, FILE * f){

  char temp[101];
  int nbarete;   /* stockage temporaire du nombre d aretes */
  int i;
  int num;       /* lecture dans le fichier d un numero */

 
  GetChaine(f,100,temp);
  G->nbsom=GetEntier(f);
  GetChaine(f,100,temp);
  nbarete=GetEntier(f);
  GetChaine(f,100,temp);
  G->nbcommod=GetEntier(f);
  GetChaine(f,100,temp);
  G->gamma=GetEntier(f);

  G->T_som=(Sommet**) malloc((G->nbsom+1)*sizeof(Sommet*));
  for (i=1;i<=G->nbsom;i++){
    G->T_som[i]=(Sommet*) malloc(sizeof(Sommet));
    G->T_som[i]->L_voisin=NULL;
  }

  G->T_commod=(Commod*)malloc(G->nbcommod*sizeof(Commod));

  for (i=0;i<G->nbsom;i++){
    GetChaine(f,100,temp);
    num=GetEntier(f);
    G->T_som[num]->num=num;
    G->T_som[num]->x=GetReel(f);
    G->T_som[num]->y=GetReel(f);
  }

  for (i=0;i<nbarete;i++){
    GetChaine(f,100,temp);
    ajout_voisin(G,GetEntier(f),GetEntier(f));
  }

  for (i=0;i<G->nbcommod;i++){
    GetChaine(f,100,temp);
    G->T_commod[i].e1=GetEntier(f);
    G->T_commod[i].e2=GetEntier(f);
  }

}


void afficheGrapheSVG(Graphe *G, char* nomInstance){

  SVGwriter svg;
  double maxx=0,maxy=0,minx=1e6,miny=1e6;
  int i;
  double xu,yu,xv,yv;
  Cellule_arete *coura;

  for(i=1;i<=G->nbsom;i++){
    if (maxx<G->T_som[i]->x) maxx=G->T_som[i]->x;
    if (maxy<G->T_som[i]->y) maxy=G->T_som[i]->y;
    if (minx>G->T_som[i]->x) minx=G->T_som[i]->x;
    if (miny>G->T_som[i]->y) miny=G->T_som[i]->y;
  }

  SVGinit(&svg,nomInstance,500,500);

  SVGpointColor(&svg, Red);
  SVGlineColor(&svg, Black);

  for(i=1;i<=G->nbsom;i++){

    xu=G->T_som[i]->x;
    yu=G->T_som[i]->y;
    
    printf("%d %d %f %f\n",i,G->T_som[i]->num,xu,yu);
    SVGpoint(&svg,500*(xu-minx)/(maxx-minx),500*(yu-miny)/(maxy-miny));

    coura=G->T_som[i]->L_voisin;
    while (coura!=NULL){

      if (coura->a->u==i){
	xv=G->T_som[coura->a->v]->x;
	yv=G->T_som[coura->a->v]->y;
      }
      else{
	xv=G->T_som[coura->a->u]->x;
	yv=G->T_som[coura->a->u]->y;
      }

      SVGline(&svg,500*(xu-minx)/(maxx-minx),500*(yu-miny)/(maxy-miny),500*(xv-minx)/(maxx-minx),500*(yv-miny)/(maxy-miny));
      
      coura=coura->suiv;
    }

  }

  SVGfinalize(&svg);

}


