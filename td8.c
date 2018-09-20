#include "td8.h"

ListeEntier* algo_Dijkstra(Graphe *g, int u, int v)
{
  int i,s,taille=g->nbsom+1,numvoisin;
  double *lambda=(double *)malloc(taille*sizeof(double));
  int *pred=(int *)malloc(taille*sizeof(int));
  int *marque=(int *)malloc(taille*sizeof(int));
  for (i=0;i<taille;i++){
    lambda[i]=1000000000;
    pred[i]=-1;
    marque[i]=0;
  }
  Tas *bordure=(Tas *)malloc(sizeof(Tas));
  init_Tas(bordure,taille);
  insert(bordure,0,u);
  lambda[u]=0;
  while (bordure->n!=0){
    s=bordure->tab[1];
    supp(bordure,bordure->tab[1]);
    marque[s]=1;
    Cellule_arete *voisin=g->T_som[s]->L_voisin;
    while (voisin!=NULL){
      if (voisin->a->u==s)
	numvoisin=voisin->a->v;
      else
	numvoisin=voisin->a->u;
      //printf("Je suis avant la boucle if s:%d,u:%d,marque:%d,%f,%f,%f\n",s,numvoisin,marque[numvoisin],lambda[numvoisin],lambda[s],longueur_arete(g,numvoisin,s));
      if ((marque[numvoisin]==0) && (lambda[numvoisin]>(lambda[s]+longueur_arete(g,numvoisin,s)))){
	lambda[numvoisin]=lambda[s]+longueur_arete(g,numvoisin,s);
	pred[numvoisin]=s;
	maj_Tas(bordure,lambda[numvoisin],numvoisin);
      }
      voisin=voisin->suiv;
    }
  }

  ListeEntier *liste=(ListeEntier *)malloc(sizeof(ListeEntier));
  Init_Liste(liste);
  int v1=v;
  while (pred[v1]!=-1){
    ajoute_en_tete(liste,v1);
    v1=pred[v1];
  }
  ajoute_en_tete(liste,v1);
  return liste;
}

ListeEntier** chaines_commodites_tas(Graphe *G)
{
  int i, nbcommod=G->nbcommod;
  ListeEntier** chaines=(ListeEntier **)malloc(sizeof(ListeEntier*)*nbcommod);
  for (i=0;i<nbcommod;i++){
    //chaines[i]=(ListeEntier*)malloc(sizeof(ListeEntier));
    chaines[i]=algo_Dijkstra(G,G->T_commod[i].e1,G->T_commod[i].e2);
  }
  return chaines;
}
