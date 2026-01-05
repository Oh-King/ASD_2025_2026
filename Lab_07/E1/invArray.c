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

}