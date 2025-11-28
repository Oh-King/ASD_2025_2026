#ifndef LABORATORI_INVENTARIO_H
#define LABORATORI_INVENTARIO_H

#define MAXLEN_N_T 51
typedef struct {
    char *name;
    char *typo;
    int hp, mp, atk, def, mag, spr; // se >0 bonus, se <0 malus
}obj_t;

void WRAP_leggi_file();
obj_t* leggi_file(char *filename);


#endif //LABORATORI_INVENTARIO_H