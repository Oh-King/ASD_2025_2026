#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
}attivita_t;

attivita_t* readNfill();
void MergeSort(attivita_t *V, int N);
void MergeSortR(attivita_t *V, attivita_t *aus, int l, int r);
void Merge(attivita_t *V, attivita_t *aus, int l, int mid, int r);
bool isLESSorEQ(attivita_t att1, attivita_t att2);
bool isOK(attivita_t att1, attivita_t att2);
int FindLastOK(attivita_t *V, int index);
void build(attivita_t *V, int *choice, int i);
void solve(attivita_t *V, int N);

int main(void) {
    int N;
    attivita_t* V = readNfill(&N);
    solve(V, N);
    return 0;
}

attivita_t* readNfill(int *N){
    int i = 0;
    FILE *fp = fopen("att3.txt", "r");
    if(fp == NULL) exit(1);
    fscanf(fp, "%d", N);
    attivita_t* V = (attivita_t*)malloc(*N*sizeof(attivita_t));
    while(fscanf(fp, "%d%d", &V[i].start, &V[i].end) == 2) i++;
    return V;
}

void MergeSort(attivita_t *V, int N) {
    attivita_t* aus = (attivita_t*)malloc(N*sizeof(attivita_t));
    int l = 0;
    int r = N-1;
    MergeSortR(V, aus, l, r);
}

void MergeSortR(attivita_t *V, attivita_t *aus, int l, int r) {
    int mid;
    if (l >= r) return;
    mid = (l+r)/2;
    MergeSortR(V, aus, l, mid);
    MergeSortR(V, aus, mid+1, r);
    Merge(V, aus, l, mid, r);
}

void Merge(attivita_t *V, attivita_t *aus, int l, int mid, int r) {
    int i, j, k;
    i = l;
    j = mid+1;
    for (k = l; k <= r; k++)
        if (i > mid)
            aus[k] = V[j++];
        else if (j > r)
            aus[k] = V[i++];
        else if (isLESSorEQ(V[i], V[j]) == true)
            aus[k] = V[i++];
        else
            aus[k] = V[j++];
    for ( k = l; k <= r; k++ )
        V[k] = aus[k];
    return;
}

bool isLESSorEQ(attivita_t att1, attivita_t att2) {
    if (att1.end <= att2.end) return true;
    return false;
}
bool isOK(attivita_t att1, attivita_t att2) {
    if ((att1.start < att2.end) && (att2.start < att1.end)) return false;
    return true;
}

// Ricostruisce e stampa la soluzione
void build(attivita_t *V, int *choice, int i) {
    if (i < 0) return;  //caso base quando ho finito
    if (choice[i] == -2) {
        //skippa, non l'ho presa
        build(V, choice, i - 1);
    } else {
        build(V, choice, choice[i]);
        // Poi stampa questa
        printf(" (%d, %d) ", V[i].start, V[i].end);
    }
}

void solve(attivita_t *V, int N) {

    MergeSort(V, N);

    int *DP = (int*)malloc(N * sizeof(int));      //memorizzo durate parziali max
    int *choice = (int*)malloc(N * sizeof(int));  //scelte: -1 senza precedenti, -2 non presa, >=0 indice precedente

    DP[0] = V[0].end - V[0].start;  //durata prima attività
    choice[0] = -1;                 //non ha precedenti

    for (int i = 1; i < N; i++) {
        int durata_i = V[i].end - V[i].start;
        int j = FindLastOK(V, i);

        int taken = durata_i + (j >= 0 ? DP[j] : 0);
        int n_taken = DP[i - 1];

        // Scelgo il massimo
        if (taken > n_taken) {
            DP[i] = taken;
            choice[i] = j;  // Prendo i, vengo da j
        } else {
            DP[i] = n_taken;
            choice[i] = -2;  // Non prendo i
        }
    }

    // PASSO 5: Stampa risultato
    printf("========= SOLUZIONE =========\n");
    printf("Durata massima: %d\n", DP[N - 1]);
    printf("Attivita selezionate: [");
    build(V, choice, N - 1);
    printf("]\n");

    free(DP);
    free(choice);
}

int FindLastOK(attivita_t *V, int index) {
    //cerco all'indietro da posizione prima di index
    for (int j = index - 1; j >= 0; j--) {
        if (isOK(V[j], V[index]) == true) {
            return j;
        }
    }
    return -1;  //nessuna attività compatibile trovata
}