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

static link NEWnode(int V, int wt, link next) {
    link node = malloc(sizeof(struct node));
    node->V = V;
    node->wt = wt;
    node->next = next;
    return node;
}

int strcmp_wrap(const void *a, const void *b) {
    char *s1 = *(char**)a;
    char *s2 = *(char**)b;
    return strcmp(s1, s2);
}

void GRAPHload( FILE *fin, Graph G) {
    char elab1[MAXC], rete1[MAXC], elab2[MAXC], rete2[MAXC];
    int flusso;
    while (fscanf(fin, "%s %s %s %s %d", elab1, rete1, elab2, rete2, &flusso) == 5) {
        int id1 = STsearch(G->tab, elab1);
        if (id1 == -1) {
            STinsert(G->tab, elab1);
            id1 = STsearch(G->tab, elab1);
        }
        int id2 = STsearch(G->tab, elab2);
        if (id2 == -1) {
            STinsert(G->tab, elab2);
            id2 = STsearch(G->tab, elab2);
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

void GRAPHstore(Graph G, FILE *fout) { //matrice adiacenze è simmetrica
    int i, j;
    int dim = STcount(G->tab);
    for (i = 0; i < dim; i++) {
        char *v_name = STsearchByIndex(G->tab, i);
        fprintf(fout, "Il vertice in questione: %s\n I suoi vicini sono: ", v_name);
        int n_adj = 0;
        char **adj = malloc(dim * sizeof(char*));
        for (j = 0; j < dim; j++) {
            if (G->m_ADJ[i][j] != 0) {
                adj[n_adj] = STsearchByIndex(G->tab, j);
                n_adj++;
            }
        }
        qsort(adj, n_adj, sizeof(char*), strcmp_wrap);
        for (int k = 0; k < n_adj; k++) {
            fprintf(fout, "%s ", adj[k]);
        }
        fprintf(fout, "\n");
        free(adj);
    }
}

int GRAPHgetIndex(Graph G, char *name) {
    return STsearch(G->tab, name);
}

void GRAPHlistFree(Graph G) {
    if (G->l_ADJ == NULL)
        return;
    int V = STcount(G->tab);
    for (int i = 0; i < V; i++) {
        link t = G->l_ADJ[i];
        while (t != NULL) {
            link next = t->next;
            free(t);
            t = next;
        }
    }
    free(G->l_ADJ);
    G->l_ADJ = NULL;
}
void GRAPHlistCreate(Graph G) {
    int V = STcount(G->tab);
    //rpima libero
    GRAPHlistFree(G);
    //poi alloco
    G->l_ADJ = malloc(V * sizeof(link));
    for (int i = 0; i < V; i++) G->l_ADJ[i] = NULL;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (G->m_ADJ[i][j] != 0)
                G->l_ADJ[i] = NEWnode(j, G->m_ADJ[i][j], G->l_ADJ[i]);
        }
    }
}

int GRAPHcheck3_M(Graph G, int a, int b, int c) {
    return G->m_ADJ[a][b] && G->m_ADJ[a][c] && G->m_ADJ[b][c];
}

int GRAPHcheck3_L(Graph G, int a, int b, int c) {
    int ab = 0, ac = 0, bc = 0;
    for (link t = G->l_ADJ[a]; t != NULL; t = t->next)
        if (t->V == b) ab = 1;
    for (link t = G->l_ADJ[a]; t != NULL; t = t->next)
        if (t->V == c) ac = 1;
    for (link t = G->l_ADJ[b]; t != NULL; t = t->next)
        if (t->V == c) bc = 1;
    return ab && ac && bc;
}

void GRAPHfree(Graph G) {
    int V = STcount(G->tab);
    //libero matrice
    for (int i = 0; i < V; i++)
        free(G->m_ADJ[i]);
    free(G->m_ADJ);
    //libero lista
    if (G->l_ADJ != NULL) {
        for (int i = 0; i < V; i++) {
            link t = G->l_ADJ[i];
            while (t != NULL) {
                link next = t->next;
                free(t);
                t = next;
            }
        }
        free(G->l_ADJ);
    }
    //libero tabella simboli
    STfree(G->tab);
    // libera grafo
    free(G);
}

int GRAPHhasList(Graph G) {
    return G->l_ADJ != NULL;
}

