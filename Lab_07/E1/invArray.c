#include "invArray.h"

struct invArray_s {
    inv_t *inv_vett;
    int n_elem, index;
};

invArray_t invArray_init() {
    invArray_t invArr = malloc(sizeof(*invA));
    invArr->inv_vett = NULL;
    invArr->n_elem = 0;
    return invArr;
}
