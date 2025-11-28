#ifndef LABORATORI_INVENTARIO_H
#define LABORATORI_INVENTARIO_H

#define MAXLEN_N_T 51
typedef struct {
    char *name;
    char *typo;
    int hp, mp, atk, def, mag, spr; // se >0 bonus, se <0 malus
}obj_t;

obj_t* WRAP_leggi_file();
obj_t* leggi_file(char *filename);
obj_t NAMEsearch(char *name, obj_t *OBJ, int n_obj);
void PRINTdetails(obj_t *OBJ, int n_obj);

#endif //LABORATORI_INVENTARIO_H