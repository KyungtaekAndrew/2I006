#include "Reseau.h"
#include "Hachage.h"
#include "arbre_quat.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  if (argc!=3){
    printf("Erreur de format: %s <Fichier.cha> <Numero_methode>", argv[0]);
    return 0;
  }
  FILE *f=fopen(argv[1],"r");
  Chaines *c;
  c=lectureChaine(f);
  fclose(f);

  switch (atoi(argv[2]))
    {
    case 1: ;
      Reseau *r=reconstitueReseauListe(c);
      f=fopen("test1_reconstitueReseau.txt","w");
      ecrireReseauTxt(r,f);
      fclose(f);
      afficheReseauSVG(r,"test1_graphe");
      liberer_reseau(r);
      break;
    case 2: ;
      Reseau *r2=recreeReseauHachage(c);
      f=fopen("test2_reconstitueReseau.txt","w");
      ecrireReseauTxt(r2,f);
      fclose(f);
      afficheReseauSVG(r2,"test2_graphe");
      liberer_reseau(r2);
      break;
    case 3: ;
      Reseau *r3=recreeReseauArbre(c);
      f=fopen("test3_reconstitueReseau.txt","w");
      ecrireReseauTxt(r3,f);
      fclose(f);
      afficheReseauSVG(r3,"test3_graphe");
      liberer_reseau(r3);
      break;
    }

  liberer_chaine(c);
  return 0;
}
