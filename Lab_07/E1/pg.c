#include "pg.h"
#include "inv.h"
#include "invArray.h"

int pg_read(FILE *fp, pg_t *pgp) {
    if (fscanf(fp, "%s %s %s %d %d %d %d %d %d",
               pgp->code, pgp->nome, pgp->classe,
               &pgp->b_stat.hp, &pgp->b_stat.mp,
               &pgp->b_stat.atk, &pgp->b_stat.def,
               &pgp->b_stat.mag, &pgp->b_stat.spr) != 9) {
        return -1;
    }
    pgp->equip = equipArray_init(); //da vedere
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
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray) {

}