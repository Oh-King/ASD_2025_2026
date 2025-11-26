#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
}attivita_t;

attivita_t* leggi_file(char* filename, int *n_att);
void attSEL(int N, attivita_t *seq);
void solve(int N, attivita_t curr_att, attivita_t *seq, int *mark, int *best, int curr_val, int pos, int *max);

bool isOK(attivita_t att1, attivita_t att2);

int main(void) {
    int n_att;
    attivita_t *seq = leggi_file("att.txt", &n_att);
    attSEL(n_att, seq);
    free(seq);
    return 0;
}

attivita_t* leggi_file(char* filename, int *n_att) {

    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", n_att);
    attivita_t *seq = malloc(*n_att*sizeof(attivita_t));
    for (int i = 0; i < *n_att; i++) fscanf(fp, "%d %d", &seq[i].start, &seq[i].end);
    return seq;
}

bool isOK(attivita_t att1, attivita_t att2) {
    if ((att1.start < att2.end) && (att2.start < att1.end)) return false;
    return true;
}

void attSEL(int N, attivita_t *seq) {
    int max = -1, i;
    int *mark = calloc(N, sizeof(int));
    int *best = calloc(N, sizeof(int));

    for (i = 0; i < N; i++) {
        int curr_val = 0;
        mark[i] = 1;
        curr_val += (seq[i].end - seq[i].start);
        if (curr_val > max ) max = curr_val;
        solve(N, seq[i], seq, mark, best, curr_val, i+1, &max);
        mark[i] = 0;
    }
    //print
    printf("La durata massima corrisponde a: %d\n", max);
    printf("Un sottoinsieme che ha durata massima:\n");
    printf("{");
    for (i = 0; i < N; i++) {
        if (best[i] == 1) printf("(%d, %d) ", seq[i].start, seq[i].end);
    }
    printf("}");
    free(mark);
    free(best);
}

void solve(int N, attivita_t curr_att, attivita_t *seq, int *mark, int *best, int curr_val, int pos, int *max) {
    int j;
    for (j = pos; j < N; j++)
        if (isOK(curr_att, seq[j]) != true) {
            continue;
        }
        else {
            curr_val += (seq[j].end - seq[j].start);
            mark[j] = 1;
            if (curr_val > *max) {
                *max = curr_val;
                for (int k = 0; k < N; k++) best[k] = mark[k];
            }
            solve(N, seq[j], seq, mark, best, curr_val, j+1, max);
            curr_val -= (seq[j].end - seq[j].start) ;
            mark[j] = 0;
        }
    return ;
}

