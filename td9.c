#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graphe.h"
#include "Struct_Liste.h"
#include "Struct_File.h"
#include "evaluation_NChaines.h"

int main(int argc,char**argv){
  
  char filename[104],filenameres[104],filenamencha[104];;
  int chmeth;
  
  if(argc!=3){
    printf("usage: %s <file> <numeromethod>\n",argv[0]);
    printf("where numeromethode = 1 if using Width firs search\n");
    return 1;
  }
  
  chmeth=atoi(argv[2]);
  strcpy(filename,argv[1]);
  strcpy(filenameres,argv[1]);
  strcpy(filenamencha,argv[1]);
  strcat(filenameres,".res");
  strcat(filenamencha,".ncha");
  
  FILE *f=fopen(filenameres,"r");
  
  if (f==NULL){
    printf("Probleme lecture du fichier %s\n",filenameres);
    exit(1);
  }
  
  Graphe G;
  
  lecture_graphe(&G,f);

  fclose(f);
  
  afficheGrapheSVG(&G,filename);
  
  f=fopen(filenamencha,"w");

  int i, nbcommod=G.nbcommod;
  ListeEntier liste;
  ListeEntier** chaines1=chaines_commodites(&G);
  ListeEntier** chaines2=chaines_commodites_tas(&G);
  ListeEntier** newchaines=(ListeEntier **)malloc(sizeof(ListeEntier *)*nbcommod);

  for (i=0;i<nbcommod/2;i++){
    newchaines[2*i]=chaines1[2*i];
  }
  for (i=0;i<nbcommod/2;i++){
    newchaines[2*i+1]=chaines2[2*i+1];
  }

  int anciengamma,newgamma;
  /*
  for (i=0;i<nbcommod;i++){
    anciengamma=calcule_gamma(&G,newchaines);
    newchaines[i]=chaines2[i];
    newgamma=calcule_gamma(&G,newchaines);
    if (anciengamma<newgamma){
      newchaines[i]=chaines1[i];
    }
  }
  */
  
  for (i=0;i<nbcommod;i++){
    liste=*newchaines[i];
    while(liste!=NULL){
      fprintf(f,"%d ",liste->u);
      liste=liste->suiv;
    }
    fprintf(f,"-1\n");
    //fprintf(f,"-1 %d \n",len_chemin_avec_min_aretes(&G,G.T_commod[i].e1,G.T_commod[i].e2));
  }
  double *longueur=(double *)malloc(sizeof(double));

  //printf("\nLongueur avec fct dans print: %lf\n",calcule_longueur(&G,chaines,longueur));
  
  double longueur1=calcule_longueur(&G,newchaines,longueur);
  //printf("\nLongueur variable: %lf\n",longueur1);
  printf("\nLongueur pointeur: %lf\n\n",*longueur);
  
  //fprintf(f,"Longueur: %f\n",*longueur);
  
  int gamma=calcule_gamma(&G,newchaines);
  printf("Gamma = %d\n\n",gamma);
  //fprintf(f,"gamma: %d\n",gamma);
  printf("Evaluation = %f\n\n",evaluation_NChaines(gamma,*longueur,filename));
  
  fclose(f);
  
  return 0;
}
