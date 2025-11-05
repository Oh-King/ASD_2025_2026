#include <stdio.h>
#include <stdlib.h>

#define MAXL 256

int disp(int pos,int *val,int *sol,int *mark, int n, int k,int cnt);
void leggi_file(char *filename, int *n_amici, char ***songs_ptr);

int main(void) {

    int n_amici;
    char ***songs_ptr;

    return 0;
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