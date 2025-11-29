#ifndef LABORATORI_INVENTARIO_H
#define LABORATORI_INVENTARIO_H

#define MAXLEN_N_T 51

typedef struct {
    int hp, mp, atk, def, mag, spr; // se >0 bonus, se <0 malus
}stat_t;

typedef struct {
    char name[MAXLEN_N_T];
    char typo[MAXLEN_N_T];
    stat_t stats;
}obj_t;

typedef struct {
    obj_t *OBJ;
    int n_obj, max_obj;
}tab_inv_t;

typedef struct tab_inv_t *tab_inv;

tab_inv_t WRAP_leggi_inv();
tab_inv_t leggi_inv(char *filename);
int NAMEsearch(char *name, tab_inv_t *tab_inv);
void PRINTdetails(tab_inv_t *tab_inv);
void FREEinv(tab_inv_t *tab_inv);

#endif //LABORATORI_INVENTARIO_H