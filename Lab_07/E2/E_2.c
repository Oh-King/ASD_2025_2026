#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

elem_t* leggi_file(int *N);
void solve();
link NEWnode(link succ, diag_t diagonale);
bool hasACRO(diag_t diag, int end);
bool checkDIFF(diag_t diag, int end, int DD);
int getDD();
int getDP();
bool checkVALID_PR(diag_t *PR, int DP);
diag_t* gen_vect_diag(int N, link head);
void WRAP_gen_prog(int N, int DP, int DD, diag_t *diag_vett);
int WRAP_gen_diag(int n, elem_t *elements, node_t *head, node_t **tail_ptr, int DD);
int gen_diag(int n, int k, int pos, diag_t curr_diag, elem_t *elements, node_t **tail_ptr, int count, int last_dir, int DD);
float calcSCORE(diag_t *program);

int main(void) {

    solve();

    return 0;
}

elem_t* leggi_file(int *N) {
    FILE *fp = fopen("elementi.txt", "r");
    int i = 0;
    fscanf(fp, "%d", N);
    elem_t *elements = (elem_t*)malloc(*N*sizeof(elem_t));
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

int gen_diag(int n, int k, int pos, diag_t curr_diag, elem_t *elements, node_t **tail_ptr, int count, int last_dir, int DD) {
    int i;

    if (pos >= k) {
        if ((hasACRO(curr_diag, pos) == true) && (checkDIFF(curr_diag, pos, DD) == true)) {
            (*tail_ptr)->next = NEWnode(NULL, curr_diag);
            (*tail_ptr)->next->diag.V_elem = (elem_t*)malloc(k * sizeof(elem_t));
            for (i = 0; i < pos; i++) {
                (*tail_ptr)->next->diag.V_elem[i] = curr_diag.V_elem[i];
            }
            (*tail_ptr)->next->diag.n_elem = pos;
            *tail_ptr = (*tail_ptr)->next;
            return count + 1;
        }
        return count;
    }

    for (i = 0; i < n; i++) {
        if (elements[i].dir_in == last_dir && (pos == 0 ? elements[i].prec == 0 : 1)) {
            curr_diag.V_elem[pos] = elements[i];
            curr_diag.n_elem = pos + 1;

            if (elements[i].fin == 1) {
                if ((hasACRO(curr_diag, pos + 1) == true) && (checkDIFF(curr_diag, pos + 1, DD) == true)) {
                    (*tail_ptr)->next = NEWnode(NULL, curr_diag);
                    (*tail_ptr)->next->diag.V_elem = (elem_t*)malloc(k * sizeof(elem_t));
                    for (int j = 0; j <= pos; j++) {
                        (*tail_ptr)->next->diag.V_elem[j] = curr_diag.V_elem[j];
                    }
                    (*tail_ptr)->next->diag.n_elem = pos + 1;
                    *tail_ptr = (*tail_ptr)->next;
                    count++;
                }
            } else {
                count = gen_diag(n, k, pos + 1, curr_diag, elements, tail_ptr, count, elements[i].dir_ex, DD);
            }
        }
    }
    return count;
}

bool hasACRO(diag_t diag, int end) {
    int i;
    for ( i = 0; i < end; i++) if (diag.V_elem[i].typo != 0) return true;
    return false;
}

bool checkDIFF(diag_t diag, int end, int DD) {
    int i, sum = 0;
    for (i = 0; i < end; i++) sum += diag.V_elem[i].diff;
    if (sum < DD) return true;
    return false;
}

int getDD() {
    int DD;
    printf("Inserisci valore DD:");
    scanf("%d", &DD);
    return DD;
}

int getDP() {
    int DP;
    printf("Inserisci valore DP:");
    scanf("%d", &DP);
    return DP;
}

void gen_prog(diag_t *diag_V, int size, diag_t *curr_prog, diag_t *best_prog,
              int *mark, int pos_diag, float *max_score, int DP, int DD) {
    if (pos_diag >= MAX_DIAG) { //caso base
        if (checkVALID_PR(curr_prog, DP) == false) { //programma provato non è ok
            return;
        }
        float curr_score = calcSCORE(curr_prog); //(N.B)

        if (curr_score > *max_score) { //se curr_score è il migliore, aggiorno max_score
            *max_score = curr_score;
            for (int i = 0; i < MAX_DIAG; i++) { //e copio programma
                best_prog[i] = curr_prog[i];
                best_prog[i].V_elem = malloc(curr_prog[i].n_elem * sizeof(elem_t));
                for (int j = 0; j < curr_prog[i].n_elem; j++) {
                    best_prog[i].V_elem[j] = curr_prog[i].V_elem[j];
                }
            }
        }
        return;
    }
    //ricorsione
    for (int i = 0; i < size; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            curr_prog[pos_diag] = diag_V[i];
            gen_prog(diag_V, size, curr_prog, best_prog, mark, pos_diag + 1,
                     max_score, DP, DD);
            mark[i] = 0;
        }
    }
}

bool checkVALID_PR(diag_t *PR, int DP){ //controllo se il programma è valido
    //CONSIDERO GIA' "CORRETTE" LE DIAGONALI, QUINDI PER I DUE ACROBATICI IN SEQUENZA
    //SUPPONGO USCITA DI PRIMO UGUALE A ENTRATA SECONDO
    //difficoltà minore di DP
    //almeno un acrobatico avanti e uno indietro nel PROGRAMMA
    //almeno due acrobatici in sequenza in una DIAGONALE
    //NON controllo l'ultima casella per il bonus
    int tot_diff = 0;
    int i, j;
    bool front = false, back = false; // alla fine se entrambi veri programma ok e posso vedere punteggio finale
    bool second_seq = false, both_acr_valid = false; //se both_acr_valid = true posso continuare con punteggio
    for(i = 0; i < MAX_DIAG; i++){
        bool first_seq = false;
        for(j = 0; j < PR[i].n_elem; j++){
            tot_diff += PR[i].V_elem[j].diff;
            if(PR[i].V_elem[j].typo != 0){
                if (PR[i].V_elem[j].typo == 1) back = true;
                else front = true;
                if (first_seq == false) first_seq = true;
                else {
                    second_seq = true;
                    both_acr_valid = true;
                }
            }else {
                if(first_seq == true) first_seq = false; //resetto
            }
        }
    }
    if (both_acr_valid == false) return false;
    if((front != true) || (back != true)) return false;
    if (tot_diff <= DP) return true;
    return false;
}

diag_t* gen_vect_diag(int N, link head){
    int i, j;
    link curr_node;
    diag_t* vett = (diag_t*)malloc(N*sizeof(diag_t));
    for(i = 0, curr_node = head; (curr_node != NULL) && (i < N); curr_node = curr_node->next, i++){
        vett[i].n_elem = curr_node->diag.n_elem;
        vett[i].V_elem = (elem_t*)malloc(vett[i].n_elem *sizeof(elem_t));
        for(j = 0; j < vett[i].n_elem; j++) vett[i].V_elem[j] = curr_node->diag.V_elem[j];
    }
    return vett;
}

float calcSCORE(diag_t *program){
    int i, j;
    float total_score = 0;
    for(i = 0; i < MAX_DIAG; i++){
        float diag_score = 0;
        for(j = 0; j < program[i].n_elem; j++){
            diag_score += program[i].V_elem[j].score;
        }
        if((i == 2) && (j == program[i].n_elem)){
            if((program[i].V_elem[j-1].diff >= 8) && (program[i].V_elem[j-1].fin == 1)) diag_score = diag_score*1.5;
        }
        total_score += diag_score;
    }
    return total_score;
}

void solve(){
    int N;
    elem_t *elements = leggi_file(&N);
    int DD = getDD();
    int DP = getDP();
    link head = malloc(sizeof(node_t)); //uso nodo fittizio
    head->next = NULL;
    link tail = head;
    int count = WRAP_gen_diag(N, elements, head, &tail, DD);
    diag_t *vett_diag = gen_vect_diag(count, head);
    WRAP_gen_prog(N, DP, DD, vett_diag);

    free(elements);
}

int WRAP_gen_diag(int n, elem_t *elements, node_t *head, node_t **tail_ptr, int DD) {
    int total_count = 0;
    diag_t curr_diag;
    int len;
    //costruisco diagonali lunghezza 1 a 5
    for (len = 1; len <= MAX_ELEM; len++) {
        curr_diag.V_elem = malloc(len * sizeof(elem_t));
        curr_diag.n_elem = 0;

        total_count = gen_diag(n, len, 0, curr_diag, elements, tail_ptr, total_count, 1, DD);

        free(curr_diag.V_elem);
    }

    return total_count;
}

void WRAP_gen_prog(int N, int DP, int DD, diag_t *diag_vett){
    int i;
    float max_score = -1;
    int *mark = calloc(N, sizeof(int));
    diag_t *curr_prog = malloc(3*sizeof(diag_t)); // non tratto gestione NULL per allocazione memoria
    diag_t *best_prog = malloc(3*sizeof(diag_t));

    for (i = 0; i < 3; i++) {
        curr_prog[i].n_elem = 0;
        curr_prog[i].V_elem = NULL;
        best_prog[i].n_elem = 0;
        best_prog[i].V_elem = NULL;
    }

    gen_prog(diag_vett, N, curr_prog, best_prog, mark, 0, &max_score, DP, DD);

    printf("Il massimo punteggio è:%f", max_score);

    free(mark);
    free(curr_prog);
    free(best_prog);
}