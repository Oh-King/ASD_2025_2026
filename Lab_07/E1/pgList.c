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
     fp = fopen("pg.txt", "r");
     pgList_t temp = pgList;
     while (pgList != NULL) {
          pg_read(fp, &(pgList->pgNode));
          pgList->next = pgList_init();
          if (pg_read(fp, &(pgList->next->pgNode)) == 0)
          pgList = pgList->next;
          else {
               printf("Problemi nella lettura personaggi\n");
               exit(1);
          }
     }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {

}

void pgList_insert(pgList_t pgList, pg_t pg) { //suppongo il parametro formale pgList sia la coda della lista

}