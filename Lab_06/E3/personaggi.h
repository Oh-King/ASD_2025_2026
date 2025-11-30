#ifndef LABORATORI_PERSONAGGI_H
#define LABORATORI_PERSONAGGI_H
#include "inventario.h"

typedef struct node_PG_t *link;

typedef struct {
    int currEQ;
    obj_t **vettEQ; //alloco un vettore di puntatori al vettore di oggetti nell'inventario
}tab_EQ_t;

typedef struct {
    char code[7];   //PGXXXX + terminatore
    char name[MAXLEN_N_T];
    char class[MAXLEN_N_T];
    tab_EQ_t *tab_EQ_ptr;
    stat_t PG_stats;
    link next;
}node_PG_t;

typedef struct {
    link head;
    link tail;
    int n_PG;
}tab_PG_t;

link newPGNode(link next, char *code, char *name, char *class, stat_t stats, tab_EQ_t *tab_EQ_ptr); //passo struct
link TAILinsert(link head, link tail); //serve head se inserisco in lista vuota
void deletePG(link head);
link searchCODE(char *code, link head);
void printPGnEQ(link head); //N.B: chiede codice/nome personaggio nella funzione stessa
void modEQofPG(char *code, link head, tab_inv_ptr tab_inv); //N.B: aggiunta/rimozione oggetto

#endif //LABORATORI_PERSONAGGI_H