#include "ST.h"
#include "Graph.h"

struct symbolTable {
    char **names;
    int n_elem;
    int max_elem;
};

ST STinit(int V) {
    ST symbtab = malloc(sizeof(struct  symbolTable));
    symbtab->names = malloc(V*sizeof(char*));
    symbtab->n_elem = 0;
    symbtab->max_elem = V;
    return symbtab;
}

void STinsert(ST tab, char *name) { //inserisco ordinato -> non mi serve indice nel prototipo
    int i;
    if (tab->n_elem == tab->max_elem) { //se sono già a massima dimensione
        tab->max_elem = tab->max_elem*2;
        tab->names = realloc(tab->names, tab->max_elem*sizeof(char*));
    }
    i = tab->n_elem-1;
    while ((i >= 0) && (strcmp(name, tab->names[i]) < 0)) {
        tab->names[i+1] = tab->names[i]; //copio puntatore in posizione successiva quindi shifto a destra
        i--;
    }
    tab->names[i+1] = strdup(name); /* sono fuori while quindi o i < 0 oppure strcmp ritorna >=0, quindi devo
    mettere name nella posizione successiva a i*/
    tab->n_elem++;
}

int STcount(ST tab) {
    return tab->n_elem;
}

int STsearch(ST tab, char *name) { //poiché vettore ordinato ->ricerca dicotomica
    int l = 0, r = tab->n_elem-1;
    while ( r >= l) {
        int mid = (l+r)/2;
        int confronto = strcmp(name, tab->names[mid]);
        if (confronto == 0) return mid;
        if (confronto > 0) {
            l = mid+1;
        }else r = mid-1;
    }
    return -1; //non ho trovato indice in tabella di simboli
}

char *STsearchByIndex(ST tab, int index) {
    return tab->names[index];
}
void STfree(ST tab) {
    for (int i = 0; i < tab->n_elem; i++)
        free(tab->names[i]);
    free(tab->names);
    free(tab);
}
