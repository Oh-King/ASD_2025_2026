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

int equipArray_inUse(equipArray_t equipArray) {
    int cnt = 0;
    int i;
    for (i = 0; i < EQUIP_SLOT; i++) {
        if (equipArray->equip[i] != -1) cnt++;  //ho supposto non fosse da fare banalmente return equipArray->inUse
    }
    return cnt;
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray) {

}