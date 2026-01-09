#include "ST.h"

struct symbolTable {
    char **names;
    int n_elem;
    int max_cap;
};