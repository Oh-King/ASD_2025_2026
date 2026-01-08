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
          pg_clean(&pgList->pgNode);
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
     pgList_t head = pgList->next;
     if (head == NULL) {
          fprintf(fp,"Lista personaggi vuota\n");
          return;
     }
     while (head != NULL) {
          pg_print(fp, &(head->pgNode), invArray);
          fprintf(fp, "\n");
          head = head->next;
     }
}

void pgList_insert(pgList_t pgList, pg_t pg) { //suppongo il parametro formale pgList sia la testa della lista
     pgList_t newNode = malloc(sizeof(struct pgList_s));
     if (newNode == NULL) {
          printf("Errore allocazione nodo personaggio\n");
          exit(1);
     }
     newNode->pgNode = pg;  //non serve copia profonda
     // inserimento in testa dopo il sentinella
     newNode->next = pgList->next;
     pgList->next = newNode;
}

void pgList_remove(pgList_t pgList, char* cod) {
     pgList_t pred, curr;
     if (pgList == NULL) {
          printf("Lista personaggi vuota\n");
          return;
     }
     for (curr = pgList, pred = curr; curr !=  NULL; pred = curr, curr = curr->next) {
          if (strcmp(curr->pgNode.code, cod) == 0) {
               pred->next = curr->next;
               pg_clean(&(curr->pgNode)); //libero equip
               free(curr);
               return;
          }
     }
     printf("Non è stato trovato un personaggio con quel codice\n");
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod) {
     pg_link ptr = NULL;
     pgList_t node;
     for (node = pgList; node != NULL; node = node-> next) {
          if (strcmp(node->pgNode.code, cod) == 0)
               return ptr = &(node->pgNode);
     }
     printf("Non e stato trovato un personaggio con quel codice\n");
     return NULL;
}