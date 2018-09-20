#ifndef __TD7_H__
#define __TD7_H__

#include <stdlib.h>
#include <stdio.h>
#include "Struct_File.h"
#include "Struct_Liste.h"
#include "Graphe.h"

/* Retourne le plus petit nombre d'arêtes d'un chemin entre deux sommets u et v d'un graphe */
int len_chemin_avec_min_d_aretes(Graphe *G, int u, int v);

/* Retourne la liste d'entiers correspondant au chemin avec le minimun d'arêtes entre u et v */
ListeEntier* chemin_avec_min_d_aretes(Graphe *G, int u, int v);

/* Retourne le pointeur d'un tableau qui represente le chemin avec le minimun d'arêtes pour chaque commodité du graphe */
ListeEntier** chaines_commodites(Graphe *G);

/* Retourne la longueur de l'arête entre u et v dans le graphe G */
double longueur_arete(Graphe *G, int u, int v);

/* Calcule la longueur totale des chemins d'un graphe */
double calcule_longueur(Graphe *G,ListeEntier** chaines,double *pointeur);

/* Augmente le gamma de l'arete entre u et v */
int augmente_gamma(Graphe *G, int u, int v);

/* Calcule le gamma du graphe G */
int calcule_gamma(Graphe *G, ListeEntier** chaines);

#endif
