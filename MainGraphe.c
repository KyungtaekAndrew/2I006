#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graphe.h"
#include "Struct_Liste.h"
#include "Struct_File.h"
#include "evaluation_NChaines.h"

void menu()
{
  printf("--- Menu ---\n");
  printf("1- Parcours en largeur\n");
  printf("2- Plus courts chemin : Algorithme de Dijkstra\n");
  printf("3- A vous de jouer!\n");
  printf("0- Quitter\n");
  printf("Que voulez-vous faire ?\n");
  return;
}

int main(int argc,char**argv)
{
  int chmeth;
  do {
    char filename[104],filenameres[104],filenamencha[104];;
    
    menu();
    scanf(" %d",&chmeth);
    if (chmeth==0 || chmeth>3) break;
    printf("Quel fichier voulez-vous traiter ?\n");
    scanf(" %s",filename);
    
    strcpy(filenameres,filename);
    strcat(filenameres,".res");
  
    FILE *fo=fopen(filenameres,"r");
  
    if (fo==NULL){
      printf("Probleme lecture du fichier %s\n",filenameres);
      exit(1);
    }
  
    Graphe G;
  
    lecture_graphe(&G,fo);
    fclose(fo);
    
    afficheGrapheSVG(&G,filename);
  
    ListeEntier **chaines;
    ListeEntier **chaines1,**chaines2,**newchaines=(ListeEntier **)malloc(sizeof(ListeEntier *)*G.nbcommod);
    int gamma,newgamma,oldgamma;
    int i, nbcommod=G.nbcommod;
    switch (chmeth)
      {
      case 1:
	chaines=chaines_commodites(&G);
	strcpy(filenamencha,filename);
	strcat(filenamencha,"_1.ncha");
	break;
      case 2:
	chaines=chaines_commodites_tas(&G);
	strcpy(filenamencha,filename);
	strcat(filenamencha,"_2.ncha");
	break;
      case 3:
	strcpy(filenamencha,filename);
	strcat(filenamencha,"_3.ncha");
	chaines1=chaines_commodites(&G);
	chaines2=chaines_commodites_tas(&G);
	for (i=0;i<nbcommod;i++)
	  newchaines[i]=chaines2[i];
	for (i=0;i<nbcommod;i++){
	  fo=fopen(filenameres,"r");
	  lecture_graphe(&G,fo);
	  fclose(fo);
	  oldgamma=calcule_gamma(&G,newchaines);
	  newchaines[i]=chaines1[i];
	  fo=fopen(filenameres,"r");
	  lecture_graphe(&G,fo);
	  fclose(fo);
	  newgamma=calcule_gamma(&G,newchaines);
	  if (newgamma>=oldgamma){
	    newchaines[i]=chaines2[i];
	  }
	}
	chaines=newchaines;
	break;
      case 0:
	return 0;
      }
    fo=fopen(filenameres,"r");
    lecture_graphe(&G,fo);
    fclose(fo);

    FILE *f=fopen(filenamencha,"w");
    ListeEntier liste;
    for (i=0;i<nbcommod;i++){
      liste=*chaines[i];
      while(liste!=NULL){
	fprintf(f,"%d ",liste->u);
	liste=liste->suiv;
      }
      fprintf(f,"-1\n");
    }
    double *longueur=(double *)malloc(sizeof(double));

    //printf("\nLongueur avec fct dans print: %lf\n",calcule_longueur(&G,chaines,longueur));
    double longueur1=calcule_longueur(&G,chaines,longueur);
    //printf("\nLongueur variable: %lf\n",longueur1);
    //printf("\nLongueur pointeur: %lf\n\n",*longueur);
    
    gamma=calcule_gamma(&G,chaines);

    printf("Methode = %d, Instance = %s, Evaluation = %f, gamma = %d, distance = %f\n",chmeth,filename,evaluation_NChaines(gamma,*longueur,filename),gamma,*longueur);
    
    fclose(f);
  } while (chmeth!=0);
  return 0;
}
