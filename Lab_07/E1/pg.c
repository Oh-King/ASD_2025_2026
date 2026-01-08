#include "pg.h"
#include "inv.h"
#include "invArray.h"

int pg_read(FILE *fp, pg_t *pgp) {
    if (fscanf(fp, "%s %s %s ",
               pgp->code, pgp->nome, pgp->classe) != 3) {
        return -1;
    }
    stat_read(fp, &(pgp->b_stat));
    pgp->equip = equipArray_init();
    //devo inizializzare a zero tutte le statistiche dell'equipaggiamento
    pgp->eq_stat.hp = 0;
    pgp->eq_stat.mp = 0;
    pgp->eq_stat.atk = 0;
    pgp->eq_stat.def = 0;
    pgp->eq_stat.mag = 0;
    pgp->eq_stat.spr = 0;
    return 0;
}

void pg_clean(pg_t *pgp) {
    equipArray_free(pgp->equip);
    pgp->equip = NULL;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    fprintf(fp, "PERSONAGGIO %s:\n", pgp->nome);
    fprintf(fp, " CODICE:%s, CLASSE:%s\nSTATISTICHE BASE: ",
        pgp->code, pgp->classe);
    stat_print(fp, &(pgp->b_stat), 1);
    fprintf(fp, "STATISTICHE EQUIPAGGIAMENTI: ");
    stat_print(fp, &(pgp->eq_stat), -999); //cerco di non dare limiti a soglia per equipaggiamenti, possono dare malus
    fprintf(fp, "STATISTICHE FINALI: ");
    stat_t fin_stat;
    fin_stat.hp = pgp->b_stat.hp + pgp->eq_stat.hp;
    fin_stat.mp = pgp->b_stat.mp + pgp->eq_stat.mp;
    fin_stat.atk = pgp->b_stat.atk + pgp->eq_stat.atk;
    fin_stat.def = pgp->b_stat.def + pgp->eq_stat.def;
    fin_stat.mag = pgp->b_stat.mag + pgp->eq_stat.mag;
    fin_stat.spr = pgp->b_stat.spr + pgp->eq_stat.spr;
    stat_print(fp, &fin_stat, 1);
    fprintf(fp, "EQUIPAGGIAMENTI IN USO:\n");
    equipArray_print(fp, pgp->equip, invArray);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    equipArray_update(pgp->equip, invArray);
    //aggiorno stats
    pgp->eq_stat.hp = pgp->eq_stat.mp = 0;
    pgp->eq_stat.atk = pgp->eq_stat.def = 0;
    pgp->eq_stat.mag = pgp->eq_stat.spr = 0;
    for (int i = 0; i < EQUIP_SLOT; i++) {
        int index = equipArray_getEquipByIndex(pgp->equip, i);
        if (index != -1) {
            inv_t *item = invArray_getByIndex(invArray, index);
            stat_t s = inv_getStat(item);
            pgp->eq_stat.hp += s.hp;
            pgp->eq_stat.mp += s.mp;
            pgp->eq_stat.atk += s.atk;
            pgp->eq_stat.def += s.def;
            pgp->eq_stat.mag += s.mag;
            pgp->eq_stat.spr += s.spr;
        }
    }
}