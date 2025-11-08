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
    int n_jewels;
    int *ord_pietre;
}collana_t;

typedef enum {Z, R, T, S} stones_conv;

void leggi_file(char *filename, int gioielli[4]);
void solve(int* gioielli, int index);
void solve_r(int gioielli[4], collana_t *sol, collana_t* best, int last_choice);
bool check(int gioielli[4], int last_choice);

int main(void) {

    int gioielli[4];
    //leggi_file("hard_test_set.txt", gioielli);
    FILE *fp = fopen("easy_test_set.txt", "r");
    if (fp == NULL) return -1;
    int n_test;
    fscanf(fp, " %d ", &n_test);
    for (int k = 0; k < n_test; k++) {
        fscanf(fp, "%d %d %d %d", &gioielli[Z], &gioielli[R], &gioielli[T], &gioielli[S]);
        solve(gioielli, k+1);
    }
    fclose(fp);

    return 0;
}

void leggi_file(char *filename, int gioielli[4]) {
    FILE *fp = fopen(filename, "r");
    int n_test;
    fscanf(fp, " %d ", &n_test);
    fscanf(fp, "%d %d %d %d", &gioielli[Z], &gioielli[R], &gioielli[T], &gioielli[S]);
    fclose(fp);
}

void solve(int gioielli[4], int index) {
    int dim = gioielli[Z] + gioielli[R] + gioielli[T] + gioielli[S];
    collana_t sol, best;
    sol.n_jewels = 0;
    sol.ord_pietre = malloc(dim*sizeof(int));
    best.n_jewels = 0;
    best.ord_pietre = malloc(dim*sizeof(int));

    //Funzione ricorsiva
    solve_r(gioielli, &sol, &best, -1);
    printf("Soluzioni test case n:%d\n", index);
    printf("Lunghezza massima: %d pietre\n", best.n_jewels);
    printf("Ordine:\n");
    for (int i = 0; i < best.n_jewels; i++) {
        char pietra;
        switch(best.ord_pietre[i]) {
            case Z: pietra = 'Z'; break;
            case R: pietra = 'R'; break;
            case T: pietra = 'T'; break;
            case S: pietra = 'S'; break;
            default: pietra = '?'; break;
        }
        printf("%c ", pietra);
    }
    printf("\n");
    //Libero memoria
    free(sol.ord_pietre);
    free(best.ord_pietre);
}

void solve_r(int gioielli[4], collana_t *sol, collana_t *best, int last_choice) {
    if (sol->n_jewels > best->n_jewels) {
        //soluzione migliore
        best->n_jewels = sol->n_jewels;
        for (int i = 0; i < sol->n_jewels; i++) {
            best->ord_pietre[i] = sol->ord_pietre[i];
            }
        }
        if (last_choice == -1) { //caso pietra 0
            for (int j = 0; j < 4; j++) {
                if (gioielli[j] > 0) {
                    gioielli[j]--;
                sol->ord_pietre[sol->n_jewels] = j;
                sol->n_jewels++;
                solve_r(gioielli, sol, best, j); //ricorro
                gioielli[j]++; //backtracking
                sol->n_jewels--;
                }
            }
        }else if (check(gioielli, last_choice) == true) {
            if (last_choice == Z || last_choice == T) {
                if (gioielli[Z] > 0) {
                    gioielli[Z]--;
                    sol->ord_pietre[sol->n_jewels] = Z;
                    sol->n_jewels++;
                    solve_r(gioielli, sol, best, Z);
                    gioielli[Z]++;
                    sol->n_jewels--;
            }
            if (gioielli[R] > 0) {
                gioielli[R]--;
                sol->ord_pietre[sol->n_jewels] = R;
                sol->n_jewels++;
                solve_r(gioielli, sol, best, R);
                gioielli[R]++;
                sol->n_jewels--;
            }
            }else{
            if (gioielli[S] > 0) {
                gioielli[S]--;
                sol->ord_pietre[sol->n_jewels] = S;
                sol->n_jewels++;
                solve_r(gioielli, sol, best, S);
                gioielli[S]++;
                sol->n_jewels--;
            }
            if (gioielli[T] > 0) {
                gioielli[T]--;
                sol->ord_pietre[sol->n_jewels] = T;
                sol->n_jewels++;
                solve_r(gioielli, sol, best, T);
                gioielli[T]++;
                sol->n_jewels--;
            }
        }
   }
}
bool check(int gioielli[4], int last_choice){
    if (last_choice == Z || last_choice == T) {
        if (gioielli[Z] > 0 || gioielli[R] > 0) return true;
    }else if (last_choice == R || last_choice == S) {
        if (gioielli[S] > 0 || gioielli[T] > 0) return true;
    }
    return false;
}