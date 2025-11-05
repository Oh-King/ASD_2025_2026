#include <stdio.h>
#include <stdlib.h>

#define MAXL 256

typedef struct {
    int n_songs;
    char **songs;
}amico_t;

int disp(int pos,int *val,int *sol,int *mark, int n, int k,int cnt);
amico_t* setVect(char *filename, int *n_amici);

int main(void) {
    int n_amici;
    amico_t *amici = setVect("brani.txt", &n_amici);

    free(amici);
    return 0;
}

amico_t* setVect(char *filename, int *n_amici) {

    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", n_amici);
    amico_t *amici =(amico_t*)malloc(*n_amici*sizeof(int));
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

int disp(int pos,int *val,int *sol,int *mark, int n, int k,int cnt){
    int i;
    if (pos >= k){
        for (i=0; i<k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i=0; i<n; i++){
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            cnt = disp(pos+1, val, sol, mark, n, k,cnt);
            mark[i] = 0;
        }
    }
    return cnt;
}
