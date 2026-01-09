#ifndef LABORATORI_GRAPH_H
#define LABORATORI_GRAPH_H

#include <stdio.h>

#define MAXC 31

typedef struct graph *Graph;
typedef struct node *link;
typedef struct {
    int u, v, wt, flusso;
    char elab1[MAXC];
    char rete1[MAXC];
    char elab2[MAXC];
    char rete2[MAXC];
}edge_t;

Graph GRAPHinit(int V);
void GRAPHload(FILE *fin);
void GRAPHstore(Graph G, FILE *fout);
int GRAPHgetIndex(Graph G, char *name);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void GRAPHremoveE(Graph G, int id1, int id2);
void GRAPHedges(Graph G, edge_t *a);
int GRAPHpath(Graph G, int id1, int id2);
static link NEWnode(int V, int wt, link next);

#endif //LABORATORI_GRAPH_H