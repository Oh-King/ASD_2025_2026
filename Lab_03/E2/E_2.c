#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 50

typedef struct {
    int dd;
    int mm;
    int yy;
}data_t;

typedef struct {
    char codice[6];
    char nome[MAXSTRING];
    char cognome[MAXSTRING];
    data_t data_nascita;
    char via[MAXSTRING];
    char citta[MAXSTRING];
    int cap;
}item;

typedef struct node *link;
typedef struct node{
    item val;
    link next;
    link prev;
}node;

link creaLista();
void menu();
link inserisciOrdinato(link head, item x);
link inserisciDaTastiera(link head);
link inserisciDaFile(link head, char *filename);
item cercaPerCodice(link head, char *codice, int *trovato);
link cancellaPerCodice(link head, char *codice, item *eliminato, int *trovato);
link cancellaPerIntervallo(link head, data_t d1, data_t d2, item *eliminato, int *trovato);
void stampaLista(link head, char *filename);
void stampaItem(item x);
int confrontaDate(data_t d1, data_t d2);
int dataInIntervallo(data_t d, data_t d1, data_t d2);
link liberaLista(link head);

int main(){
    link head = creaLista();
    int scelta, trovato;
    item eliminato;
    char codice[6], filename[100];
    data_t d1, d2;

    do{
        menu();
        printf("\nInserisci la tua scelta: ");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                head = inserisciDaTastiera(head);
                break;
            case 2:
                printf("Inserisci il nome del file: ");
                scanf("%s", filename);
                head = inserisciDaFile(head, filename);
                break;
            case 3:
                printf("Inserisci il codice da cercare: ");
                scanf("%s", codice);
                item trovato_item = cercaPerCodice(head, codice, &trovato);
                if(trovato){
                    printf("\nElemento trovato:\n");
                    stampaItem(trovato_item);
                }else{
                    printf("\nElemento non trovato.\n");
                }
                break;
            case 4:
                printf("Inserisci il codice da cancellare: ");
                scanf("%s", codice);
                head = cancellaPerCodice(head, codice, &eliminato, &trovato);
                if(trovato){
                    printf("\nElemento cancellato:\n");
                    stampaItem(eliminato);
                }else{
                    printf("\nElemento non trovato.\n");
                }
                break;
            case 5:
                printf("Inserisci la prima data (gg/mm/aaaa): ");
                scanf("%d/%d/%d", &d1.dd, &d1.mm, &d1.yy);
                printf("Inserisci la seconda data (gg/mm/aaaa): ");
                scanf("%d/%d/%d", &d2.dd, &d2.mm, &d2.yy);
                printf("\nElementi cancellati nell'intervallo:\n");
                do{
                    head = cancellaPerIntervallo(head, d1, d2, &eliminato, &trovato);
                    if(trovato){
                        stampaItem(eliminato);
                    }
                }while(trovato);
                break;
            case 6:
                printf("Inserisci il nome del file di output: ");
                scanf("%s", filename);
                stampaLista(head, filename);
                printf("Lista stampata su file.\n");
                break;
            case 0:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }
    }while(scelta != 0);

    head = liberaLista(head);
    return 0;
}

link creaLista(){
    return NULL;
}

void menu(){
    printf("\n===== GESTIONE ANAGRAFICA =====\n");
    printf("1. Inserisci elemento da tastiera\n");
    printf("2. Inserisci elementi da file\n");
    printf("3. Ricerca per codice\n");
    printf("4. Cancella per codice\n");
    printf("5. Cancella per intervallo di date\n");
    printf("6. Stampa lista su file\n");
    printf("0. Esci\n");
}

int confrontaDate(data_t d1, data_t d2){
    if(d1.yy != d2.yy) return d1.yy - d2.yy;
    if(d1.mm != d2.mm) return d1.mm - d2.mm;
    return d1.dd - d2.dd;
}

link inserisciOrdinato(link head, item x){
    link nuovo = (link)malloc(sizeof(node));
    nuovo->val = x;
    nuovo->next = NULL;
    nuovo->prev = NULL;

    if(head == NULL){
        return nuovo;
    }

    // Inserimento in testa se più anziano
    if(confrontaDate(x.data_nascita, head->val.data_nascita) < 0){
        nuovo->next = head;
        head->prev = nuovo;
        return nuovo;
    }

    // Cerco la posizione corretta
    link curr = head;
    while(curr->next != NULL && confrontaDate(x.data_nascita, curr->next->val.data_nascita) >= 0){
        curr = curr->next;
    }

    // Inserimento
    nuovo->next = curr->next;
    nuovo->prev = curr;
    if(curr->next != NULL){
        curr->next->prev = nuovo;
    }
    curr->next = nuovo;

    return head;
}

link inserisciDaTastiera(link head){
    item x;
    printf("\nInserimento nuovo elemento:\n");
    printf("Codice (AXXXX): ");
    scanf("%s", x.codice);
    printf("Nome: ");
    scanf("%s", x.nome);
    printf("Cognome: ");
    scanf("%s", x.cognome);
    printf("Data di nascita (gg/mm/aaaa): ");
    scanf("%d/%d/%d", &x.data_nascita.dd, &x.data_nascita.mm, &x.data_nascita.yy);
    printf("Via: ");
    scanf("%s", x.via);
    printf("Citta: ");
    scanf("%s", x.citta);
    printf("CAP: ");
    scanf("%d", &x.cap);

    return inserisciOrdinato(head, x);
}

link inserisciDaFile(link head, char *filename){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Errore nell'apertura del file.\n");
        return head;
    }

    item x;
    while(fscanf(fp, "%s %s %s %d/%d/%d %s %s %d",
                x.codice, x.nome, x.cognome,
                &x.data_nascita.dd, &x.data_nascita.mm, &x.data_nascita.yy,
                x.via, x.citta, &x.cap) == 9){
        head = inserisciOrdinato(head, x);
    }

    fclose(fp);
    printf("Elementi inseriti da file.\n");
    return head;
}

item cercaPerCodice(link head, char *codice, int *trovato){
    link curr = head;
    *trovato = 0;
    item vuoto;

    while(curr != NULL){
        if(strcmp(curr->val.codice, codice) == 0){
            *trovato = 1;
            return curr->val;
        }
        curr = curr->next;
    }

    return vuoto;
}

link cancellaPerCodice(link head, char *codice, item *eliminato, int *trovato){
    link curr = head;
    *trovato = 0;

    while(curr != NULL){
        if(strcmp(curr->val.codice, codice) == 0){
            *trovato = 1;
            *eliminato = curr->val;

            // Rimuovo nodo
            if(curr->prev != NULL){
                curr->prev->next = curr->next;
            }else{
                head = curr->next;
            }

            if(curr->next != NULL){
                curr->next->prev = curr->prev;
            }

            free(curr);
            return head;
        }
        curr = curr->next;
    }

    return head;
}

int dataInIntervallo(data_t d, data_t d1, data_t d2){
    return (confrontaDate(d, d1) >= 0 && confrontaDate(d, d2) <= 0);
}

link cancellaPerIntervallo(link head, data_t d1, data_t d2, item *eliminato, int *trovato){
    link curr = head;
    *trovato = 0;

    while(curr != NULL){
        if(dataInIntervallo(curr->val.data_nascita, d1, d2)){
            *trovato = 1;
            *eliminato = curr->val;

            if(curr->prev != NULL){
                curr->prev->next = curr->next;
            }else{
                head = curr->next;
            }

            if(curr->next != NULL){
                curr->next->prev = curr->prev;
            }

            free(curr);
            return head;
        }
        curr = curr->next;
    }

    return head;
}

void stampaItem(item x){
    printf("%s %s %s %02d/%02d/%d %s %s %d\n",
           x.codice, x.nome, x.cognome,
           x.data_nascita.dd, x.data_nascita.mm, x.data_nascita.yy,
           x.via, x.citta, x.cap);
}

void stampaLista(link head, char *filename){
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Errore nell'apertura del file.\n");
        return;
    }

    link curr = head;
    while(curr != NULL){
        fprintf(fp, "%s %s %s %02d/%02d/%d %s %s %d\n",
                curr->val.codice, curr->val.nome, curr->val.cognome,
                curr->val.data_nascita.dd, curr->val.data_nascita.mm, curr->val.data_nascita.yy,
                curr->val.via, curr->val.citta, curr->val.cap);
        curr = curr->next;
    }

    fclose(fp);
}

link liberaLista(link head){
    link curr = head, temp;
    while(curr != NULL){
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    return NULL;
}