#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 1000
#define STRING 31
#define MAX_CMD 14
#define FINE_PROGRAMMA 0

typedef struct {	//struttura per tipo "ora"
	int hrs;
	int mins;
	int secs;
}ora_t;

typedef struct {	//struttura per tipo "data"
	int dd;
	int mm;
	int yy;
}data_t;

typedef struct {	//struttura per tipo "tratta"
	char codice_tratta[STRING];
	char partenza[STRING];
	char destinazione[STRING];
	char data_str[STRING];
	char ora_p_str[STRING];
	char ora_a_str[STRING];
	data_t data;
	ora_t ora_part;
	ora_t ora_arr;
	int rit;
}tratta_t;

typedef struct {	//struttura tabella
	int n_tratte;
	tratta_t log[ROWS];		//vettore di tratta_t di dimensione ROWS
}tabella_t;

typedef enum {
	r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_stampa_contenuti, r_ordinamento_data, r_ordinamento_codice_t,
	r_ordinamento_partenza, r_ordinamento_arrivo, r_ricerca_tratta_codice, r_ricerca_tratta_part, r_ordinamenti_contemporanei ,r_fine
	} comando_e;

typedef int (*confronta_ptr)(tratta_t, tratta_t);

//DICHIARAZIONE FUNZIONI USATE

comando_e leggiComando(char comandi[][STRING]);
int confrontaDate(data_t data1, data_t data2);
tabella_t leggiTabella(FILE* filename);
void menuParola(tabella_t tab, comando_e cmd,
	tratta_t** vector_data, tratta_t **vector_t_code, tratta_t **vector_part, tratta_t **vector_arr);
void stampaComandi(char comandi[][STRING]);
void stampaCorsa(tabella_t tab, int index);
void data_string_to_int(char data[STRING], char ora_p_str[STRING], char ora_a_str[STRING], tabella_t* tab, int index);
void ordinaData(tabella_t *tab, tratta_t *vector_data); //passo direttamente la tabella così agisco con puntatori senza perdere informazione su n_tratte
void sortData(tratta_t *log, tratta_t *log_copy, int l, int r, int type);
void mergeData(tratta_t *log, tratta_t *log_copy, int l, int q, int r, int type);
void MergeSort(tratta_t *log, tratta_t *log_copy, int l, int r, confronta_ptr confronta);
void Merge(tratta_t *log, tratta_t *log_copy, int l, int q, int r, confronta_ptr confronta);
bool isLESSorEQ(tratta_t log1, tratta_t log2);
int confrontaTratta(tratta_t log1, tratta_t log2);
int confrontaPartenza(tratta_t log1, tratta_t log2);
int confrontaArrivo(tratta_t log1, tratta_t log2);
void Ordina(tabella_t* tab, tratta_t *vettore_gen,confronta_ptr confronta, int type);
void linear_research(tabella_t *tab, char *codice);
void binary_search(tabella_t *tab, char *codice);


int main() {
	FILE* fin = fopen("corse.txt", "r");
	if(fin == NULL) return -1;

	bool end = false;

	char comandi[][STRING] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "stampa_contenuti",
	"ordinamento_data", "ordinamento_codice_t" , "ordinamento_partenza", "ordinamento_arrivo",
	"ricerca_tratta_code", "ricerca_tratta_part", "ordinamenti_in_contemporanea","fine"};
	tabella_t tab = leggiTabella(fin);
	fclose(fin);

	tratta_t **vector_data = (tratta_t**) malloc(tab.n_tratte * sizeof(tratta_t));
	tratta_t **vector_t_code = (tratta_t**) malloc(tab.n_tratte * sizeof(tratta_t));
	tratta_t **vector_part = (tratta_t**) malloc(tab.n_tratte * sizeof(tratta_t));
	tratta_t **vector_arr = (tratta_t**) malloc(tab.n_tratte * sizeof(tratta_t));

	for (int i = 0; i < tab.n_tratte; i++) {
		*(vector_arr+i) = *(vector_part+i) = *(vector_t_code+i) = *(vector_data+i) = &tab.log[i];
	}

	while(!end){
		comando_e cmd = leggiComando(comandi);
		if(cmd == r_fine) {
			free(vector_arr);
			free(vector_part);
			free(vector_data);
			free(vector_t_code);
			printf("Hai scelto di chiudere il programma!");
			return FINE_PROGRAMMA;
		}
		menuParola(tab, cmd, vector_data, vector_t_code, vector_part, vector_arr);
	}
	return 0;
}

void stampaComandi(char comandi[][STRING]){		//stampa a video i comandi possibili, DA AGGIUNGERE UN COMANDO PER
	printf("I comandi disponili sono:\n");		//STAMPARE TUTTI E 4 GLI ORDINAMENTI ASSIEME
	printf("|");
	for(int i = 0; i < MAX_CMD; i++)
		printf("| %s |", comandi[i]);
	printf("|\n");
}

comando_e leggiComando(char comandi[][STRING]){
	int i;
	char cmd[STRING];
	printf("Quale comando vuoi?: \n");
	stampaComandi(comandi);
	scanf("%s", cmd);
	for(i = 0; i < MAX_CMD; i++){
		if(strcmp(cmd, comandi[i]) == 0)
		return (comando_e) i;
	}
	return -1;
}

void menuParola(tabella_t tab, comando_e cmd,
	tratta_t** vector_data, tratta_t **vector_t_code, tratta_t **vector_part, tratta_t **vector_arr){
	data_t d1, d2;
	char input_cmd[STRING];
	int ritardo_tot = 0;
	int research_type;
	tratta_t *log_copy;

	switch(cmd){
		// COMANDI DI ORDINAMENTO - Non necessitano ciclo
		case r_ordinamenti_contemporanei:
			printf("==============================\n");
			ordinaData(&tab, *vector_data);
			Ordina(&tab, *vector_t_code, confrontaTratta, 0);
			Ordina(&tab, *vector_arr, confrontaPartenza, 1);
			Ordina(&tab, *vector_part, confrontaArrivo, 2);
		printf("==============================\n");
		return;
		case r_ordinamento_data:
			ordinaData(&tab, *vector_data);	//FATTO
			return;

		case r_ordinamento_codice_t:
			Ordina(&tab, *vector_t_code, confrontaTratta, 0);
			return;

		case r_ordinamento_partenza:
			Ordina(&tab, *vector_arr, confrontaPartenza, 1);
			return;

		case r_ordinamento_arrivo:
			Ordina(&tab, *vector_part, confrontaArrivo, 2);
			return;

		case r_stampa_contenuti:
			for(int i = 0; i < tab.n_tratte; i++)
				stampaCorsa(tab, i);
			return;

		// COMANDI DI RICERCA E FILTRO - Necessitano del loop
		case r_date:
			printf("Inserisci la prima data nel formato [dd/mm/yyyy]: \n");
			scanf("%d/%d/%d", &d1.dd, &d1.mm, &d1.yy);
			printf("Inserisci la seconda data nel formato [dd/mm/yyyy]: \n");
			scanf("%d/%d/%d", &d2.dd, &d2.mm, &d2.yy);

			for(int i = 0; i < tab.n_tratte; i++){
				if(confrontaDate(d1, tab.log[i].data) <= 0 && confrontaDate(tab.log[i].data, d2) <= 0)
					stampaCorsa(tab, i);
			}
			return;

		case r_partenza:
			printf("Inserisci la fermata di partenza: \n");
			scanf("%s", input_cmd);

			for(int i = 0; i < tab.n_tratte; i++){
				if(strcmp(input_cmd, tab.log[i].partenza) == 0)
					stampaCorsa(tab, i);
			}
			return;

		case r_capolinea:
			printf("Inserisci la fermata di arrivo: \n");
			scanf("%s", input_cmd);

			for(int i = 0; i < tab.n_tratte; i++){
				if(strcmp(input_cmd, tab.log[i].destinazione) == 0)
					stampaCorsa(tab, i);
			}
			return;

		case r_ritardo:
			printf("Inserisci la prima data [yyyy/mm/dd] per trovare i ritardi: \n");
			scanf("%d/%d/%d", &d1.yy, &d1.mm, &d1.dd);
			printf("Inserisci la seconda data [yyyy/mm/dd] per trovare i ritardi: \n");
			scanf("%d/%d/%d", &d2.yy, &d2.mm, &d2.dd);

			for(int i = 0; i < tab.n_tratte; i++){
				if(confrontaDate(d1, tab.log[i].data) <= 0 && confrontaDate(tab.log[i].data, d2) <= 0 && tab.log[i].rit > 0)
					stampaCorsa(tab, i);
			}
			return;

		case r_ritardo_tot:
			printf("Inserisci il codice della tratta della quale vuoi calcolare il ritardo totale: \n");
			scanf("%s", input_cmd);

			for(int i = 0; i < tab.n_tratte; i++){
				if(strcmp(input_cmd, tab.log[i].codice_tratta) == 0 && tab.log[i].rit > 0)
					ritardo_tot += tab.log[i].rit;
			}
			printf("Il ritardo totale accumulato dalla tratta %s e' di %d minuti\n", input_cmd, ritardo_tot);
			return;

		case r_ricerca_tratta_codice:

			printf("Inserisci il codice della tratta da cercare: \n");
			scanf("%s", input_cmd);
			printf("Vuoi ricercare linearmente (0) o binariamente (1)?:");
			do
			{
				scanf("%d", &research_type);
			}while (research_type != 0 && research_type != 1);
			 if(research_type == 0 ) {
				 linear_research(&tab, input_cmd);
			 } else {
			 	 MergeSort(tab.log, log_copy, 0, tab.n_tratte-1,  confrontaTratta);
				 binary_search(&tab, input_cmd);
			 }
			return;

		case r_ricerca_tratta_part:
			printf("Inserisci la fermata di partenza da cercare: \n");
			scanf("%s", input_cmd);

			for(int i = 0; i < tab.n_tratte; i++){
				if(strcmp(input_cmd, tab.log[i].partenza) == 0)
					stampaCorsa(tab, i);
			}
			return;

		default:
			printf("ERRORE: il comando non è valido\n");
			return;
	}
}

int confrontaDate(data_t data1, data_t data2){
	if(data1.yy != data2.yy) return (data1.yy-data2.yy);
	else if(data1.mm != data2.mm) return (data1.mm-data2.mm);
	else if(data1.dd != data2.dd) return (data1.dd-data2.dd);
	else return 0;
}

void stampaCorsa(tabella_t tab, int index){
	printf("La corsa di codice %s, partita da %s in data %d/%d/%d alle ore: %d:%d:%d, e' arrivata a %s alle ore %d:%d:%d con %i minuti di ritardo\n",
		tab.log[index].codice_tratta, tab.log[index].partenza, tab.log[index].data.dd, tab.log[index].data.mm, tab.log[index].data.yy,
		tab.log[index].ora_part.hrs, tab.log[index].ora_part.mins, tab.log[index].ora_part.secs, tab.log[index].destinazione, tab.log[index].ora_arr.hrs,
		tab.log[index].ora_arr.mins, tab.log[index].ora_arr.secs, tab.log[index].rit);
}

void data_string_to_int(char data[STRING], char ora_p_str[STRING], char ora_a_str[STRING], tabella_t* tab, int index){	//FATTA
	sscanf(data, "%d/%d/%d", &tab->log[index].data.yy, &tab->log[index].data.mm, &tab->log[index].data.dd);
	sscanf(ora_p_str, "%d:%d:%d", &tab->log[index].ora_part.hrs, &tab->log[index].ora_part.mins, &tab->log[index].ora_part.secs);
	sscanf(ora_a_str, "%d:%d:%d", &tab->log[index].ora_arr.hrs, &tab->log[index].ora_arr.mins, &tab->log[index].ora_arr.secs);
}


tabella_t leggiTabella(FILE* filename){
    tabella_t tab;
    char line[256];  // Buffer per riga
    fscanf(filename, "%d", &tab.n_tratte);  // Legge numero tratte
    fgets(line, sizeof(line), filename);  // Consuma newline dopo numero
    for(int i = 0; i < tab.n_tratte; i++){
        if(fgets(line, sizeof(line), filename) == NULL) break;  // Leggi riga
        // Parsa la riga: assumi spazi tra campi, ma gestisci spazi nei nomi con %[^\n] o simili
        sscanf(line, "%s %s %s %s %s %s %d",
            tab.log[i].codice_tratta, tab.log[i].partenza, tab.log[i].destinazione, tab.log[i].data_str, tab.log[i].ora_p_str, tab.log[i].ora_a_str, &tab.log[i].rit);
        data_string_to_int(tab.log[i].data_str, tab.log[i].ora_p_str, tab.log[i].ora_a_str, &tab, i);
    }
    return tab;
}

void ordinaData(tabella_t *tab, tratta_t *vector_data){
	int type;
	printf("Vuoi ordinare le date in ordine crescente (0) o decrescente (1)?\n");
	do{
		scanf("%d", &type);
	}while(type != 0 && type != 1);

	int l = 0, r = tab->n_tratte-1;

	tratta_t *log_copy = malloc(tab->n_tratte * sizeof(tratta_t));
	if(log_copy == NULL) return;
	sortData(vector_data, log_copy, l, r, type);
	free(log_copy);

	// Stampa il risultato ordinato
	printf("=== TRATTE ORDINATE PER DATA %s ===\n", (type == 0) ? "(CRESCENTE)" : "(DECRESCENTE)");
	for(int i = 0; i < tab->n_tratte; i++){
		printf("%d. %s | %s -> %s | Data: %s Ora: %s\n",
			i+1, vector_data[i].codice_tratta, vector_data[i].partenza,
			vector_data[i].destinazione, vector_data[i].data_str, vector_data[i].ora_p_str);
	}
	printf("===============================\n\n");
}

void sortData(tratta_t *log, tratta_t *log_copy, int l, int r, int type){
	int q;
	if(l >= r) return;
	q = (l+r)/2;
	sortData(log, log_copy, l, q, type);
	sortData(log, log_copy, q+1, r, type);
	mergeData(log, log_copy, l, q, r, type);
}

void mergeData(tratta_t *log, tratta_t *log_copy, int l, int q, int r, int type){
	int i = l;
	int j = q + 1;

	for(int k = l; k <= r; k++){
		if(i > q)
			log_copy[k] = log[j++];
		else if(j > r)
			log_copy[k] = log[i++];
		else {
			// type == 0: ordine crescente (usa isLESSorEQ normale)
			// type == 1: ordine decrescente (inverte il confronto)
			bool condizione = (type == 0) ? isLESSorEQ(log[i], log[j]) : isLESSorEQ(log[j], log[i]);

			if(condizione)
				log_copy[k] = log[i++];
			else
				log_copy[k] = log[j++];
		}
	}

	// Copia il risultato nell'array originale
	for(int k = l; k <= r; k++)
		log[k] = log_copy[k];
}

bool isLESSorEQ(tratta_t log1, tratta_t log2){
	//NB: confronto con stringhe solo perché il formato lo permette, chiaramente ciò presume che l'input sia corretto
	//ciò solo per avere una funzione piu compatta, negli altri casi ho usato una struct per definire i tipi di data e ora
	int cmp_data = strcmp(log1.data_str, log2.data_str);

	if(cmp_data < 0)
		return true;  // log1 ha data precedente
	else if(cmp_data > 0)
		return false; // log1 ha data successiva
	else {
		// Date uguali, confronta per ora di partenza (stringa formato hh:mm:ss)
		int cmp_ora = strcmp(log1.ora_p_str, log2.ora_p_str);
		return (cmp_ora <= 0);  // log1 <= log2 se ora è minore o uguale
	}
}

void Ordina(tabella_t* tab, tratta_t *vettore_gen, confronta_ptr confronta, int type){
	char *cat[3] = {"codice tratta", "partenza", "arrivo"};

	printf("Ordino le tratte per %s:\n", cat[type]);
	printf("==============================\n");

	//vettore supporto
	tratta_t *log_copy = malloc(tab->n_tratte * sizeof(tratta_t));
	if(log_copy == NULL) {
		printf("Errore allocazione memoria!\n");
		return;
	}
	// Ordina usando MergeSort
	int l = 0, r = tab->n_tratte - 1;
	MergeSort(vettore_gen, log_copy, l, r, confronta);

	//Array ordinato
	for(int i = 0; i < tab->n_tratte; i++)
		printf("%d. Codice: %s | %s -> %s\n", i+1, vettore_gen[i].codice_tratta,
			vettore_gen[i].partenza, vettore_gen[i].destinazione);
	printf("==============================\n\n");
	free(log_copy);
}

// MergeSort generico che usa puntatori a funzione per i confronti
void MergeSort(tratta_t *log, tratta_t *log_copy, int l, int r, confronta_ptr confronta){
	if(l >= r) return;
	int q = (l + r) / 2;
	MergeSort(log, log_copy, l, q, confronta);
	MergeSort(log, log_copy, q+1, r, confronta);
	Merge(log, log_copy, l, q, r, confronta);
}

// Merge generico che usa puntatori a funzione per i confronti
void Merge(tratta_t *log, tratta_t *log_copy, int l, int q, int r, confronta_ptr confronta){
	int i = l;
	int j = q + 1;

	for(int k = l; k <= r; k++){
		if(i > q)
			log_copy[k] = log[j++];
		else if(j > r)
			log_copy[k] = log[i++];
		else if(confronta(log[i], log[j]) <= 0)
			log_copy[k] = log[i++];
		else
			log_copy[k] = log[j++];
	}

	// Copio il risultato nell'array originale
	for(int k = l; k <= r; k++)
		log[k] = log_copy[k];
}

int confrontaTratta(tratta_t log1, tratta_t log2){
	return strcmp(log1.codice_tratta, log2.codice_tratta);
}
int confrontaPartenza(tratta_t log1, tratta_t log2){
	return strcmp(log1.partenza, log2.partenza);
}
int confrontaArrivo(tratta_t log1, tratta_t log2){
	return strcmp(log1.destinazione, log2.destinazione);
}

void linear_research(tabella_t *tab, char *codice){
	for (int i = 0; i < tab->n_tratte; i++)
		if (strcmp(tab->log[i].codice_tratta, codice) == 0){
			printf("Ho trovato la tratta %s, partita da %s e arrivata a %s\n",
				tab->log[i].codice_tratta, tab->log[i].partenza, tab->log[i].destinazione);
			return;
		}
	printf("Non ho trovato nessuna traccia con quel codice\n");
}

void binary_search(tabella_t *tab, char *codice){
	//NB: prima di fare la ricerca devo esser sicuro che la tabella sia ordinata per codice_tratta
	int sx = 0, dx = tab->n_tratte - 1;

	while(sx <= dx){
		int mid = sx + (dx - sx) / 2;
		int cmp = strcmp(tab->log[mid].codice_tratta, codice);
		if(cmp == 0){
			// Trovato!
			printf("Ho trovato la tratta %s, partita da %s e arrivata a %s\n",
				tab->log[mid].codice_tratta, tab->log[mid].partenza, tab->log[mid].destinazione);
			return;
		}
		if(cmp < 0)
			sx = mid + 1;  // Il codice cercato è nella metà destra
		else
			dx = mid - 1;  // Il codice cercato è nella metà sinistra
	}
	printf("Non ho trovato nessuna traccia con quel codice\n");
}
