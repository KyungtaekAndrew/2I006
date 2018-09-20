
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double max(double a,double b){
  if (a>b) return a;
  return b;
}

double eval(int gammaMin,int gammaMax,double longueurMin,double longueurMax,int gamma,double longueur){
  return ((1-(pow((pow((max((gamma-gammaMin),0)/(gammaMax-gammaMin)),2)+pow(((longueur-longueurMin)/(longueurMax-longueurMin)),2)),0.5))/(pow(2,0.5)))*100);
}

double evaluation_NChaines(int gamma, double longueur,char* nom){
  double gammaMin=0;
  double gammaMax=1;
  double longueurMin=0;
  double longueurMax=1;
  if (strcmp(nom,"07397_pla")==0) { 
    gammaMin = 947-100; 
    gammaMax = 1350;
    longueurMin = 1852207421.05;
    longueurMax=  3309558964.59;
  }
  else if (strcmp(nom,"00783_rat")==0){
    gammaMin = 35-10;
    gammaMax = 65;
    longueurMin = 90521.40;
    longueurMax= 179149.60;  
  } else if (strcmp(nom,"05934_rl")==0){
    gammaMin = 	182-30;
    gammaMax = 400;
    longueurMin = 20846876.42;
    longueurMax= 48710747.42;   
  } else return -1000000;
  return eval(gammaMin,gammaMax,longueurMin,longueurMax,gamma,longueur);
}






