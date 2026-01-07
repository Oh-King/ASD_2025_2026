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

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    int i;
    fprintf(fp,"EQUIPAGGIAMENTI:\n");
    for (i = 0; i < EQUIP_SLOT; i++) {
        if (equipArray->equip[i] != -1) {
            invArray_printByIndex(fp, invArray, equipArray->equip[i]);
        }
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    eq_act choice;
    char name[26];
    int index;
    printf("Vuoi aggiungere (0) o rimuovere (1) dall'inventario?\n");
    scanf("%d", &choice);
    if (choice == add) {
        if (equipArray->inUse == 8) {
            printf("Il personaggio ha già raggiunto il massimo di equipaggiamenti!\n");
            return;
        }
        printf("Inserisci il nome dell'oggetto che vuoi aggiungere:\n");
        scanf("%s", name);
        index = invArray_searchByName(invArray, name);
        for (int i = 0; i < EQUIP_SLOT; i++) {
            if (equipArray->equip[i] == -1) {
                equipArray->equip[i] = index;
                return;
            }
        }
    }else { //quindi si vuole rimuovere
        printf("Inserisci la posizione dell'equipaggiamento che vuoi rimuovere:\n");
        scanf("%d", &index);
        if (index < 0 || index > 7) {
            printf("Posizione non valida!");
            return;
        }
        if (equipArray->equip[index] != -1) {
            equipArray->equip[index] = -1;
        } else {
            printf("In quella posizione non c'è nessun equipaggiamento");
        }

    }
}