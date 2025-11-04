#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(char *filename, int *nr, int *nc);
void separa(int **mat_ptr, int nr, int nc, int **bianchi, int **neri, int *dim_b, int *dim_n);

int main(){

    int nr, nc, dim_b, dim_n;
    int *bianchi = NULL, *neri = NULL;

    int **mat_ptr = malloc2dR("mat.txt", &nr, &nc);
    separa(mat_ptr, nr, nc, &bianchi, &neri, &dim_b, &dim_n);

    printf("Le caselle bianche sono: ");
    for (int i = 0; i < dim_b; i++)
        printf("%d ", bianchi[i]);
    printf("\nLe caselle nere sono: ");
    for (int j = 0; j< dim_n; j++)
        printf("%d ", neri[j]);

    free(bianchi);
    free(neri);

    for (int i = 0; i< nr; i++)
            free(mat_ptr[i]);
    free(mat_ptr);

return 0;
}

int **malloc2dR(char *filename, int *nr, int *nc) {
    FILE *fin = fopen(filename, "r");

    fscanf(fin,"%d %d ", nr, nc);

    //allocazione dinamica della matrice
    int **mat_ptr = malloc(*nr*sizeof(int*));
    for (int i = 0; i < *nr; i++){
        mat_ptr[i] =(int*) malloc(*nc*sizeof(int));
    }

    for (int i = 0; i < *nr; i++) {  //assegno valori a mat_ptr
        for (int j = 0; j < *nc; j++)
            fscanf(fin, "%d ", &mat_ptr[i][j]);    //righe interne, colonne esterne
    }
    fclose(fin);
    return mat_ptr;
}

void separa(int **mat_ptr, int nr, int nc, int **bianchi, int **neri, int *dim_b, int *dim_n) {
    int k = 0, q = 0;
    *dim_b = (nr*nc + 1) / 2;
    *dim_n = nr*nc / 2;
    *bianchi = malloc(*dim_b*sizeof(int));
    *neri = malloc(*dim_n*sizeof(int));
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++)
            if ((i+j)%2 == 0)
                (*bianchi)[k++] = mat_ptr[i][j];    //PRECEDENZA OPERATORI!!!
            else (*neri)[q++] = mat_ptr[i][j];  //PRECEDENZA OPERATORI!!!
    }
}
