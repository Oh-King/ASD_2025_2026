#include "personaggi.h"
#include "inventario.h"
#include <stdlib.h>
#include <string.h>

link newNode(char *code, char *name, char *class, stat_t stats, int max_EQ) {
    link x = (link)malloc(sizeof(node_PG_t));
    if (x == NULL) return NULL;

    strcpy(x->code, code);
    strcpy(x->name, name);
    strcpy(x->class, class);
    x->PG_stats = stats;

    // Inizializza tab_EQ
    x->tab_EQ_ptr = (tab_EQ_t*)malloc(sizeof(tab_EQ_t));
    if (x->tab_EQ_ptr == NULL) {
        free(x);
        return NULL;
    }
    x->tab_EQ_ptr->curr_EQ = 0;
    x->tab_EQ_ptr->vettEQ = (obj_t**)malloc(max_EQ * sizeof(obj_t*));
    if (x->tab_EQ_ptr->vettEQ == NULL) {
        free(x->tab_EQ_ptr);
        free(x);
        return NULL;
    }

    x->next = NULL;
    return x;
}
