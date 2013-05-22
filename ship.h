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

void shipInit(field_t *field) ;
void shipMove(field_t *field, int y, int x);
void removeShip(field_t *field, int y, int x);
void shipSetArcane(field_t *field, int y, int x, int state);
void shipSetWing(field_t *field, int y, int x, int state);
void shipSetVertigo(field_t *field, int y, int x, int state);
void shipSetYomen(field_t *field, int y, int x, int state);
void shipSetOmega(field_t *field, int y, int x, int state);
void shipSetHero(field_t *field, int y, int x, int state);
void shipSetSkull(field_t *field, int y, int x, int state);
int bulletMove(field_t *field, int y, int x);
