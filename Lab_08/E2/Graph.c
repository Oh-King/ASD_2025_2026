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

