#include "inv.h"

void stat_read(FILE *fp, stat_t *statp) {
    if (fscanf(fp, "%d%d%d%d%d%d",
        &(statp->hp), &(statp->mp), &(statp->atk), &(statp->def), &(statp->mag), &(statp->spr))!= 6)
        exit(1);
    return;
}

void stat_print(FILE *fp, stat_t *statp, int soglia) { /*in questo caso soglia variabile,
    da esercizio se stat < 1 allora stampo 1, fp può essere stdout oppure file */
    fprintf(fp, "HP: %d, MP: %d, ATK: %d, DEF: %d, MAG: %d, SPR: %d\n",
        statp->hp < soglia? soglia : statp->hp,
        statp->mp < soglia? soglia : statp->mp,
        statp->atk < soglia ? soglia : statp->atk,
        statp->def < soglia ? soglia : statp->def,
        statp->mag < soglia ? soglia : statp->mag,
        statp->spr < soglia ? soglia: statp->spr
        );
}

void inv_read(FILE *fp, inv_t *invp) {
    if (fscanf(fp, "%s %s %d %d %d %d %d %d",
        invp->nome, invp->tipo, &(invp->stat.hp), &(invp->stat.mp), &(invp->stat.atk), &(invp->stat.def),
        &(invp->stat.mag), &(invp->stat.spr)) != 8) exit(1);
}

void inv_print(FILE *fp, inv_t *invp) {
    fprintf(fp, "NOME: %s, TIPO: %s\n"
                "STATISTICHE:"
                "hp:%d, mp:%d, atk:%d, def:%d, mag:%d, spr:%d",
                invp->nome, invp->tipo, invp->stat.hp, invp->stat.mp, invp->stat.atk, invp->stat.def,
                invp->stat.mag, invp->stat.spr);
}

stat_t inv_getStat(inv_t *invp) {
    return invp->stat;
}