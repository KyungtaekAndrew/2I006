#include "td7.h"

int len_chemin_avec_min_aretes(Graphe *G, int u, int v)
{
  Cellule_arete *cour;
  int u1,v1;
  int nbsom=G->nbsom+1; // +1 car la numérotation des sommets commence à 1
  int *visit=(int *)malloc(nbsom*sizeof(int));
  int i;
  S_file *F=(S_file *)malloc(sizeof(S_file));
  Init_file(F);
  
  for (i=0;i<nbsom;i++) visit[i]=-1;
  visit[u]=0;
  enfile(F,u);
  
  while (!(estFileVide(F))){
    u1=defile(F);
    cour=G->T_som[u1]->L_voisin;
    
    while (cour!=NULL){
      if (cour->a->u==u1){
	v1=cour->a->v;
      }
      else{
	v1=cour->a->u;
      }
      if (visit[v1]==-1){
	visit[v1]=visit[u1]+1;
	enfile(F,v1);
      }
      cour=cour->suiv;
    }
  }
  return visit[v];
}

ListeEntier* chemin_avec_min_aretes(Graphe *G, int u, int v)
{
  Cellule_arete *cour;
  int u1,v1;
  int nbsom=G->nbsom+1; // +1 car la numérotation des sommets commence à 1
  int *visit=(int *)malloc(nbsom*sizeof(int));
  int *pere=(int *)malloc(nbsom*sizeof(int));
  int i;
  S_file *F=(S_file *)malloc(sizeof(S_file));
  Init_file(F);
  ListeEntier *liste=(ListeEntier *)malloc(sizeof(ListeEntier));
  Init_Liste(liste);
  
  for (i=0;i<nbsom;i++){
    visit[i]=-1;
    pere[i]=-1;
  }
  visit[u]=0;
  enfile(F,u);
  
  while (!(estFileVide(F))){
    u1=defile(F);
    cour=G->T_som[u1]->L_voisin;
    
    while (cour!=NULL){
      if (cour->a->u==u1){
	v1=cour->a->v;
      }
      else{
	v1=cour->a->u;
      }
      if (visit[v1]==-1){
	visit[v1]=visit[u1]+1;
	enfile(F,v1);
	pere[v1]=u1;
      }
      cour=cour->suiv;
    }
  }
  
  v1=v;
  while (pere[v1]!=-1){
    ajoute_en_tete(liste,v1);
    v1=pere[v1];
  }
  ajoute_en_tete(liste,v1);
  return liste;
}

ListeEntier** chaines_commodites(Graphe *G)
{
  int i, nbcommod=G->nbcommod;
  ListeEntier** chaines=(ListeEntier **)malloc(sizeof(ListeEntier*)*nbcommod);
  for (i=0;i<nbcommod;i++){
    //chaines[i]=(ListeEntier*)malloc(sizeof(ListeEntier));
    chaines[i]=chemin_avec_min_aretes(G,G->T_commod[i].e1,G->T_commod[i].e2);
  }
  return chaines;
}

double longueur_arete(Graphe *G, int u, int v)
{
  Sommet *sommetu=G->T_som[u];
  Cellule_arete* voisin=sommetu->L_voisin;
  while (voisin!=NULL){
    if ( ((voisin->a->u==u) && (voisin->a->v==v)) || ((voisin->a->u==v) && (voisin->a->v==u)) ){
      //printf("u:%d v:%d longueur:%f\n",voisin->a->u,voisin->a->v,voisin->a->longueur);
      return voisin->a->longueur;
    }
    voisin=voisin->suiv;
  }
  return 0;
}

double calcule_longueur(Graphe *G,ListeEntier** chaines,double *pointeur)
{
  double longueur=0;
  ListeEntier liste;
  int i=0,nbcommod=G->nbcommod;
  for (i=0;i<nbcommod;i++){
    liste=*chaines[i];
    int u,v;
    u=liste->u;
    liste=liste->suiv;
    while (liste!=NULL){
      v=liste->u;
      //printf("u=%d & &=%d\n",u,v);
      longueur+=longueur_arete(G,u,v);
      u=v;
      liste=liste->suiv;
    }
  }
  *pointeur=longueur;
  //printf("\nJe suis dans la fonction %lf\n",longueur);
  return longueur;
}

int augmente_gamma(Graphe *G, int u, int v)
{
  Cellule_arete* voisin=G->T_som[u]->L_voisin;
  while (voisin!=NULL){
    if ( ((voisin->a->u==u) && (voisin->a->v==v)) || ((voisin->a->u==v) && (voisin->a->v==u)) ){
      voisin->a->calc_gamma++;
      return voisin->a->calc_gamma;
    }
    voisin=voisin->suiv;
  }
  return -1;
}

int calcule_gamma(Graphe *G, ListeEntier **chaines)
{
  int gamma=0;
  int current_gamma;
  ListeEntier liste;
  
  int i=0,nbcommod=G->nbcommod;
  for (i=0;i<nbcommod;i++){
    if (chaines[i]==NULL)
      break;
    liste=*chaines[i];
    int u,v;
    u=liste->u;
    liste=liste->suiv;
    while (liste!=NULL){
      v=liste->u;
      current_gamma=augmente_gamma(G,u,v);
      if (current_gamma>gamma){
	//printf("%d %d\n",u,v);
	gamma=current_gamma;
      }
      u=v;
      liste=liste->suiv;
    }
  }
  
  //printf("Salut fct: %d\n",gamma);
  return gamma;
}
