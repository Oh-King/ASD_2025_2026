#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>

obj_t* WRAP_leggi_file() {
    char *filename = NULL;
    printf("Inserisci il nome del file:\n");
    scanf("%s", filename);
    obj_t *obj = leggi_file(filename);
    return obj;
}

obj_t *leggi_file(char *filename) {
    int n_obj, i = 0;
    char temp[MAXLEN_N_T];
    FILE *fp = fopen("filename", "r");
    fscanf(fp, "%d", &n_obj);
    obj_t *OBJ = (obj_t*)malloc(n_obj*sizeof(obj_t));
    while (fscanf(fp,"%s %s %d %d %d %d %d %d",
        OBJ[i].name, OBJ[i].typo, &OBJ[i].hp, &OBJ[i].mp,&OBJ[i].atk,&OBJ[i].def,&OBJ[i].mag,&OBJ[i].spr) == 7) {
        i++;
    }
    fclose(fp);
    return OBJ;
}