#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tab_inv_t WRAP_leggi_file() {
    int n_obj;
    char filename[MAXLEN_N_T];
    printf("Inserisci il nome del file:\n");
    scanf("%s", filename);
    tab_inv_t tab_inv = leggi_file(filename);
    return tab_inv;
}

tab_inv_t leggi_file(char *filename) {
    int  i = 0;
    tab_inv_t tab_inv;
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &tab_inv.n_obj);
    tab_inv.OBJ = (obj_t*)malloc(tab_inv.n_obj*sizeof(tab_inv_t));
    while (fscanf(fp,"%s %s %d %d %d %d %d %d",
        tab_inv.OBJ[i].name, tab_inv.OBJ[i].typo, &tab_inv.OBJ[i].hp, &tab_inv.OBJ[i].mp,
        &tab_inv.OBJ[i].atk,&tab_inv.OBJ[i].def,&tab_inv.OBJ[i].mag,&tab_inv.OBJ[i].spr) == 8) {
        i++;
    }
    fclose(fp);
    return tab_inv;
}

int NAMEsearch(char *name, obj_t *OBJ, int n_obj) {   //O(n)
    int i;
    for (i = 0; i < n_obj; i++)
        if (strcmp(OBJ[i].name, name) == 0) return i;
    return -1;
}

void PRINTdetails(obj_t *OBJ, int n_obj) {      //O(n)
    char name[MAXLEN_N_T];
    printf("Inserisci il nome dell'oggetto che vuoi ricercare:\n");
    scanf("%s", name);
    int i = NAMEsearch(name, OBJ, n_obj);
    if (i != -1) {
        printf("I dettagli dell'oggetto - %s - sono:\n", name);
    printf("Tipologia: %s\n",OBJ[i].typo);
    printf("Hp: %d\n", OBJ[i].hp);
    printf("Mp: %d\n", OBJ[i].mp);
    printf("Atk: %d\n", OBJ[i].atk);
    printf("Def: %d\n", OBJ[i].def);
    printf("Mag: %d\n", OBJ[i].mag);
    printf("Spr: %d\n", OBJ[i].spr);
    return;
    }
    else {
       printf("Non è stato trovato nessun oggetto con quel nome\n");
    return;
    }
}


