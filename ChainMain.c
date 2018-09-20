#include "Chaine.h"
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc !=3){
    printf ("Erreur format: %s <NomFichierOrigin.txt> <NomFichierDest.txt>", argv[0]);
    return 0;
  }
  char *nomfic;
  FILE *f;

  nomfic=strdup(argv[1]);
  f=fopen(nomfic,"r");
  free(nomfic);
  Chaines *chaine;
  chaine=lectureChaine(f);
  fclose(f);

  nomfic=strdup(argv[2]);
  f=fopen(nomfic,"w");
  free(nomfic);
  ecrireChaineTxt(chaine,f);
  fclose(f);

  afficheChaineSVG(chaine,"graphe");
  printf("Longueur totale: %f\n",longueurTotale(chaine));
  printf("Nombre de points: %d\n",comptePointsTotal(chaine));

  liberer_chaine(chaine);
  return 0;
}
