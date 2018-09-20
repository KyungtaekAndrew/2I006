#include "Struct_Tas.h"
#include <stdio.h>

int main()
{
  Tas *tas1=(Tas *)malloc(sizeof(Tas));
  init_Tas(tas1);
  insert(tas1,15,5);
  insert(tas1,12,6);
  insert(tas1,22,2);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[1],tas1->M[tas1->tab[1]],tas1->f[tas1->tab[1]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[2],tas1->M[tas1->tab[2]],tas1->f[tas1->tab[2]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[3],tas1->M[tas1->tab[3]],tas1->f[tas1->tab[3]]);
  supp(tas1,5);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[1],tas1->M[tas1->tab[1]],tas1->f[tas1->tab[1]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[2],tas1->M[tas1->tab[2]],tas1->f[tas1->tab[2]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[3],tas1->M[tas1->tab[3]],tas1->f[tas1->tab[3]]);
  maj_Tas(tas1,23,6);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[1],tas1->M[tas1->tab[1]],tas1->f[tas1->tab[1]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[2],tas1->M[tas1->tab[2]],tas1->f[tas1->tab[2]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[3],tas1->M[tas1->tab[3]],tas1->f[tas1->tab[3]]);
  insert(tas1,21,5);
  insert(tas1,22.5,3);
  printf("Salut\n");
  printf("%d %d %d %f\n",tas1->n,tas1->tab[1],tas1->M[tas1->tab[1]],tas1->f[tas1->tab[1]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[2],tas1->M[tas1->tab[2]],tas1->f[tas1->tab[2]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[3],tas1->M[tas1->tab[3]],tas1->f[tas1->tab[3]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[4],tas1->M[tas1->tab[4]],tas1->f[tas1->tab[4]]);

  supp(tas1,5);
  //maj_Tas(tas1,22.4,5);
  printf("Salut\n");
  printf("%d %d %d %f\n",tas1->n,tas1->tab[1],tas1->M[tas1->tab[1]],tas1->f[tas1->tab[1]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[2],tas1->M[tas1->tab[2]],tas1->f[tas1->tab[2]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[3],tas1->M[tas1->tab[3]],tas1->f[tas1->tab[3]]);
  printf("%d %d %d %f\n",tas1->n,tas1->tab[4],tas1->M[tas1->tab[4]],tas1->f[tas1->tab[4]]);
  return 0;
}
