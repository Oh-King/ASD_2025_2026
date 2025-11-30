#include "personaggi.h"
#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tab_PG_t WRAP_leggi_PG() {
    char filename[MAXLEN_N_T];
    printf("Inserisci il nome del file personaggi:\n");
    scanf("%s", filename);
    return leggi_PG(filename);
}

tab_PG_t leggi_PG(char *filename) {
    tab_PG_t tab_PG;
    tab_PG.head = NULL;
    tab_PG.tail = NULL;
    tab_PG.n_PG = 0;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) exit(1);

    char code[7], name[MAXLEN_N_T], class[MAXLEN_N_T];
    stat_t stats;

    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d",
                  code, name, class,
                  &stats.hp, &stats.mp, &stats.atk,
                  &stats.def, &stats.mag, &stats.spr) == 9) {
        link new_node = newPGNode(code, name, class, stats);
        if (new_node != NULL) {
            insertPG(&tab_PG, new_node);
        }
    }

    fclose(fp);
    return tab_PG;
}

link newPGNode(char *code, char *name, char *class, stat_t stats) {
    link new = malloc(sizeof(node_PG_t));
    if (new == NULL) return NULL;

    strcpy(new->code, code);
    strcpy(new->name, name);
    strcpy(new->class, class);
    new->PG_stats = stats;

    new->tab_EQ_ptr = malloc(sizeof(tab_EQ_t));
    if (new->tab_EQ_ptr == NULL) {
        free(new);
        return NULL;
    }

    new->tab_EQ_ptr->vettEQ = calloc(8, sizeof(obj_t*));
    if (new->tab_EQ_ptr->vettEQ == NULL) {
        free(new->tab_EQ_ptr);
        free(new);
        return NULL;
    }

    new->tab_EQ_ptr->currEQ = 0;
    new->next = NULL;

    return new;
}

void insertPG(tab_PG_t *tab_PG, link node) {
    if (tab_PG->head == NULL || strcmp(node->code, tab_PG->head->code) < 0) {
        node->next = tab_PG->head;
        tab_PG->head = node;
        if (tab_PG->tail == NULL) tab_PG->tail = node;
    } else {
        link prev = tab_PG->head;
        while (prev->next != NULL && strcmp(prev->next->code, node->code) < 0) {
            prev = prev->next;
        }
        node->next = prev->next;
        prev->next = node;
        if (node->next == NULL) tab_PG->tail = node;
    }
    tab_PG->n_PG++;
}

void deletePG(tab_PG_t *tab_PG, char *code) {
    if (tab_PG->head == NULL) {
        printf("Lista vuota\n");
        return;
    }

    link curr = tab_PG->head;
    link prev = NULL;

    while (curr != NULL && strcmp(curr->code, code) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Personaggio con codice %s non trovato\n", code);
        return;
    }

    if (prev == NULL) {
        tab_PG->head = curr->next;
        if (tab_PG->head == NULL) tab_PG->tail = NULL;
    } else {
        prev->next = curr->next;
        if (curr->next == NULL) tab_PG->tail = prev;
    }

    free(curr->tab_EQ_ptr->vettEQ);
    free(curr->tab_EQ_ptr);
    free(curr);
    tab_PG->n_PG--;

    printf("Personaggio %s eliminato\n", code);
}

link SEARCHcode(tab_PG_t *tab_PG, char *code) {
    link curr = tab_PG->head;
    while (curr != NULL) {
        if (strcmp(curr->code, code) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

void modEQofPG(tab_PG_t *tab_PG, tab_inv_t *tab_inv) {
    char code[7];
    int choice;

    printf("Inserisci il codice del personaggio:\n");
    scanf("%s", code);

    link pg = SEARCHcode(tab_PG, code);
    if (pg == NULL) {
        printf("Personaggio non trovato\n");
        return;
    }

    printf("1. Aggiungi oggetto\n");
    printf("2. Rimuovi oggetto\n");
    scanf("%d", &choice);

    if (choice == 1) {
        addEQ(pg, tab_inv);
    } else if (choice == 2) {
        removeEQ(pg);
    }
}

void addEQ(link pg, tab_inv_t *tab_inv) {
    if (pg->tab_EQ_ptr->currEQ >= 8) {
        printf("Equipaggiamento pieno\n");
        return;
    }

    char name[MAXLEN_N_T];
    printf("Inserisci il nome dell'oggetto da aggiungere:\n");
    scanf("%s", name);

    int idx = NAMEsearch(name, tab_inv);
    if (idx == -1) {
        printf("Oggetto non trovato nell'inventario\n");
        return;
    }

    pg->tab_EQ_ptr->vettEQ[pg->tab_EQ_ptr->currEQ] = &(tab_inv->OBJ[idx]);
    pg->tab_EQ_ptr->currEQ++;
    printf("Oggetto %s aggiunto all'equipaggiamento\n", name);
}

void removeEQ(link pg) {
    if (pg->tab_EQ_ptr->currEQ == 0) {
        printf("Equipaggiamento vuoto\n");
        return;
    }

    int pos;
    printf("Posizioni occupate: %d\n", pg->tab_EQ_ptr->currEQ);
    for (int i = 0; i < pg->tab_EQ_ptr->currEQ; i++) {
        printf("%d. %s\n", i, pg->tab_EQ_ptr->vettEQ[i]->name);
    }

    printf("Inserisci la posizione da rimuovere (0-%d):\n", pg->tab_EQ_ptr->currEQ - 1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= pg->tab_EQ_ptr->currEQ) {
        printf("Posizione non valida\n");
        return;
    }

    for (int i = pos; i < pg->tab_EQ_ptr->currEQ - 1; i++) {
        pg->tab_EQ_ptr->vettEQ[i] = pg->tab_EQ_ptr->vettEQ[i + 1];
    }

    pg->tab_EQ_ptr->currEQ--;
    printf("Oggetto rimosso\n");
}

void PRINTpersonaggi(tab_PG_t *tab_PG) {
    link curr = tab_PG->head;
    printf("\n=== LISTA PERSONAGGI ===\n");
    while (curr != NULL) {
        printf("\nCodice: %s\n", curr->code);
        printf("Nome: %s\n", curr->name);
        printf("Classe: %s\n", curr->class);
        printf("Stats base: HP=%d MP=%d ATK=%d DEF=%d MAG=%d SPR=%d\n",
               curr->PG_stats.hp, curr->PG_stats.mp, curr->PG_stats.atk,
               curr->PG_stats.def, curr->PG_stats.mag, curr->PG_stats.spr);
        printf("Oggetti equipaggiati: %d/8\n", curr->tab_EQ_ptr->currEQ);
        curr = curr->next;
    }
}

stat_t calcStatsFINAL(link pg) {
    stat_t final = pg->PG_stats;

    for (int i = 0; i < pg->tab_EQ_ptr->currEQ; i++) {
        obj_t *obj = pg->tab_EQ_ptr->vettEQ[i];
        final.hp += obj->stats.hp;
        final.mp += obj->stats.mp;
        final.atk += obj->stats.atk;
        final.def += obj->stats.def;
        final.mag += obj->stats.mag;
        final.spr += obj->stats.spr;
    }

    return final;
}

void PRINTstatsfinali(link pg) {
    stat_t final = calcStatsFINAL(pg);

    printf("\n=== STATISTICHE FINALI %s ===\n", pg->name);
    printf("HP: %d\n", final.hp);
    printf("MP: %d\n", final.mp);
    printf("ATK: %d\n", final.atk);
    printf("DEF: %d\n", final.def);
    printf("MAG: %d\n", final.mag);
    printf("SPR: %d\n", final.spr);
}

void FREEpersonaggi(tab_PG_t *tab_PG) {
    link curr = tab_PG->head;
    link temp;

    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp->tab_EQ_ptr->vettEQ);
        free(temp->tab_EQ_ptr);
        free(temp);
    }

    tab_PG->head = NULL;
    tab_PG->tail = NULL;
    tab_PG->n_PG = 0;
}
