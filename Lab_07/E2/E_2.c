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

int gen_diag(int n, int k, int pos, diag_t curr_diag, elem_t *elements,node_t *node, node_t *tail, int count, int last_dir) {
    int i;  //nuovo nodo in caso servisse
    if (pos >= k) {  //vuol dire che la diagonale corrente ha raggiunto la cardinalità massima
        tail->next = NEWnode(NULL, curr_diag);
        node = tail;
        tail = tail->next;
        return count+1;
    }
    for (i = 0; i < n; i++) {
        if (elements[i].dir_in == last_dir && (pos == 0 ? elements[i].prec == 0 : 1)) {
            curr_diag.V_elem[pos] = elements[i];
            curr_diag.n_elem = pos +1;
            if (elements[i].fin == 1) {
                node->next = NEWnode(NULL, curr_diag);
                count++;
            }else {
                count = gen_diag(n, k, pos+1, curr_diag, elements, node, tail, count, elements[i].dir_ex);
            }
        }
    }
    return count;
}
