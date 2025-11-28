#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

obj_t* WRAP_leggi_file() {
    char *filename = NULL;
    printf("Inserisci il nome del file:\n");
    scanf("%s", filename);
    obj_t *obj = leggi_file(filename);
    return obj;
}

obj_t *leggi_file(char *filename, int *n_obj) {
    int  i = 0;
    char temp[MAXLEN_N_T];
    FILE *fp = fopen("filename", "r");
    fscanf(fp, "%d", n_obj);
    obj_t *OBJ = (obj_t*)malloc(*n_obj*sizeof(obj_t));
    while (fscanf(fp,"%s %s %d %d %d %d %d %d",
        OBJ[i].name, OBJ[i].typo, &OBJ[i].hp, &OBJ[i].mp,&OBJ[i].atk,&OBJ[i].def,&OBJ[i].mag,&OBJ[i].spr) == 7) {
        i++;
    }
    fclose(fp);
    return OBJ;
}

obj_t NAMEsearch(char *name, obj_t *OBJ, int n_obj) {   //O(n)
    int i;
    for (i = 0; i < n_obj; i++)
        if (strcmp(OBJ[i].name, name) == 0) return OBJ[i];
}

void PRINTdetails(obj_t *OBJ, int n_obj) {      //O(n)
    int i;
    char name[MAXLEN_N_T];
    printf("Inserisci il nome dell'oggetto che vuoi ricercare:\n");
    scanf("%s", name);
    for (i = 0; i < n_obj; i++) {
        if (strcmp(OBJ[i].name, name)) {
            printf("I dettagli dell'oggetto - %s - sono:\n", name);
            printf("Tipologia: %s\n",OBJ[i].typo);
            printf("Hp: %d\n", OBJ[i].hp);
            printf("Mp: %d\n", OBJ[i].mp);
            printf("Atk: %d\n", OBJ[i].atk);
            printf("Def: %d\n", OBJ[i].def);
            printf("Mag: %d\n", OBJ[i].mag);
            printf("Spr: %d\n", OBJ[i].spr);
            }
        }
    }


