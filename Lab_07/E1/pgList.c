#include "pgList.h"

struct pgList_s {
     pg_t pgNode;
     pgList_t next;
};

pgList_t pgList_init() {
     pgList_t pgList = malloc(sizeof(struct pgList_s));
     pgList->next = NULL;
     return pgList;
}

void pgList_free(pgList_t pgList) {
     pgList_t temp;
     while (pgList != NULL) {
          temp = pgList->next;
          free(pgList);
          pgList = temp;
     }
}

void pgList_read(FILE *fp, pgList_t pgList) {
     pg_t pg;
     while (pg_read(fp, &pg) != EOF) {
          pgList_insert(pgList, pg);
     }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
     if (pgList == NULL) {
          fprintf(fp,"Lista personaggi vuota\n");
          return;
     }
     while (pgList != NULL) {
          pg_print(fp, &(pgList->pgNode), invArray);
          fprintf(fp, "\n");
          pgList = pgList->next;
     }
}

void pgList_insert(pgList_t pgList, pg_t pg) { //suppongo il parametro formale pgList sia la coda della lista

}