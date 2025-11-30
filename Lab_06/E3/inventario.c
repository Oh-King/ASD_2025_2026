#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tab_inv_t WRAP_leggi_inv() {
    int n_obj;
    char filename[MAXLEN_N_T];
    printf("Inserisci il nome del file:\n");
    scanf("%s", filename);
    tab_inv_t tab_inv = leggi_file(filename);
    return tab_inv;
}

tab_inv_t leggi_inv(char *filename) {
    int  i = 0;
    tab_inv_t tab_inv;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL ) exit (1);
    fscanf(fp, "%d", &tab_inv.max_obj);
    tab_inv.n_obj = -1; // init a -1 ma devo cambiare
    tab_inv.OBJ = (obj_t*)malloc(tab_inv.max_obj*sizeof(obj_t));
    while (fscanf(fp,"%s %s %d %d %d %d %d %d",
        tab_inv.OBJ[i].name, tab_inv.OBJ[i].typo, &tab_inv.OBJ[i].stats.hp, &tab_inv.OBJ[i].stats.mp,
        &tab_inv.OBJ[i].stats.atk,&tab_inv.OBJ[i].stats.def,&tab_inv.OBJ[i].stats.mag,&tab_inv.OBJ[i].stats.spr) == 8) {
        i++;
    }
    fclose(fp);
    return tab_inv;
}

int NAMEsearch(char *name, tab_inv_t *tab_inv) {   //O(n)
    int i;
    for (i = 0; i < tab_inv->max_obj; i++)
        if (strcmp(tab_inv->OBJ[i].name, name) == 0) return i;
    return -1;
}

void PRINTdetails(tab_inv_t *tab_inv) {      //O(n)
    char name[MAXLEN_N_T];
    printf("Inserisci il nome dell'oggetto che vuoi ricercare:\n");
    scanf("%s", name);
    int i = NAMEsearch(name, tab_inv);
    if (i != -1) {
        printf("I dettagli dell'oggetto - %s - sono:\n", name);
        printf("Tipologia: %s\n", tab_inv->OBJ[i].typo);
        printf("Hp: %d\n", tab_inv->OBJ[i].stats.hp);
        printf("Mp: %d\n", tab_inv->OBJ[i].stats.mp);
        printf("Atk: %d\n", tab_inv->OBJ[i].stats.atk);
        printf("Def: %d\n", tab_inv->OBJ[i].stats.def);
        printf("Mag: %d\n", tab_inv->OBJ[i].stats.mag);
        printf("Spr: %d\n", tab_inv->OBJ[i].stats.spr);
        return;
    }
    else {
       printf("Non è stato trovato nessun oggetto con quel nome\n");
    return;
    }
}

void FREEinv(tab_inv_t *tab_inv) {
    free(tab_inv->OBJ);
}


