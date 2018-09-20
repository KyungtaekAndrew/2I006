#include "Reseau.h"
#include "Hachage.h"
#include "arbre_quat.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

void menu()
{
  printf("--- Menu ---\n");
  printf("1- Construire le reseau avec liste\n");
  printf("2- Construire le reseau avec la table de hachage\n");
  printf("3- Construire le reseau avec l'arbre quaternaire\n");
  printf("4- Construire le reseau avec les 3 structures\n");
  printf("5- Obtenir temps de calcul\n");
  printf("6- Construire le reseau avec le 3 structures & temps de calcul\n");
  printf("0- Quitter\n");
  printf("Que voulez-vous faire ?\n");
  return;
}

int main()
{
  int ch;
  do {
    char nomfic[256];
    menu();
    scanf(" %d",&ch);
    if (ch==0) break;
    printf("Quel fichier voulez-vous construire ?\n");
    scanf(" %s",nomfic);
    FILE *f=fopen(nomfic,"r");
    Chaines *c;
    c=lectureChaine(f);
    fclose(f);
    Reseau *r;
    switch (ch)
      {
      case 1: ;
	r=reconstitueReseauListe(c);
	f=fopen("ReseauListe.txt","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"ReseauListe_graphe");
	liberer_reseau(r);
	break;
      case 2: ;
	r=recreeReseauHachage(c);
	f=fopen("ReseauHachage.txt","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"ReseauHachage_graphe");
	liberer_reseau(r);
	break;
      case 3: ;
	r=recreeReseauArbre(c);
	f=fopen("ReseauArbre.txt","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"ReseauArbre_graphe");
	liberer_reseau(r);
	break;
      case 4: ;
	r=reconstitueReseauListe(c);
	f=fopen("ReseauListe.txt","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"ReseauListe_graphe");
	liberer_reseau(r);
	r=recreeReseauHachage(c);
	f=fopen("ReseauHachage.txt","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"ReseauHachage_graphe");
	liberer_reseau(r);
	r=recreeReseauArbre(c);
	f=fopen("ReseauArbre.txt","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"ReseauArbre_graphe");
	liberer_reseau(r);
	break;
      case 5: ;
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu;
	FILE *res=fopen("TempsCalcul.txt","w");
	temps_initial=clock();
	r=reconstitueReseauListe(c);
	temps_final=clock();
	temps_cpu=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
	fprintf(res,"%f\n",temps_cpu);
	liberer_reseau(r);
	
	temps_initial=clock();
	r=recreeReseauHachage(c);
	temps_final=clock();
	fprintf(res,"%f\n",temps_cpu);
	liberer_reseau(r);
	
	temps_initial=clock();
	r=recreeReseauArbre(c);
	temps_final=clock();
	temps_cpu=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
	fprintf(res,"%f\n",temps_cpu);
	liberer_reseau(r);
	fclose(res);
	break;
      case 6: ;
        res=fopen("TempsCalcul.txt","w");
	temps_initial=clock();
	r=reconstitueReseauListe(c);
	temps_final=clock();
	temps_cpu=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
	fprintf(res,"%f\n",temps_cpu);
	f=fopen("ReseauListe.res","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"_ReseauListe");
	liberer_reseau(r);
	
	temps_initial=clock();
	r=recreeReseauHachage(c);
	temps_final=clock();
	fprintf(res,"%f\n",temps_cpu);
	f=fopen("ReseauHachage.res","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"_ReseauHachage");
	liberer_reseau(r);
	
	temps_initial=clock();
	r=recreeReseauArbre(c);
	temps_final=clock();
	temps_cpu=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
	fprintf(res,"%f\n",temps_cpu);
	f=fopen("ReseauArbre.res","w");
	ecrireReseauTxt(r,f);
	fclose(f);
	afficheReseauSVG(r,"_ReseauArbre");
	liberer_reseau(r);
	
	fclose(res);
	break;
      }
  } while (ch!=0);
  return 0;
}
