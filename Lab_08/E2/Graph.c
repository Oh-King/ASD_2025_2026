#include "Graph.h"

struct node {
    int V;
    int wt;
    link next;
};

struct graph {
    int V, E;
    int **m_ADJ;
    link l_ADJ;
    ST tab;
};

