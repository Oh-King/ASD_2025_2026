#ifndef LABORATORI_PERSONAGGI_H
#define LABORATORI_PERSONAGGI_H

#include "inventario.h"

#define MAXLEN_N_T 51

typedef struct {
    obj_t **vettEQ;
    int currEQ;
} tab_EQ_t;

typedef struct node_PG_t {
    char code[7];
    char name[MAXLEN_N_T];
    char class[MAXLEN_N_T];
    tab_EQ_t *tab_EQ_ptr;
    stat_t PG_stats;
    struct node_PG_t *next;
} node_PG_t;

typedef node_PG_t *link;

typedef struct {
    link head, tail;
    int n_PG;
} tab_PG_t;

tab_PG_t WRAP_leggi_PG();
tab_PG_t leggi_PG(char *filename);
link newPGNode(char *code, char *name, char *class, stat_t stats);
void insertPG(tab_PG_t *tab_PG, link node);
void deletePG(tab_PG_t *tab_PG, char *code);
link SEARCHcode(tab_PG_t *tab_PG, char *code);
void modEQofPG(tab_PG_t *tab_PG, tab_inv_t *tab_inv);
void addEQ(link pg, tab_inv_t *tab_inv);
void removeEQ(link pg);
void PRINTpersonaggi(tab_PG_t *tab_PG);
void PRINTstatsfinali(link pg);
stat_t calcStatsFINAL(link pg);
void FREEpersonaggi(tab_PG_t *tab_PG);

#endif
