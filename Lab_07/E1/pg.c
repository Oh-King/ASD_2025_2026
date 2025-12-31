#include "pg.h"
#include "inv.h"
#include "invArray.h"

int pg_read(FILE *fp, pg_t *pgp) {
    char filename[LEN];
    printf("Inserisci nome file:");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    fprintf(fp, "===DETTAGLI DEL PERSONAGGIO %s===", pgp->nome);
    fprintf(fp, "CODICE: %s"
                "CLASSE: %s "
                "HP: %d"
                "MP: %d"
                "ATK: %d"
                "DEF: %d"
                "MAG: %d"
                "SPR: %d", pgp->code, pgp->classe,
                pgp->b_stat.hp ,pgp->b_stat.mp ,
                pgp->b_stat.atk ,pgp->b_stat.def ,
                pgp->b_stat.mag, pgp->b_stat.spr);
}