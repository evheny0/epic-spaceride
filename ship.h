#include <stdlib.h>
#include <math.h>
#include "field.h"

enum SHIPS {
    ARCANE,
    WING,
    VERTIGO,
    YOMEN,
    OMEGA,
    HERO,
    SKULL
};


void shipMove(field_t *field, int y, int x);
int bulletMove(field_t *field, int y, int x);
