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

vvoid GRAPHload(Graph G, FILE *fin) {
    char elab1[MAXC], rete1[MAXC], elab2[MAXC], rete2[MAXC];
    int flusso;
    while (fscanf(fin, "%s %s %s %s %d", elab1, rete1, elab2, rete2, &flusso) == 5) {

        //unisco id e rete
        char nome1[70], nome2[70];
        sprintf(nome1, "%s_%s", elab1, rete1);
        sprintf(nome2, "%s_%s", elab2, rete2);
        int id1 = STsearch(G->tab, nome1);
        if (id1 == -1) {
            STinsert(G->tab, nome1);
            id1 = STsearch(G->tab, nome1);
        }
        int id2 = STsearch(G->tab, nome2);
        if (id2 == -1) {
            STinsert(G->tab, nome2);
            id2 = STsearch(G->tab, nome2);
        }
        if (G->m_ADJ[id1][id2] == 0) {
            G->m_ADJ[id1][id2] = flusso;
            G->m_ADJ[id2][id1] = flusso;
            G->E++;
        }
    }
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