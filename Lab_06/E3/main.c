#include "personaggi.h"
#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    tab_inv_t tab_inv;
    tab_PG_t tab_PG;
    int choice;

    // Caricamento inventario
    tab_inv = WRAP_leggi_inv();
    printf("Inventario caricato: %d oggetti\n", tab_inv.n_obj);

    // Caricamento personaggi
    tab_PG = WRAP_leggi_PG();
    printf("Personaggi caricati: %d\n", tab_PG.n_PG);

    do {
        printf("\n=== MENU ===\n");
        printf("1. Stampa personaggi\n");
        printf("2. Aggiungi personaggio\n");
        printf("3. Elimina personaggio\n");
        printf("4. Modifica equipaggiamento\n");
        printf("5. Stampa statistiche finali\n");
        printf("6. Stampa dettagli oggetto\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                PRINTpersonaggi(&tab_PG);
                break;

            case 2: {
                char code[7], name[MAXLEN_N_T], class[MAXLEN_N_T];
                stat_t stats;
                printf("Inserisci codice nome classe hp mp atk def mag spr:\n");
                scanf("%s %s %s %d %d %d %d %d %d",
                      code, name, class,
                      &stats.hp, &stats.mp, &stats.atk,
                      &stats.def, &stats.mag, &stats.spr);
                link new_pg = newPGNode(code, name, class, stats);
                if (new_pg != NULL) {
                    insertPG(&tab_PG, new_pg);
                    printf("Personaggio aggiunto\n");
                }
                break;
            }

            case 3: {
                char code[7];
                printf("Inserisci il codice del personaggio da eliminare:\n");
                scanf("%s", code);
                deletePG(&tab_PG, code);
                break;
            }

            case 4:
                modEQofPG(&tab_PG, &tab_inv);
                break;

            case 5: {
                char code[7];
                printf("Inserisci il codice del personaggio:\n");
                scanf("%s", code);
                link pg = SEARCHcode(&tab_PG, code);
                if (pg != NULL) {
                    PRINTstatsfinali(pg);
                } else {
                    printf("Personaggio non trovato\n");
                }
                break;
            }

            case 6:
                PRINTdetails(&tab_inv);
                break;

            case 0:
                printf("Uscita...\n");
                break;

            default:
                printf("Scelta non valida\n");
        }
    } while (choice != 0);

    FREEpersonaggi(&tab_PG);
    FREEinv(&tab_inv);

    return 0;
}
