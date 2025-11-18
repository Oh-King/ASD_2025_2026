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
    tile_t *best_sol;
    tessera_t *tile_vett;
    int *mark;
    int N, R, C;
}parameters;

void setNfill_param(parameters *parametri);
void wrap(parameters *parametri);
void solve(parameters *parametri, int pos, int *max);
int calc_score(parameters *parametri);
void print_board(parameters *parametri);

int main(void) {
    parameters parametri;
    setNfill_param(&parametri);
    wrap(&parametri);

    // Libera memoria
    free(parametri.mark);
    free(parametri.tile_vett);
    free(parametri.best_sol);
    for (int i = 0; i < parametri.R; i++) {
        free(parametri.board[i]);
    }
    free(parametri.board);

    return 0;
}

void setNfill_param(parameters *parametri) {
    int i= 0;
    FILE *fp = fopen("tiles.txt", "r");
    if (fp == NULL) {
        printf("Errore apertura tiles.txt\n");
        exit(1);
    }
    fscanf(fp, "%d", &(parametri->N));

    parametri->mark =(int*)calloc(parametri->N, sizeof(int));
    parametri->tile_vett = (tessera_t*)malloc(parametri->N*sizeof(tessera_t));

    while (fscanf(fp," %c %d %c %d",
        &(parametri->tile_vett[i].color1), &(parametri->tile_vett[i].val1),
        &(parametri->tile_vett[i].color2), &(parametri->tile_vett[i].val2)) == 4) {
        i++;
    }
    fclose(fp);

    fp = fopen("board.txt","r");
    if (fp == NULL) {
        printf("Errore apertura board.txt\n");
        exit(1);
    }
    if (fscanf(fp, "%d%d", &(parametri->R), &(parametri->C)) != 2) {
        printf("Errore lettura board.txt\n");
        exit(1);
    }

    parametri->board = (tile_t**) malloc(parametri->R*sizeof(tile_t*));
    for (int k = 0; k < parametri->R; k++) {
        parametri->board[k] = (tile_t*)malloc(parametri->C*sizeof(tile_t));
    }
    parametri->best_sol = (tile_t*)malloc(parametri->R * parametri->C * sizeof(tile_t));

    // Inizializza best_sol
    for (int idx = 0; idx < parametri->R * parametri->C; idx++) {
        parametri->best_sol[idx].tile_id = -1;
        parametri->best_sol[idx].rotation = -1;
    }

    // Inizializza board a -1
    for (int k = 0; k < parametri->R; k++) {
        for (int j = 0; j < parametri->C; j++) {
            parametri->board[k][j].tile_id = -1;
            parametri->board[k][j].rotation = -1;
        }
    }

    // Leggi le celle pre-riempite
    for (int k = 0; k < parametri->R; k++) {
        for (int j = 0; j < parametri->C; j++) {
            int tile_id, rotation;
            fscanf(fp, "%d/%d", &tile_id, &rotation);
            if (tile_id != -1) {
                parametri->board[k][j].tile_id = tile_id;
                parametri->board[k][j].rotation = rotation;
                parametri->mark[tile_id] = 2;
            }
        }
    }
    fclose(fp);
}

void wrap(parameters *parametri) {
    int pos = 0, max = -1;
    solve(parametri, pos, &max);
    printf("Il punteggio massimo raggiunto corrisponde a: %d\n", max);
    printf("Con la seguente configurazione:\n");
    print_board(parametri);
}

void solve(parameters *parametri, int pos, int *max) {
    if (pos >= (parametri->R)*(parametri->C)) {
        int curr_score = calc_score(parametri);
        if (curr_score > *max) {
            *max = curr_score;
            // Salvo la soluzione migliore
            for (int i = 0; i < parametri->R * parametri->C; i++) {
                int r = i / parametri->C;
                int c = i % parametri->C;
                parametri->best_sol[i] = parametri->board[r][c];
            }
        }
        return;
    }

    int pos_r = pos / parametri->C;
    int pos_c = pos % parametri->C;

    // Se la cella è già occupata, salta
    if(parametri->board[pos_r][pos_c].tile_id != -1){
        solve(parametri, pos+1, max);
        return;
    }

    // Prova tutte le tessere disponibili
    for (int i = 0; i < parametri->N; i++) {
        if (parametri->mark[i] == 0) {
            parametri->mark[i] = 1;
            parametri->board[pos_r][pos_c].tile_id = i;

            // Prova senza rotazione
            parametri->board[pos_r][pos_c].rotation = NFLIP;
            solve(parametri, pos+1, max);

            // Prova con rotazione
            parametri->board[pos_r][pos_c].rotation = FLIP;
            solve(parametri, pos+1, max);

            // Backtracking
            parametri->board[pos_r][pos_c].rotation = -1;
            parametri->board[pos_r][pos_c].tile_id = -1;
            parametri->mark[i] = 0;
        }
    }
}

int calc_score(parameters *parametri){
    int score = 0, row, col;

    // Calcolo punteggio per righe (tubi orizzontali)
    for (row = 0; row < parametri->R; row++) {
        tessera_t t0 = parametri->tile_vett[parametri->board[row][0].tile_id];
        char color = (parametri->board[row][0].rotation == NFLIP) ? t0.color1 : t0.color2;
        int ok = 1;
        int row_score = 0;

        for (col = 0; col < parametri->C; col++) {
            tessera_t t = parametri->tile_vett[parametri->board[row][col].tile_id];
            char curr_color = (parametri->board[row][col].rotation == NFLIP) ? t.color1 : t.color2;
            int curr_val = (parametri->board[row][col].rotation == NFLIP) ? t.val1 : t.val2;

            if (curr_color != color) {
                ok = 0;
                break;
            }
            row_score += curr_val;
        }
        if (ok == 1) score += row_score;
    }

    // Calcolo punteggio per colonne (tubi verticali)
    for (col = 0; col < parametri->C; col++) {
        tessera_t t0 = parametri->tile_vett[parametri->board[0][col].tile_id];
        char color = (parametri->board[0][col].rotation == NFLIP) ? t0.color2 : t0.color1;
        int ok = 1;
        int col_score = 0;

        for (row = 0; row < parametri->R; row++) {
            tessera_t t = parametri->tile_vett[parametri->board[row][col].tile_id];
            char curr_color = (parametri->board[row][col].rotation == NFLIP) ? t.color2 : t.color1;
            int curr_val = (parametri->board[row][col].rotation == NFLIP) ? t.val2 : t.val1;

            if (curr_color != color) {
                ok = 0;
                break;
            }
            col_score += curr_val;
        }
        if (ok == 1) score += col_score;
    }

    return score;
}

void print_board(parameters *parametri) {
    for (int r = 0; r < parametri->R; r++) {
        for (int c = 0; c < parametri->C; c++) {
            int idx = r * parametri->C + c;
            printf("%d/%d ", parametri->best_sol[idx].tile_id, parametri->best_sol[idx].rotation);
        }
        printf("\n");
    }
}
