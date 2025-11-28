#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>

obj_t *leggi_file(char *filename) {
    int n_obj, i = 0;
    char temp[MAXLEN_N_T];
    FILE *fp = fopen("filename", "r");
    fscanf(fp, "%d", &n_obj);
    obj_t *OBJ = (obj_t*)malloc(n_obj*sizeof(obj_t));
    while (fscanf(fp,"%s %d%d%d%d%d%d", temp, &OBJ[i].hp, &OBJ[i].mp,&OBJ[i].atk,&OBJ[i].def,&OBJ[i].mag,&OBJ[i].spr) == 7);

    return OBJ;
}