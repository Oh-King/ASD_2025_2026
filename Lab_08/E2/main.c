#include "Graph.h"
#include "ST.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <file_grafo>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        printf("Errore apertura file\n");
        return 1;
    }
    Graph G = GRAPHinit(50);
    GRAPHload(fin, G);
    fclose(fin);

    int scelta = -1;

    while (scelta != 0) {
        printf("\n=== MENU ===\n");
        printf("1) Stampa vertici e adiacenze (ordine alfabetico)\n");
        printf("2) Verifica sottografo completo (matrice)\n");
        printf("3) Genera lista di adiacenza\n");
        printf("4) Verifica sottografo completo (lista)\n");
        printf("0) Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        if (scelta == 1) {
            GRAPHstore(G, stdout);
        }

        else if (scelta == 2) {
            char a[MAXC], b[MAXC], c[MAXC];
            printf("Inserisci 3 vertici: ");
            scanf("%s %s %s", a, b, c);
            int id1 = GRAPHgetIndex(G, a);
            int id2 = GRAPHgetIndex(G, b);
            int id3 = GRAPHgetIndex(G, c);
            if (id1 == -1 || id2 == -1 || id3 == -1)
                printf("Errore: nome non trovato\n");
            else if (GRAPHcheck3_M(G, id1, id2, id3))
                printf("Formano un sottografo completo\n");
            else
                printf("NON formano un sottografo completo\n");
        }
        else if (scelta == 3) {
            GRAPHlistCreate(G);
            printf("Lista di adiacenza generata\n");
        }
        else if (scelta == 4) {
            char a[MAXC], b[MAXC], c[MAXC];
            printf("Inserisci 3 vertici: ");
            scanf("%s %s %s", a, b, c);
            int id1 = GRAPHgetIndex(G, a);
            int id2 = GRAPHgetIndex(G, b);
            int id3 = GRAPHgetIndex(G, c);
            if (id1 == -1 || id2 == -1 || id3 == -1)
                printf("Errore: nome non trovato\n");
            else if (GRAPHcheck3_L(G, id1, id2, id3))
                printf("Formano un sottografo completo\n");
            else
                printf("NON formano un sottografo completo\n");
        }
    }
    return 0;
}
