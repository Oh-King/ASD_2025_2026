#include "Graph.h"
#include "ST.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <file_grafo>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        printf("Errore apertura file\n");
        return 1;
    }
    Graph G = GRAPHinit(50); // capacità iniziale
    GRAPHload(fin, G);
    fclose(fin);

    printf("=== GRAFO ===\n");
    GRAPHstore(G, stdout);
    char n1[MAXC], n2[MAXC], n3[MAXC];
    printf("\nInserisci 3 vertici: ");
    scanf("%s %s %s", n1, n2, n3);

    int id1 = GRAPHgetIndex(G, n1);
    int id2 = GRAPHgetIndex(G, n2);
    int id3 = GRAPHgetIndex(G, n3);

    if (id1 == -1 || id2 == -1 || id3 == -1) {
        printf("Almeno un nome non esiste.\n");
        return 0;
    }

    printf("--- MATRICE ---\n");
    if (GRAPHcheck3_M(G, id1, id2, id3))
        printf("I tre vertici formano un sottografo completo.\n");
    else
        printf("I tre vertici non formano un sottografo completo.\n");

    GRAPHlistCreate(G);
    printf("--- LISTA ---\n");
    if (GRAPHckeck3_L(G, id1, id2, id3))
        printf("I tre vertici formano un sottografo completo.\n");
    else
        printf("I tre vertici non formano un sottografo completo.\n");
    return 0;
}
