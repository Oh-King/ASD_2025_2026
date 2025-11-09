#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
}attivita_t;

attivita_t* leggi_file(char* filename);

int main(void) {

    attivita_t *seq = leggi_file("att.txt");

    free(seq);
    return 0;
}

attivita_t* leggi_file(char* filename) {
    int n_att;
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &n_att);
    attivita_t *seq = malloc(n_att*sizeof(attivita_t));
    for (int i = 0; i < n_att; i++) fscanf(fp, "%d %d", &seq[i].start, &seq[i].end);
    return seq;
}