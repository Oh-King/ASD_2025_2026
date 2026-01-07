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
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    fprintf(fp, "PERSONAGGIO %s:\n", pgp->nome);
    fprintf(fp, " CODICE:%s\nCLASSE:%s\nSTATISTICHE BASE: hp:%d mp:%d atk:%d def:%d mag:%d spr:%d \n",
        pgp->code, pgp->classe, pgp->b_stat.hp, pgp->b_stat.mp, pgp->b_stat.atk,
        pgp->b_stat.def, pgp->b_stat.mag, pgp->b_stat.spr);
    fprintf(fp, "");
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    equipArray_update(pgp->equip, invArray);
}