#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pgList.h"
#include "invArray.h"
#include "pg.h"

#define N_SCELTE 7
#define DBG 0

enum { falso, vero };
typedef int bool;

void stampaMenu(char *scelte[], int *selezione) {
    int i = 0;
    printf("\nMENU'\n");
    for (i = 0; i < N_SCELTE; i++)
        printf("%2d > %s\n", i, scelte[i]);
    fflush(stdout);
    scanf(" %d", selezione);
}

int main(int argc, char **argv) {
    printf("FASE 0: Programma avviato\n");
    fflush(stdout);
    char *scelte[] = {
        "Uscita",
        "Stampa personaggi",
        "Stampa inventario",
        "Cerca personaggio",
        "Aggiungi personaggio",
        "Elimina personaggio",
        "Modifica equip"
    };

    char codiceRicerca[LEN];
    int selezione;
    FILE *fin;
    bool fineProgramma;

    printf("FASE 1: alloco le varie strutture\n");
    fflush(stdout);
    pgList_t pgList = pgList_init(); //aggiungo nodo sentinella
    invArray_t invArray = invArray_init();
    pg_t *pgp, pg;

    printf("FASE 2: apro pg.txt\n");
    fflush(stdout);
    fin = fopen("pg.txt", "r");
    if (fin == NULL) {
        printf("ERRORE NELL'APERTURA DEL FILE pg.txt\n");
        return -1;
    }
    printf("FASE 3: chiamo pgList_read e chiudo file\n");
    fflush(stdout);
    pgList_read(fin, pgList);
    fclose(fin);
#if DBG
    pgList_print(stdout, pgList);
#endif /* DBG */
    printf("FASE 4: apro inventario.txt");
    fflush(stdout);
    fin = fopen("inventario.txt", "r");
    if (fin == NULL) {
        printf("ERRORE NELL'APERTURA DEL FILE inventario.txt\n");
        return -1;
    }
    printf("FASE 5: chiamo invArray_read e chiudo file\n");
    fflush(stdout);
    invArray_read(fin, invArray);
    fclose(fin);
#if DBG
    invArray_print(stdout, invArray);
#endif /* DBG */
    printf("FASE 6: entro loop Menu\n");
    fflush(stdout);
    fineProgramma = falso;

    do {
        printf("FASE 7: stampo Menu\n");
        fflush(stdout);
        stampaMenu(scelte, &selezione);
        printf("FASE 8: ho stampato il menu. Ho selezionato: %d\n", selezione);
        fflush(stdout);
        switch (selezione) {
            case 0: {
                fineProgramma = vero;
            }
            break;

            case 1: {
                pgList_print(stdout, pgList, invArray);
            }
            break;

            case 2: {
                invArray_print(stdout, invArray);
            }
            break;

            case 3: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgp = pgList_searchByCode(pgList, codiceRicerca);
                if (pgp != NULL) {
                    pg_print(stdout, pgp, invArray);
                }
            }
            break;

            case 4: {
                printf("Cod Nome Classe HP MP ATK DEF MAG SPR: ");
                if (pg_read(stdin, &pg) == 0) {
                    pgList_insert(pgList, pg);
                }else printf("Errore lettura personaggio\n");
            }
            break;

            case 5: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgList_remove(pgList, codiceRicerca);
            }
            break;

            case 6: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgp = pgList_searchByCode(pgList, codiceRicerca);
                if (pgp != NULL) {
                    pg_updateEquip(pgp, invArray);
                }
            }
            break;

            default: {
                printf("Scelta non valida\n");
            }
            break;
        }
    } while (!fineProgramma);

    printf("FASE 9: sono prima di pgList_free e invArray_free\n");
    fflush(stdout);
    pgList_free(pgList);
    invArray_free(invArray); //libero anche inventario
    return 0;
}
