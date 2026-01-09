#ifndef LABORATORI_ST_H
#define LABORATORI_ST_H

typedef struct symbolTable *ST;

ST STinit(int V);
char *STsearchByIndex(ST tab, int index);
int STsearch(ST tab, char *name);
int STcount(ST tab);
void STinsert(ST tab, char *name, int index);

#endif //LABORATORI_ST_H