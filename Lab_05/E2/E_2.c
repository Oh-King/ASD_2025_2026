#include <stdio.h>
#include <stdlib.h>

#define EMPTY (-1)
#define NFLIP 0
#define FLIP 1

typedef enum {not_flip, flip} rot_t;

typedef struct {
    char color1, color2;
    int val1, val2;
}tessera_t;

typedef struct {
    int tile_id;
    int rotation;
}tile_t;

typedef struct {
    tile_t **board;
    tessera_t *tile_vett;
    int *mark;
    int N, R, C;
}parameters;

void setNfill_param(parameters *parametri);
void solve(parameters *parametri, int index, int max);

int main(void) {

    return 0;
}

void setNfill_param(parameters *parametri) {
    FILE *fp = fopen("tiles.txt", "r");     //lettura di tiles.txt e riempimento vettore
    fscanf(fp, "%d", &(parametri->N));
    parametri->mark =(int*)calloc(parametri->N, sizeof(int));
    parametri->tile_vett = (tessera_t*)malloc(sizeof(tessera_t));
    while (fscanf(fp,"%c%d%c%d",
        &(parametri->tile_vett->color1), &(parametri->tile_vett->val1),
        &(parametri->tile_vett->color2), &(parametri->tile_vett->val2)) == 4) {
    }
    fclose(fp);
    fp = fopen("board.txt","r");
    if (fscanf(fp, "%d%d", &(parametri->R), &(parametri->C)) != 2) printf("Errore lettura board.txt");
    else {
        parametri->board = (tile_t**) malloc(parametri->R*sizeof(tile_t*));
        for (int i = 0; i < parametri->R; i++) {
            parametri->board[i] = (tile_t*)malloc(parametri->C*sizeof(tile_t));
        }
        int index = 0;
        for (int k = 0; k < parametri->R; k++) {
            for (int j = 0; j < parametri->C; j++) {
                fscanf(fp, "%d/%d", &(parametri->board[k][j].tile_id), &(parametri->board[k][j].rotation));
                if (parametri->board[k][j].tile_id != -1) parametri->mark[index++] = 2; //inizializzo a 2 per segnalare
                //che sono le tessere della configurazione iniziale, poi segnerò a 1 quelli di volta in volta selezionati
                else index++;
            }
        }
    }
    fclose(fp);
}

void solve(parameters *parametri, int index, int pos, int max) {
    if (pos >= index) {
        printf("Il punteggio massimo raggiunto corrisponde a:%d\n", max);
        printf("Con la seguente configurazione:\n");
        for (int i = 0; i < parametri->R; i++) {
            for (int j = 0; j < parametri->C; j++) {
                printf("%d/%d", parametri->board[i][j].tile_id, parametri->board[i][j].rotation);
            }
            printf("\n");
        }
    }
    else {

    }
}

