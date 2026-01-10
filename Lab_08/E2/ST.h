#ifndef LABORATORI_ST_H
#define LABORATORI_ST_H
#include <stdlib.h>
#include <string.h>

typedef struct symbolTable *ST;

ST STinit(int V);
char *STsearchByIndex(ST tab, int index);
int STsearch(ST tab, char *name);
int STcount(ST tab);
void STinsert(ST tab, char *name);
void STfree(ST tab);

#endif //LABORATORI_ST_H