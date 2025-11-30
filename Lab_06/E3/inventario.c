#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tab_inv_t WRAP_leggi_inv() {
    char filename[MAXLEN_N_T];
    printf("Inserisci il nome del file inventario:\n");
    scanf("%s", filename);
    return leggi_inv(filename);
}

tab_inv_t leggi_inv(char *filename) {
    int i = 0;
    tab_inv_t tab_inv;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) exit(1);

    fscanf(fp, "%d", &tab_inv.max_obj);
    tab_inv.n_obj = 0;
    tab_inv.OBJ = (obj_t*)malloc(tab_inv.max_obj * sizeof(obj_t));

    while (fscanf(fp, "%s %s %d %d %d %d %d %d",
                  tab_inv.OBJ[i].name, tab_inv.OBJ[i].typo,
                  &tab_inv.OBJ[i].stats.hp, &tab_inv.OBJ[i].stats.mp,
                  &tab_inv.OBJ[i].stats.atk, &tab_inv.OBJ[i].stats.def,
                  &tab_inv.OBJ[i].stats.mag, &tab_inv.OBJ[i].stats.spr) == 8) {
        i++;
        tab_inv.n_obj++;
                  }

    fclose(fp);
    return tab_inv;
}

int NAMEsearch(char *name, tab_inv_t *tab_inv) {
    for (int i = 0; i < tab_inv->n_obj; i++) {
        if (strcmp(tab_inv->OBJ[i].name, name) == 0) return i;
    }
    return -1;
}

void PRINTdetails(tab_inv_t *tab_inv) {
    char name[MAXLEN_N_T];
    printf("Inserisci il nome dell'oggetto:\n");
    scanf("%s", name);

    int i = NAMEsearch(name, tab_inv);
    if (i != -1) {
        printf("\n=== DETTAGLI %s ===\n", name);
        printf("Tipologia: %s\n", tab_inv->OBJ[i].typo);
        printf("HP: %d\n", tab_inv->OBJ[i].stats.hp);
        printf("MP: %d\n", tab_inv->OBJ[i].stats.mp);
        printf("ATK: %d\n", tab_inv->OBJ[i].stats.atk);
        printf("DEF: %d\n", tab_inv->OBJ[i].stats.def);
        printf("MAG: %d\n", tab_inv->OBJ[i].stats.mag);
        printf("SPR: %d\n", tab_inv->OBJ[i].stats.spr);
    } else {
        printf("Oggetto non trovato\n");
    }
}

void FREEinv(tab_inv_t *tab_inv) {
    free(tab_inv->OBJ);
}
