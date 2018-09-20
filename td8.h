#ifndef _TD8_H_
#define _TD8_H_

#include "Struct_Tas.h"
#include "Struct_Liste.h"
#include "td7.h"

ListeEntier* algo_Dijkstra(Graphe *g, int u, int v);
ListeEntier** chaines_commodites_tas(Graphe *G);

#endif
