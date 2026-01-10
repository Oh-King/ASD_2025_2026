#include "Graph.h"
#include "ST.h"

struct node {
    int V;
    int wt; //sarebbe il flusso
    link next;
};

struct graph {
    int V, E;
    int **m_ADJ;
    link *l_ADJ;
    ST tab;
};

int GRAPHload(FILE *fin) {

}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->l_ADJ = NULL;
    G->m_ADJ = malloc(V*sizeof(int*));
    for (int i = 0; i < V; i++) {
        G->m_ADJ[i] = malloc(V*sizeof(int));
        for (int j = 0; j < V; j++) {
            G->m_ADJ[i][j] = 0;
        }
    }
    G->tab = STinit(V);
    return G;
}