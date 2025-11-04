#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    int a, b;
}arco_t;

void powerset(int pos, int *val, int *sol,int n, int start, arco_t *archi, int E);
arco_t* leggi_file(char *filename, int *N, int *E, arco_t *archi);
bool checkNprint(arco_t *archi, int *sol, int pos, int E);


int main(void) {

    int N, E;
    int pos = 0, cnt = 0, start = 0;

    arco_t *archi = NULL;
    int *vertici = NULL;
    char *filename = (char*)malloc(50*sizeof(char));

    //printf("Inserisci il nome del file:");
    //scanf("%s", filename);
    if (filename == NULL ) return -1;

    archi = leggi_file("grafo.txt", &N, &E, archi);
    vertici = (int*)malloc(N*sizeof(int));
    for (int i = 0; i < N; i++) vertici[i] = i;
    int *sol = (int*)malloc((int)pow(2,N)*sizeof(arco_t));

    powerset(pos, vertici, sol, N, start, archi, E);

    free(archi);
    return 0;
}

void powerset(int pos,int *vertici,int *sol,int n,int start, arco_t *archi, int E) {
    int i;
    if (start >= n) {
        checkNprint(archi, sol, pos, E);
        return;
    }
    for (i = start; i < n; i++) {
        sol[pos] = vertici[i];
        powerset(pos+1, vertici, sol, n, i+1, archi, E);   //incremento start nei parametri di powerset
    }
    powerset(pos, vertici, sol, n, n, archi, E); //commento perché tanto sarebbe solo il caso terminale
    //con start = n
    return;
}

arco_t* leggi_file(char *filename, int *N, int *E, arco_t *archi) {
    int i = 0;
    FILE *fp = fopen(filename, "r");

    fscanf(fp, "%d%d", N, E);
    archi = (arco_t*)malloc((*E)*sizeof(arco_t));

    while (fscanf(fp, "%d%d", &archi[i].a, &archi[i].b) == 2) i++;

    fclose(fp);
    return archi;
}

bool checkNprint(arco_t *archi, int *sol, int pos, int E) {
    for (int i = 0; i < E; i++) {
        bool covered = false;
        // Verifica se almeno un vertice in sol copre l'arco i
        for (int j = 0; j < pos; j++) {
            if (sol[j] == archi[i].a || sol[j] == archi[i].b) {
                covered = true;
                break;  //coperto, passo al prossimo
            }
        }
        if (!covered) { //se non è coperto ritorno falso subito
            return false;
        }
    }
    // Tutti gli archi sono coperti
    for (int k = 0; k < pos; k++) {
        printf("%d ", sol[k]);
    }
    printf("\n");
    return true;
}

