#ifndef __EVALUATION_H__
#define __EVALUATION_H__

double eval(int gammaMin,int gammaMax,double longueurMin,double longueurMax,int gamma,double longueur);


/* Fonction retournant l evaluation d une solution donnee par gamma et longueur totale des chaines; ne fonctionne que pour les instances
   00783_rat, 05934_rl et 07397_pla */
double evaluation_NChaines(int gamma, double longueur,char* nom);

#endif

