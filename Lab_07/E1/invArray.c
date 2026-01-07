#include "invArray.h"

struct invArray_s {
    inv_t *inv_vett;
    int n_elem;
};

invArray_t invArray_init() {
    invArray_t invArr = malloc(sizeof(struct invArray_s));
    invArr->inv_vett = NULL;
    invArr->n_elem = 0;
    return invArr;
}
void invArray_free(invArray_t invArray) {
    free(invArray->inv_vett);
    free(invArray);
}
void invArray_read(FILE *fp, invArray_t invArray) {
    fscanf(fp, "%d", &(invArray->n_elem));
    for (int i = 0; i < invArray->n_elem; i++) {
        inv_read(fp, &(invArray->inv_vett[i]));
    }
}
void invArray_print(FILE *fp, invArray_t invArray) {
    for (int i = 0; i < invArray->n_elem; i++) {
        fprintf(fp, "%d) NOME: %s, TIPO: %s \n"
                    "STATISTICHE: hp:%d mp:%d atk:%d def:%d mag:%d spr:%d",i , invArray->inv_vett[i].nome, invArray->inv_vett[i].tipo,
        invArray->inv_vett[i].stat.hp, invArray->inv_vett[i].stat.mp, invArray->inv_vett[i].stat.atk,
        invArray->inv_vett[i].stat.def, invArray->inv_vett[i].stat.mag, invArray->inv_vett[i].stat.spr);
    }
}
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {
    fprintf(fp, "NOME: %s, TIPO: %s \n"
        "STATISTICHE: ", invArray->inv_vett[index].nome,
        invArray->inv_vett[index].tipo);
    stat_print(fp, &invArray->inv_vett[index].stat, -999);
}
inv_t* invArray_getByIndex(invArray_t invArray, int index) {
    inv_t *ptr = &(invArray->inv_vett[index]);
    return ptr;
}
int invArray_searchByName(invArray_t invArray, char *name) {
    int i;
    for (i = 0; i < invArray->n_elem; i++) {
        if (strcmp(invArray->inv_vett->nome, name) == 0) return i;
    }
    return -1;
}