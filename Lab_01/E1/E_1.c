#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_L_EXP 100
#define MAX_L_IN 500

char* cercaRegExp(char *src, char* regexp);

int main(void) {

	char exp[MAX_L_EXP];
	char src[MAX_L_IN];

	printf("Inserisci la stringa:");
	scanf("%s", src);
	printf("Ora inserisci l'espressione regolare:");
	scanf("%s", exp);

	printf("Ho trovato: %p", cercaRegExp(src, exp));
	return 0;
}

char* cercaRegExp(char *src, char* regexp) {
	//prova ogni posizione di src come punto di partenza
	for (int start_pos = 0; src[start_pos] != '\0'; start_pos++) {

		int p = 0;  // indice in regexp
		int s = 0;  // "distanza" dalla posizione di partenza in src
		bool match_ok = true;

		//prova a matchare il pattern da src[start_pos]
		while (regexp[p] != '\0' && match_ok) {

			// stringa non finita
			if (src[start_pos + s] == '\0') {
				match_ok = false;
				break;
			}

			// Caso 1: punto '.' - match qualsiasi carattere
			if (regexp[p] == '.') {
				p++;
				s++;
			}
			// Caso 2: classe di caratteri '[...]' o '[^...]'
			else if (regexp[p] == '[') {
				p++; // salta '['

				bool negated = false;
				if (regexp[p] == '^') {
					negated = true;
					p++;
				}

				// Raccogli tutti i caratteri fino a ']'
				char set[MAX_L_EXP];
				int set_len = 0;
				while (regexp[p] != ']' && regexp[p] != '\0') {
					set[set_len++] = regexp[p];
					p++;
				}

				if (regexp[p] == ']') {
					p++; // salta ']'
				}

				// Verifica se il carattere corrente è in set
				bool found = false;
				for (int i = 0; i < set_len; i++) {
					if (src[start_pos + s] == set[i]) {
						found = true;
						break;
					}
				}

				// Applica la negazione se necessario
				if (negated) {
					found = !found;
				}

				if (found) {
					s++;
				} else {
					match_ok = false;
				}
			}
			// Caso 3: backslash '\a' o '\A'
			else if (regexp[p] == '\\') {
				p++; // salta '\'

				if (regexp[p] == 'a') {
					// caso minuscola
					if (src[start_pos + s] >= 'a' && src[start_pos + s] <= 'z') {
						p++;
						s++;
					} else {
						match_ok = false;
					}
				}
				else if (regexp[p] == 'A') {
					// caso maiuscola
					if (src[start_pos + s] >= 'A' && src[start_pos + s] <= 'Z') {
						p++;
						s++;
					} else {
						match_ok = false;
					}
				}
				else {
					// Backslash non riconosciuto, considero carattere normale
					if (src[start_pos + s] == regexp[p]) {
						p++;
						s++;
					} else {
						match_ok = false;
					}
				}
			}
			// Caso 4: carattere normale
			else {
				if (src[start_pos + s] == regexp[p]) {
					p++;
					s++;
				} else {
					match_ok = false;
				}
			}
		}

		// Se il pattern è completamente matchato, restituisci il puntatore
		if (match_ok && regexp[p] == '\0') {
			return &src[start_pos];
		}
	}

	// Nessun match trovato
	return NULL;
}
