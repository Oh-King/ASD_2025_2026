#include <stdio.h>

#define EMPTY -1
#define NOT_FLIP 0
#define FLIP 1

typedef enum {not_flip, flip} rot_t;

typedef struct {
    char color1, color2;
    int val1, val2;
}tessera_t;

typedef struct {
    int card_id;
    rot_t rotation;
}tile_t;

int main(void) {

    return 0;
}