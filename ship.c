#include "ship.h"

void shipInit(field_t *field) 
{
    field->shipLocation.x = field->size.x / 2;
    field->shipLocation.y = field->size.y - 1;
    shipMove(field, 0, 0);
}

void removeShip(field_t *field, int y, int x)
{
    int i, j;
    for (i = (y - 4); i <= y; i++) {
        for (j = (x - 2); j <= (x + 2); j++) {
            if (field->values[i][j] == SHIP) {
                field->values[i][j] = EMPTY;
            }
        }
    }
}

void shipMove(field_t *field, int y, int x)
{
    removeShip(field, field->shipLocation.y, field->shipLocation.x);
    field->shipLocation.x += x;
    (field->shipLocation.x >= field->size.x || field->shipLocation.x < 0) ? field->shipLocation.x -= x : x;
    field->shipLocation.y += y;
    (field->shipLocation.y >= field->size.y || (field->shipLocation.y - 3) < 0) ? field->shipLocation.y -= y : y;

    switch (field->shipType) {
    case ARCANE: 
        shipSetArcane(field, field->shipLocation.y, field->shipLocation.x, SHIP);
        break;
    case WING: 
        shipSetWing(field, field->shipLocation.y, field->shipLocation.x, SHIP);
        break;
    case VERTIGO: 
        shipSetVertigo(field, field->shipLocation.y, field->shipLocation.x, SHIP);
        break;
    case YOMEN: 
        shipSetYomen(field, field->shipLocation.y, field->shipLocation.x, SHIP);
        break;
    case OMEGA: 
        shipSetOmega(field, field->shipLocation.y, field->shipLocation.x, SHIP);
        break;
    case HERO: 
        shipSetHero(field, field->shipLocation.y, field->shipLocation.x, SHIP);
        break;
    case SKULL: 
        shipSetSkull(field, field->shipLocation.y, field->shipLocation.x, SHIP);
        break;
    }
}

void shipSetArcane(field_t *field, int y, int x, int state)
{
    state = (state) ? (SHIP) : (EMPTY);
    ((field->values[y][x - 1] < BLOCK_LVL1) || (field->values[y][x - 1] > BLOCK_LVL3)) ? (field->values[y][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y][x + 1] < BLOCK_LVL1) || (field->values[y][x + 1] > BLOCK_LVL3)) ? (field->values[y][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 2] < BLOCK_LVL1) || (field->values[y - 1][x - 2] > BLOCK_LVL3)) ? (field->values[y - 1][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 1] < BLOCK_LVL1) || (field->values[y - 1][x - 1] > BLOCK_LVL3)) ? (field->values[y - 1][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x] < BLOCK_LVL1) || (field->values[y - 1][x] > BLOCK_LVL3)) ? (field->values[y - 1][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 1] < BLOCK_LVL1) || (field->values[y - 1][x + 1] > BLOCK_LVL3)) ? (field->values[y - 1][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 2] < BLOCK_LVL1) || (field->values[y - 1][x + 2] > BLOCK_LVL3)) ? (field->values[y - 1][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x - 1] < BLOCK_LVL1) || (field->values[y - 2][x - 1] > BLOCK_LVL3)) ? (field->values[y - 2][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x] < BLOCK_LVL1) || (field->values[y - 2][x] > BLOCK_LVL3)) ? (field->values[y - 2][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x + 1] < BLOCK_LVL1) || (field->values[y - 2][x + 1] > BLOCK_LVL3)) ? (field->values[y - 2][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x - 1] < BLOCK_LVL1) || (field->values[y - 3][x - 1] > BLOCK_LVL3)) ? (field->values[y - 3][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x] < BLOCK_LVL1) || (field->values[y - 3][x] > BLOCK_LVL3)) ? (field->values[y - 3][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x + 1] < BLOCK_LVL1) || (field->values[y - 3][x + 1] > BLOCK_LVL3)) ? (field->values[y - 3][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x] < BLOCK_LVL1) || (field->values[y - 4][x] > BLOCK_LVL3)) ? (field->values[y - 4][x] = state) : (field->gameStatus = GAMEOVER);
}

void shipSetWing(field_t *field, int y, int x, int state)
{
    state = (state) ? (SHIP) : (EMPTY);
    ((field->values[y][x - 1] < BLOCK_LVL1) || (field->values[y][x - 1] > BLOCK_LVL3)) ? (field->values[y][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y][x + 1] < BLOCK_LVL1) || (field->values[y][x + 1] > BLOCK_LVL3)) ? (field->values[y][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 2] < BLOCK_LVL1) || (field->values[y - 1][x - 2] > BLOCK_LVL3)) ? (field->values[y - 1][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 1] < BLOCK_LVL1) || (field->values[y - 1][x - 1] > BLOCK_LVL3)) ? (field->values[y - 1][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x] < BLOCK_LVL1) || (field->values[y - 1][x] > BLOCK_LVL3)) ? (field->values[y - 1][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 1] < BLOCK_LVL1) || (field->values[y - 1][x + 1] > BLOCK_LVL3)) ? (field->values[y - 1][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 2] < BLOCK_LVL1) || (field->values[y - 1][x + 2] > BLOCK_LVL3)) ? (field->values[y - 1][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x - 2] < BLOCK_LVL1) || (field->values[y - 2][x - 2] > BLOCK_LVL3)) ? (field->values[y - 2][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x] < BLOCK_LVL1) || (field->values[y - 2][x] > BLOCK_LVL3)) ? (field->values[y - 2][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x + 2] < BLOCK_LVL1) || (field->values[y - 2][x + 2] > BLOCK_LVL3)) ? (field->values[y - 2][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x] < BLOCK_LVL1) || (field->values[y - 3][x] > BLOCK_LVL3)) ? (field->values[y - 3][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x] < BLOCK_LVL1) || (field->values[y - 4][x] > BLOCK_LVL3)) ? (field->values[y - 4][x] = state) : (field->gameStatus = GAMEOVER);
    
}

void shipSetVertigo(field_t *field, int y, int x, int state)
{
    state = (state) ? (SHIP) : (EMPTY);
    ((field->values[y][x - 2] < BLOCK_LVL1) || (field->values[y][x - 2] > BLOCK_LVL3)) ? (field->values[y][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y][x + 2] < BLOCK_LVL1) || (field->values[y][x + 2] > BLOCK_LVL3)) ? (field->values[y][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 2] < BLOCK_LVL1) || (field->values[y - 1][x - 2] > BLOCK_LVL3)) ? (field->values[y - 1][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 1] < BLOCK_LVL1) || (field->values[y - 1][x - 1] > BLOCK_LVL3)) ? (field->values[y - 1][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 1] < BLOCK_LVL1) || (field->values[y - 1][x + 1] > BLOCK_LVL3)) ? (field->values[y - 1][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 2] < BLOCK_LVL1) || (field->values[y - 1][x + 2] > BLOCK_LVL3)) ? (field->values[y - 1][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x - 1] < BLOCK_LVL1) || (field->values[y - 2][x - 1] > BLOCK_LVL3)) ? (field->values[y - 2][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x] < BLOCK_LVL1) || (field->values[y - 2][x] > BLOCK_LVL3)) ? (field->values[y - 2][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x + 1] < BLOCK_LVL1) || (field->values[y - 2][x + 1] > BLOCK_LVL3)) ? (field->values[y - 2][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x] < BLOCK_LVL1) || (field->values[y - 3][x] > BLOCK_LVL3)) ? (field->values[y - 3][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x] < BLOCK_LVL1) || (field->values[y - 4][x] > BLOCK_LVL3)) ? (field->values[y - 4][x] = state) : (field->gameStatus = GAMEOVER);
    
}

void shipSetYomen(field_t *field, int y, int x, int state)
{
    state = (state) ? (SHIP) : (EMPTY);
    ((field->values[y][x - 2] < BLOCK_LVL1) || (field->values[y][x - 2] > BLOCK_LVL3)) ? (field->values[y][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y][x + 2] < BLOCK_LVL1) || (field->values[y][x + 2] > BLOCK_LVL3)) ? (field->values[y][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 2] < BLOCK_LVL1) || (field->values[y - 1][x - 2] > BLOCK_LVL3)) ? (field->values[y - 1][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 1] < BLOCK_LVL1) || (field->values[y - 1][x - 1] > BLOCK_LVL3)) ? (field->values[y - 1][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 1] < BLOCK_LVL1) || (field->values[y - 1][x + 1] > BLOCK_LVL3)) ? (field->values[y - 1][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 2] < BLOCK_LVL1) || (field->values[y - 1][x + 2] > BLOCK_LVL3)) ? (field->values[y - 1][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x - 1] < BLOCK_LVL1) || (field->values[y - 2][x - 1] > BLOCK_LVL3)) ? (field->values[y - 2][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x] < BLOCK_LVL1) || (field->values[y - 2][x] > BLOCK_LVL3)) ? (field->values[y - 2][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x + 1] < BLOCK_LVL1) || (field->values[y - 2][x + 1] > BLOCK_LVL3)) ? (field->values[y - 2][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x - 2] < BLOCK_LVL1) || (field->values[y - 3][x - 2] > BLOCK_LVL3)) ? (field->values[y - 3][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x] < BLOCK_LVL1) || (field->values[y - 3][x] > BLOCK_LVL3)) ? (field->values[y - 3][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x + 2] < BLOCK_LVL1) || (field->values[y - 3][x + 2] > BLOCK_LVL3)) ? (field->values[y - 3][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x] < BLOCK_LVL1) || (field->values[y - 4][x] > BLOCK_LVL3)) ? (field->values[y - 4][x] = state) : (field->gameStatus = GAMEOVER);
    
}

void shipSetOmega(field_t *field, int y, int x, int state)
{
    state = (state) ? (SHIP) : (EMPTY);
    ((field->values[y][x - 1] < BLOCK_LVL1) || (field->values[y][x - 1] > BLOCK_LVL3)) ? (field->values[y][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y][x + 1] < BLOCK_LVL1) || (field->values[y][x + 1] > BLOCK_LVL3)) ? (field->values[y][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 2] < BLOCK_LVL1) || (field->values[y - 1][x - 2] > BLOCK_LVL3)) ? (field->values[y - 1][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 1] < BLOCK_LVL1) || (field->values[y - 1][x - 1] > BLOCK_LVL3)) ? (field->values[y - 1][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x] < BLOCK_LVL1) || (field->values[y - 1][x] > BLOCK_LVL3)) ? (field->values[y - 1][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 1] < BLOCK_LVL1) || (field->values[y - 1][x + 1] > BLOCK_LVL3)) ? (field->values[y - 1][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 2] < BLOCK_LVL1) || (field->values[y - 1][x + 2] > BLOCK_LVL3)) ? (field->values[y - 1][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x - 1] < BLOCK_LVL1) || (field->values[y - 2][x - 1] > BLOCK_LVL3)) ? (field->values[y - 2][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x + 1] < BLOCK_LVL1) || (field->values[y - 2][x + 1] > BLOCK_LVL3)) ? (field->values[y - 2][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x - 2] < BLOCK_LVL1) || (field->values[y - 3][x - 2] > BLOCK_LVL3)) ? (field->values[y - 3][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x - 1] < BLOCK_LVL1) || (field->values[y - 3][x - 1] > BLOCK_LVL3)) ? (field->values[y - 3][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x] < BLOCK_LVL1) || (field->values[y - 3][x] > BLOCK_LVL3)) ? (field->values[y - 3][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x + 1] < BLOCK_LVL1) || (field->values[y - 3][x + 1] > BLOCK_LVL3)) ? (field->values[y - 3][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x + 2] < BLOCK_LVL1) || (field->values[y - 3][x + 2] > BLOCK_LVL3)) ? (field->values[y - 3][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x - 1] < BLOCK_LVL1) || (field->values[y - 4][x - 1] > BLOCK_LVL3)) ? (field->values[y - 4][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x + 1] < BLOCK_LVL1) || (field->values[y - 4][x + 1] > BLOCK_LVL3)) ? (field->values[y - 4][x + 1] = state) : (field->gameStatus = GAMEOVER);
    
}

void shipSetHero(field_t *field, int y, int x, int state)
{
    state = (state) ? (SHIP) : (EMPTY);
    ((field->values[y][x - 2] < BLOCK_LVL1) || (field->values[y][x - 2] > BLOCK_LVL3)) ? (field->values[y][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y][x + 2] < BLOCK_LVL1) || (field->values[y][x + 2] > BLOCK_LVL3)) ? (field->values[y][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 2] < BLOCK_LVL1) || (field->values[y - 1][x - 2] > BLOCK_LVL3)) ? (field->values[y - 1][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 1] < BLOCK_LVL1) || (field->values[y - 1][x - 1] > BLOCK_LVL3)) ? (field->values[y - 1][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 1] < BLOCK_LVL1) || (field->values[y - 1][x + 1] > BLOCK_LVL3)) ? (field->values[y - 1][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 2] < BLOCK_LVL1) || (field->values[y - 1][x + 2] > BLOCK_LVL3)) ? (field->values[y - 1][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x - 1] < BLOCK_LVL1) || (field->values[y - 2][x - 1] > BLOCK_LVL3)) ? (field->values[y - 2][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x] < BLOCK_LVL1) || (field->values[y - 2][x] > BLOCK_LVL3)) ? (field->values[y - 2][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x + 1] < BLOCK_LVL1) || (field->values[y - 2][x + 1] > BLOCK_LVL3)) ? (field->values[y - 2][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x - 1] < BLOCK_LVL1) || (field->values[y - 3][x - 1] > BLOCK_LVL3)) ? (field->values[y - 3][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x + 1] < BLOCK_LVL1) || (field->values[y - 3][x + 1] > BLOCK_LVL3)) ? (field->values[y - 3][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x - 1] < BLOCK_LVL1) || (field->values[y - 4][x - 1] > BLOCK_LVL3)) ? (field->values[y - 4][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x + 1] < BLOCK_LVL1) || (field->values[y - 4][x + 1] > BLOCK_LVL3)) ? (field->values[y - 4][x + 1] = state) : (field->gameStatus = GAMEOVER);
    
}

void shipSetSkull(field_t *field, int y, int x, int state)
{
    state = (state) ? (SHIP) : (EMPTY);
    ((field->values[y][x - 1] < BLOCK_LVL1) || (field->values[y][x - 1] > BLOCK_LVL3)) ? (field->values[y][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y][x + 1] < BLOCK_LVL1) || (field->values[y][x + 1] > BLOCK_LVL3)) ? (field->values[y][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 2] < BLOCK_LVL1) || (field->values[y - 1][x - 2] > BLOCK_LVL3)) ? (field->values[y - 1][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x - 1] < BLOCK_LVL1) || (field->values[y - 1][x - 1] > BLOCK_LVL3)) ? (field->values[y - 1][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 1] < BLOCK_LVL1) || (field->values[y - 1][x + 1] > BLOCK_LVL3)) ? (field->values[y - 1][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 1][x + 2] < BLOCK_LVL1) || (field->values[y - 1][x + 2] > BLOCK_LVL3)) ? (field->values[y - 1][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x - 2] < BLOCK_LVL1) || (field->values[y - 2][x - 2] > BLOCK_LVL3)) ? (field->values[y - 2][x - 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x] < BLOCK_LVL1) || (field->values[y - 2][x] > BLOCK_LVL3)) ? (field->values[y - 2][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 2][x + 2] < BLOCK_LVL1) || (field->values[y - 2][x + 2] > BLOCK_LVL3)) ? (field->values[y - 2][x + 2] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x - 1] < BLOCK_LVL1) || (field->values[y - 3][x - 1] > BLOCK_LVL3)) ? (field->values[y - 3][x - 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x] < BLOCK_LVL1) || (field->values[y - 3][x] > BLOCK_LVL3)) ? (field->values[y - 3][x] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 3][x + 1] < BLOCK_LVL1) || (field->values[y - 3][x + 1] > BLOCK_LVL3)) ? (field->values[y - 3][x + 1] = state) : (field->gameStatus = GAMEOVER);
    ((field->values[y - 4][x] < BLOCK_LVL1) || (field->values[y - 4][x] > BLOCK_LVL3)) ? (field->values[y - 4][x] = state) : (field->gameStatus = GAMEOVER);
    
}

int bulletMove(field_t *field, int y, int x)
{
    if (y < 0) {
        field->values[y + 1][x] = EMPTY;
        field->score += -1;
        return -1;
    }
    switch (field->values[y][x]) {
    case BLOCK_LVL1:
        field->values[y + 1][x] = EMPTY;
        field->values[y][x] = EMPTY;
        field->score += 2;
        return 1;
    case BLOCK_LVL2:
        field->values[y + 1][x] = EMPTY;
        field->values[y][x] = BLOCK_LVL1;
        field->score += 3;
        return 1;
    case BLOCK_LVL3:
        field->values[y + 1][x] = EMPTY;
        field->values[y][x] = BLOCK_LVL2;
        field->score += 4;
        return 1;
    }
    field->values[y][x] = BULLET;
    field->values[y + 1][x] = EMPTY;
    return 0;
}
