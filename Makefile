CC = gcc
CFLAGS = -Wall -g
EXEC = ChainMain main MainGraphe td9

all: $(EXEC)

SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) $(CFLAGS) -c $<

entree_sortie.o: entree_sortie.c entree_sortie.h
	$(CC) $(CFLAGS) -c $<

Chaine.o: Chaine.c Chaine.h entree_sortie.h SVGwriter.h
	$(CC) $(CFLAGS) -c $<

ChainMain.o: ChainMain.c Chaine.h
	$(CC) $(CFLAGS) -c $<

ChainMain: ChainMain.o Chaine.o entree_sortie.o SVGwriter.o
	$(CC) $(CFLAGS) -lm -o $@ $^

Reseau.o: Reseau.c Reseau.h Chaine.h
	$(CC) $(CFLAGS) -c $<

Hachage.o: Hachage.c Hachage.h Reseau.o
	$(CC) $(CFLAGS) -c $<

arbre_quat.o: arbre_quat.c arbre_quat.h Reseau.o
	$(CC) $(CFLAGS) -c $<

ReconstitueReseau.o: ReconstitueReseau.c Reseau.h Hachage.h arbre_quat.h
	$(CC) $(CFLAGS) -c $<

ReconstitueReseau: ReconstitueReseau.o Reseau.o Hachage.o arbre_quat.o Chaine.o entree_sortie.o SVGwriter.o
	$(CC) $(CFLAGS) -lm -o $@ $^

main.o: main.c Reseau.h Hachage.h arbre_quat.o
	$(CC) $(CFLAGS) -c $<

main: main.o Reseau.o Hachage.o arbre_quat.o Chaine.o entree_sortie.o SVGwriter.o
	$(CC) $(CFLAGS) -lm -o $@ $^

MainGraphe: MainGraphe.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o Struct_Tas.o evaluation_NChaines.o td7.o td8.o
	gcc -Wall -O -o MainGraphe $^ -lm

MainGraphe.o: MainGraphe.c Graphe.h
	gcc -c MainGraphe.c

Graphe.o: Graphe.c Graphe.h SVGwriter.h Struct_File.h Struct_Liste.h
	gcc -c Graphe.c

Struct_File.o: Struct_File.c Struct_File.h
	gcc -c Struct_File.c

Struct_Liste.o: Struct_Liste.c Struct_Liste.h
	gcc -c Struct_Liste.c

Struct_Tas.o: Struct_Tas.c Struct_Tas.h
	gcc -c Struct_Tas.c

evaluation_NChaines.o: evaluation_NChaines.c evaluation_NChaines.h
	gcc -c evaluation_NChaines.c

td7.o: td7.c td7.h
	gcc -c td7.c

td8.o: td8.c td8.h
	gcc -c td8.c

td9: td9.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o Struct_Tas.o evaluation_NChaines.o td7.o td8.o
	gcc -Wall -O -o td9 $^ -lm

td9.o: td9.c Graphe.h
	gcc -c td9.c

clean: 
	rm -fr *.o $(EXEC)
	