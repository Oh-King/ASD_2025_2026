#include "equipArray.h"

struct equipArray_s {
    int equip[EQUIP_SLOT]; //ogni casella del vettore contiene indice del vettore inventario di equipaggiamento corrisp.
    int inUse; //numero di equipaggiamenti in uso
};

equipArray_t equipArray_init() {
    int i;
    equipArray_t equipArray = malloc(sizeof(struct equipArray_s));
    equipArray->inUse = 0;
    for(i = 0; i < EQUIP_SLOT; i++) {
        equipArray->equip[i] = -1;
    }
    return equipArray;
}

void equipArray_free(equipArray_t equipArray) {
    free(equipArray);
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray) {

}