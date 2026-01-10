#ifndef LABORATORI_GRAPH_H
#define LABORATORI_GRAPH_H

#include <stdio.h>

#define MAXC 31

typedef struct graph *Graph;
typedef struct node *link;
typedef struct {
    int u, v, flusso;
}edge_t;

Graph GRAPHinit(int V); //ok
void GRAPHload(FILE *fin, Graph G); //ok
int strcmp_wrap(const void *a, const void *b); //ok
void GRAPHstore(Graph G, FILE *fout); //ok
int GRAPHgetIndex(Graph G, char *name); //ok
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void GRAPHremoveE(Graph G, int id1, int id2);
void GRAPHedges(Graph G, edge_t *a);
int GRAPHpath(Graph G, int id1, int id2);
void GRAPHlistFree(Graph G);
void GRAPHlistCreate(Graph G);
int GRAPHcheck3_M(Graph G, int a, int b, int c);
int GRAPHcheck3_L(Graph G, int id1, int id2, int id3);

#endif //LABORATORI_GRAPH_H