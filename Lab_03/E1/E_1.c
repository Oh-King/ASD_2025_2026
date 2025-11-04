#include <stdio.h>
#include <stdlib.h>

int majority(int *vet, int N);
int check(int *vet, int l, int r);
int main() {
    int N;
    int *vet = NULL;

    printf("Inserisci il valore di N:");
    scanf(" %d", &N);
    vet = malloc(N*sizeof(int));

    for (int i = 0; i < N; i++) {
        printf("Inserisci il valore %d del vettore:", i+1);
        scanf("%d", &vet[i]);
    }

    int res = majority(vet, N);
    printf("L'elemento maggioritario corrisponde a: %d", res);
    return 0;
}

int majority(int *vet, int N) {
    int l = 0, r = N-1, count = 0;
    int val = check(vet, l, r);
    for (int i = 0; i < N; i++) {
        if (vet[i] == val) count++;
    }
    if (count > N/2) return val;
    else printf("Non c'è elemento maggioritario");
    return -1;
}

int check(int *vet, int l, int r) {
    int occ_u = 0, occ_v = 0;
    int mid = (l+r)/2;
    if (l >= r) return vet[l];
    int u = check(vet, l, mid);
    int v = check(vet, mid+1, r);
    for (int i = l; i <= r; i++) {
        if (vet[i] == u) occ_u++;
        if (vet[i] == v) occ_v++;
    }
    if (occ_u > occ_v) return u;
    return v;
}