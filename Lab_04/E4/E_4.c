/*
 * Z -> Z/R
 * R -> T/S
 * T -> Z/R
 * S -> T/S
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    int n_jewels;
    int *ord_pietre;
}collana_t;

typedef struct {
    int val;
    int n_jewels;
}jewels_t;

typedef enum {Z, R, T, S} stones_conv;

void leggi_file(char *filename, jewels_t gioielli[4]);
void solve(jewels_t* gioielli, int index);
void solve_r(jewels_t gioielli[4], collana_t *sol, collana_t* best, int last_choice, int cons, int n_smr, int n_zaf);
bool check(jewels_t gioielli[4], int last_choice);

int max_rip;

int main(void) {
    FILE *fp = fopen("test_set.txt", "r");
    if (fp == NULL ) return -1;
    int n_test;
    fscanf(fp, "%d", &n_test);
    jewels_t gioielli[4];
    //leggi_file("test_set.txt", gioielli);
    for (int index = 0; index < n_test; index++) {
        fscanf(fp, "%d%d%d%d%d%d%d%d%d",
        &gioielli[Z].n_jewels, &gioielli[R].n_jewels, &gioielli[T].n_jewels, &gioielli[S].n_jewels,
        &gioielli[Z].val, &gioielli[R].val, &gioielli[T].val, &gioielli[S].val, &max_rip);
       solve(gioielli, index+1);
    }
    fclose(fp);
    return 0;
}

void leggi_file(char *filename, jewels_t gioielli[4]) {
    FILE *fp = fopen(filename, "r");
    int n_test;
    fscanf(fp, "%d", &n_test);
    fscanf(fp, "%d%d%d%d%d%d%d%d%d",
        &gioielli[Z].n_jewels, &gioielli[R].n_jewels, &gioielli[T].n_jewels, &gioielli[S].n_jewels,
        &gioielli[Z].val, &gioielli[R].val, &gioielli[T].val, &gioielli[S].val, &max_rip);
    fclose(fp);
}

void solve(jewels_t gioielli[4], int index) {
    int dim = gioielli[Z].n_jewels + gioielli[R].n_jewels + gioielli[T].n_jewels + gioielli[S].n_jewels;
    collana_t sol, best;
    sol.value = 0;
    sol.n_jewels = 0;
    sol.ord_pietre = malloc(dim*sizeof(int));
    best.value = 0;
    best.n_jewels = 0;
    best.ord_pietre = malloc(dim*sizeof(int));

    //Funzione ricorsiva
    solve_r(gioielli, &sol, &best, -1, 0, 0, 0);
    printf("Per il test case n: %d, abbiamo i seguenti risultati:\n", index);
    printf("Lunghezza massima: %d pietre\n", best.n_jewels);
    printf("Valore max: %d\n", best.value);
    printf("Ordine:\n");
    printf("-");
    for (int i = 0; i < best.n_jewels; i++) {
        char pietra;
        switch(best.ord_pietre[i]) {
            case Z: pietra = 'Z'; break;
            case R: pietra = 'R'; break;
            case T: pietra = 'T'; break;
            case S: pietra = 'S'; break;
            default: pietra = '?'; break;
        }
        printf("%c-", pietra);
    }
    printf("\n");
    //Libero memoria
    free(sol.ord_pietre);
    free(best.ord_pietre);
}

void solve_r(jewels_t gioielli[4], collana_t *sol, collana_t *best, int last_choice, int cons, int n_smr, int n_zaf) {
    //verifica del max_rip
    if (sol->value > best->value) {
        //soluzione migliore
        best->n_jewels = sol->n_jewels;
        best->value = sol->value;
        for (int i = 0; i < sol->n_jewels; i++) {
            best->ord_pietre[i] = sol->ord_pietre[i];
        }
    }
    if (last_choice == -1) { //caso pietra 0
        for (int j = 1; j < 4; j++) {   //non parto da 0 perché gli zaffiri non possono superare gli smeraldi
            if (gioielli[j].n_jewels > 0) {
                gioielli[j].n_jewels--;
                sol->value += gioielli[j].val;
                sol->ord_pietre[sol->n_jewels] = j;
                sol->n_jewels++;
                solve_r(gioielli, sol, best, j, 1, j == 3 ? 1 : 0, 0); //ricorro, prima volta che uso questa pietra
                gioielli[j].n_jewels++; //backtracking
                sol->n_jewels--;
                sol->value -= gioielli[j].val;
            }
        }
    }else if (check(gioielli, last_choice) == true) {
        if (last_choice == Z || last_choice == T) {
            if ((gioielli[Z].n_jewels > 0) && (last_choice != Z || cons < max_rip ) && (n_zaf+1 <= n_smr)){
                gioielli[Z].n_jewels--;
                sol->ord_pietre[sol->n_jewels] = Z;
                sol->n_jewels++;
                sol->value += gioielli[Z].val;
                solve_r(gioielli, sol, best, Z, last_choice == Z ? cons+1 : 1, n_smr, n_zaf+1);
                gioielli[Z].n_jewels++;
                sol->n_jewels--;
                sol->value -= gioielli[Z].val;
            }
            if (gioielli[R].n_jewels > 0 ) {
                gioielli[R].n_jewels--;
                sol->ord_pietre[sol->n_jewels] = R;
                sol->n_jewels++;
                sol->value += gioielli[R].val;
                solve_r(gioielli, sol, best, R, last_choice == R ? cons+1 : 1, n_smr, n_zaf);
                gioielli[R].n_jewels++;
                sol->n_jewels--;
                sol->value -= gioielli[R].val;
            }
        }
        else{  //caso in cui last_choice = S o last_choice = T
            if (gioielli[S].n_jewels > 0 && (last_choice != S || cons < max_rip)) {
                gioielli[S].n_jewels--;
                sol->ord_pietre[sol->n_jewels] = S;
                sol->n_jewels++;
                sol->value += gioielli[S].val;
                solve_r(gioielli, sol, best, S, last_choice == S ? cons+1 : 1, n_smr+1, n_zaf);
                gioielli[S].n_jewels++;
                sol->n_jewels--;
                sol->value -= gioielli[S].val;
            }
            if (gioielli[T].n_jewels > 0) {
                gioielli[T].n_jewels--;
                sol->ord_pietre[sol->n_jewels] = T;
                sol->n_jewels++;
                sol->value += gioielli[T].val;
                solve_r(gioielli, sol, best, T, last_choice == T ? cons+1 : 1, n_smr, n_zaf);
                gioielli[T].n_jewels++;
                sol->n_jewels--;
                sol->value -= gioielli[T].val;
            }
        }
    }
}
bool check(jewels_t gioielli[4], int last_choice){
    if (last_choice == Z || last_choice == T) {
        if (gioielli[Z].n_jewels > 0 || gioielli[R].n_jewels > 0) return true;
    }else if (last_choice == R || last_choice == S) {
        if (gioielli[S].n_jewels > 0 || gioielli[T].n_jewels > 0) return true;
    }
    return false;
}