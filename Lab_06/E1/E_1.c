#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
}attivita_t;

void MergeSort(attivita_t *V, int N);
void MergeSortR(attivita_t *V, attivita_t *aus, int l, int r);
void Merge(attivita_t *V, attivita_t *aus, int l, int mid, int r);

int main(void) {

    return 0;
}

void MergeSort(attivita_t *V, int N) {
    attivita_t aus[N];
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
        else if (ITEMlt(A[i], A[j]) || ITEMeq(A[i], A[j]))
            aus[k] = V[i++];
        else
            aus[k] = V[j++];
    for ( k = l; k <= r; k++ )
        V[k] = aus[k];
    return;
}

bool isLESSorEQ(attivita_t att1, attivita_t att2) {
    if ((att1.end - att1.start) <= (att2.end - att2.start)) return true;
    return false;

}