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

elem_t* leggi_file();
void solve();
link NEWnode(link succ, diag_t diagonale);
bool hasACRO(diag_t diag, int end);
bool checkDIFF(diag_t diag, int end, int DD);
int getDD();
int getDP();

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

int gen_diag(int n, int k, int pos, diag_t curr_diag, elem_t *elements, node_t *node, node_t *tail, int count, int last_dir, int DD) {
    int i;

    if (pos >= k) {
        if ((hasACRO(curr_diag, pos) == true) && (checkDIFF(curr_diag, pos, DD) == true)) {
            tail->next = NEWnode(NULL, curr_diag);
            tail->next->diag.V_elem = (elem_t*)malloc(k * sizeof(elem_t));
            for (i = 0; i < pos; i++) {
                tail->next->diag.V_elem[i] = curr_diag.V_elem[i];
            }
            tail->next->diag.n_elem = pos;
            tail = tail->next;
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
                    tail->next = NEWnode(NULL, curr_diag);
                    tail->next->diag.V_elem = (elem_t*)malloc(k * sizeof(elem_t));
                    for (int j = 0; j <= pos; j++) {
                        tail->next->diag.V_elem[j] = curr_diag.V_elem[j];
                    }
                    tail->next->diag.n_elem = pos + 1;
                    tail = tail->next;
                    count++;
                }
            } else {
                count = gen_diag(n, k, pos + 1, curr_diag, elements, node, tail, count, elements[i].dir_ex, DD);
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
    for (i = 0; i < end; i++) sum+= diag.V_elem[i].diff;
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

void gen_prog(diag_t *diag_V, int size, diag_t **curr_prog, diag_t **best_prog, int *mark, int row, int col, int sum_diff, int DP) {
    int i;
    if((row >= MAX_DIAG) && (col >= MAX_ELEM)){
        if(checkVALID_PR == true)
        calcSCORE()

    }
}

bool checkVALID_PR(diag_t **PR, int DP){ //controllo se il programma è valido
    //CONSIDERO GIA' "CORRETTE" LE DIAGONALI, QUINDI PER I DUE ACROBATICI IN SEQUENZA
    //SUPPONGO USCITA DI PRIMO UGUALE A ENTRATA SECONDO
    //difficoltà minore di DP
    //almeno un acrobatico avanti e uno indietro nel PROGRAMMA
    //almeno due acrobatici in sequenza in una DIAGONALE
    //NON controllo l'ultima casella per il bonus
    int tot_diff = 0;
    int i, j;
    bool first_acr = false, second_acr = false; // alla fine se entrambi veri programma ok e posso vedere punteggio finale
    bool first_seq = false, second_seq = false, both_acr_valid = false; //se both_acr_valid = true posso continuare con punteggio
    for(i = 0; i < MAX_DIAG; i++){
        for(j = 0; j < MAX_ELEM; j++){
            tot_diff += PR[i][j].V_elem->diff;
            if(PR[i][j].V_elem->typo != 0){
                if(first_acr == false){
                    first_acr = true;
                    if(first_seq == false) first_seq = true;
                }
                else if(second_acr == false) {
                    second_acr = true;
                    if(first_seq == false) first_seq = true;
                }
                else if(first_seq == false) first_seq = true;
                else if(first_seq == true) {
                    second_seq = true;
                    both_acr_valid = true;
                }
            }else {
                if(first_seq == true) first_seq = false;
            }
        }
    }
    if(tot_diff < DP){}
}