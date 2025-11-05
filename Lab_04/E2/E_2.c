#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 256

typedef struct {
    int n_songs;
    char **songs;
}amico_t;


amico_t* setNfillVect(char *filename, int *n_amici);
int comb(int pos, amico_t *val, char **sol, int n, int k);

int print_counter = 1;

int main(void) {
    int n_amici;
    amico_t *amici = setNfillVect("brani.txt", &n_amici);
    char **sol = malloc(n_amici * sizeof(char*));
    for (int i = 0; i < n_amici; i++)
        sol[i] = malloc(MAXL*sizeof(char));

    comb(0, amici, sol, n_amici, n_amici);

    for (int i = 0; i < n_amici; i++) {
        free(sol[i]);
    }
    free(sol);
    for (int j = 0; j < n_amici; j++) {
        for (int k = 0; k < amici[j].n_songs; k++)
            free(amici[j].songs[k]);
        free(amici[j].songs);
    }
    free(amici);
    return 0;
}

amico_t* setNfillVect(char *filename, int *n_amici) {

    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", n_amici);
    amico_t *amici =(amico_t*)malloc(*n_amici*sizeof(amico_t));
    for (int i = 0; i < *n_amici; i++) {
        fscanf(fp, "%d", &amici[i].n_songs);
        amici[i].songs = malloc(amici[i].n_songs*sizeof(char*));
        for (int j = 0; j < amici[i].n_songs; j++) {
            amici[i].songs[j] = malloc(MAXL*sizeof(char));
            fscanf(fp, "%s", amici[i].songs[j]);
        }
    }
    fclose(fp);
    return amici;
}

int comb(int pos, amico_t *val, char **sol, int n, int k) {
    int i;
    if (pos >= k) {
        printf("%d. ", print_counter);
        for (i=0; i < k; i++) {
            if (i == k-1) printf("%s", sol[i]);
            else printf("%s - ", sol[i]);
        }
        printf("\n");
        print_counter++;
        return 0;
    }
    for (i = 0; i < val[pos].n_songs; i++) {
        strcpy(sol[pos], val[pos].songs[i]);
        comb(pos+1, val, sol, n, k);
    }
    return 0;
}
