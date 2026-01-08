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
     pgList_t tmp;
     while (pgList != NULL) {
          tmp = pgList->next;
          free(pgList);
          pgList = tmp;
     }
}

void pgList_read(FILE *fp, pgList_t pgList) {

}