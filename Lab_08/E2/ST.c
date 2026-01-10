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

}