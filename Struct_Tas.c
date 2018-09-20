#include "Struct_Tas.h"

int pere(int i)
{
  if (i==1)
    return 0;
  return i/2;
}

int filsGauche(Tas *t,int i)
{
  int fg=2*i;
  if (fg>t->n)
    return 0;
  else
    return fg;
}

int filsDroit(Tas *t,int i)
{
  int fd=2*i+1;
  if (fd>t->n)
    return 0;
  else
    return fd;
}

int plusPetitFils(Tas *t, int i)
{
  if (!filsDroit(t,i))
    return filsGauche(t,i);
  else{
    int fg=filsGauche(t,i);
    int fd=filsDroit(t,i);
    if (t->f[t->tab[fg]]<t->f[t->tab[fd]])
      return fg;
    else
      return fd;
  }
}

void init_Tas(Tas *t,int N)
{
  t->tab=(int *)malloc(sizeof(int)*N);
  t->M=(int *)malloc(sizeof(int)*N);
  t->f=(double *)malloc(sizeof(double)*N);
  int i;
  for (i=0;i<N;i++){
    t->M[i]=0;
  }
  t->n=0;
}

void echanger(Tas *t,int j,int k)
{
  int tmp=t->tab[j];
  t->tab[j]=t->tab[k];
  t->tab[k]=tmp;
  int i=t->tab[k];
  t->M[i]=k;
  i=t->tab[j];
  t->M[i]=j;

}

void monter(Tas *t,int j)
{
  if (!pere(j)) return;
  int p=pere(j);
  if (t->f[t->tab[p]]>t->f[t->tab[j]]){
    echanger(t,j,p);
    monter(t,p);
  }
}

void descendre(Tas *t, int j)
{
  if (!filsGauche(t,j))
    return;
  int fils=plusPetitFils(t,j);
  if (t->f[t->tab[fils]]<t->f[t->tab[j]]){
    echanger(t,fils,j);
    descendre(t,fils);
  }
}

void insert(Tas *t,double f,int i)
{
  if (t->M[i]==0){
    t->n++;
    t->f[i]=f;
    t->tab[t->n]=i;
    t->M[i]=t->n;
    monter(t,t->n);
  }
}

void supp(Tas *t,int i)
{
  int k=t->M[i];
  if (k>0){
    if (t->n>1){
      echanger(t,t->n,k);
      t->n--;
      if (t->f[t->tab[k]]<t->f[t->tab[pere(k)]]){
	monter(t,k);
      }
      else if (t->f[t->tab[k]]>t->f[t->tab[plusPetitFils(t,k)]])
	descendre(t,k);
      t->M[i]=0;
    }
    else if (t->n==1){
      t->n--;
      t->M[i]=0;
    }
  }
}

void maj_Tas(Tas *t,double f,int i)
{
  supp(t,i);
  insert(t,f,i);
}
