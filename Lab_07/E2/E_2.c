#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEM 5
#define MAX_DIAG 3

typedef struct {
    char name[101];
    int typo, //se == 2 acrobatico avanti, == 1 acrobatico indietro, == 0 transizione
    dir_in, dir_ex, // == 1 frontalmente, == 0 di spalle
    prec, // == 0 primo in sequenza, == 1 preceduto da altro elemento
    fin,  // == 1 non ha elementi dopo, == 0 può avere elementi dopo
    diff; // difficoltà ELEMENTO SINGOLO
    float score; //punteggio ottenuto per corretta esecuzione
}elem_t;

typedef struct {
    int n_elem;
    elem_t* V_elem;
}diag_t;

typedef struct node_t {
    struct node_t* next;
    diag_t diag;
}node_t;

typedef node_t *link;

elem_t* leggi_file();
void solve();
link NEWnode(link succ, diag_t diagonale);

int main(void) {

    return 0;
}

elem_t* leggi_file() {
    FILE *fp = fopen("elementi.txt", "r");
    int N;
    int i = 0;
    fscanf(fp, "%d", &N);
    elem_t *elements = (elem_t*)malloc(N*sizeof(elem_t));
    while (fscanf(fp, "%s %d %d %d %d %d %f %d",
        elements[i].name,
        &elements[i].typo,
        &elements[i].dir_in,
        &elements[i].dir_ex,
        &elements[i].prec,
        &elements[i].fin,
        &elements[i].score,
        &elements[i].diff) == 8) i++;
    return elements;
}



link NEWnode(link succ, diag_t diagonale) {
    link node = malloc(sizeof(node_t));
    if (node == NULL ) return NULL;
    node->next = succ;
    node->diag = diagonale;
    return node;
}



link disp_list(elem_t *elements, int pos, int max_el, elem_t *curr_diag,int cnt) {
    link head = NULL;

    return head;
}

void solve() {
    elem_t *elements = leggi_file();
    disp_list(elements, 0, 1, diag, cnt);
    disp_list(elements, 0, 2, diag, cnt);
    disp_list(elements, 0, 3, diag, cnt);
    disp_list(elements, 0, 4, diag, cnt);
    disp_list(elements, 0, 5, diag, cnt);

    free(elements);
}
