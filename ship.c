#include "ship.h"

void shipMove(field_t *field, int y, int x)
{
    field->values[field->shipLocation.y][field->shipLocation.x - 1] = EMPTY;
    field->values[field->shipLocation.y][field->shipLocation.x + 1] = EMPTY;
    field->values[field->shipLocation.y - 1][field->shipLocation.x] = EMPTY;
    field->values[field->shipLocation.y - 1][field->shipLocation.x - 2] = EMPTY;
    field->values[field->shipLocation.y - 1][field->shipLocation.x - 1] = EMPTY;
    field->values[field->shipLocation.y - 1][field->shipLocation.x + 1] = EMPTY;
    field->values[field->shipLocation.y - 1][field->shipLocation.x + 2] = EMPTY;
    field->values[field->shipLocation.y - 2][field->shipLocation.x] = EMPTY;
    field->values[field->shipLocation.y - 2][field->shipLocation.x - 1] = EMPTY;
    field->values[field->shipLocation.y - 2][field->shipLocation.x + 1] = EMPTY;
    field->values[field->shipLocation.y - 3][field->shipLocation.x] = EMPTY;


    field->shipLocation.x += x;
    ((field->shipLocation.x) == field->sizeX || (field->shipLocation.x) < 0) ? field->shipLocation.x -= x : x;
    field->shipLocation.y += y;
    (field->shipLocation.y == field->sizeY || (field->shipLocation.y - 3) < 0) ? field->shipLocation.y -= y : y;

    if ((field->values[field->shipLocation.y][field->shipLocation.x - 1] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y][field->shipLocation.x + 1] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 1][field->shipLocation.x] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 1][field->shipLocation.x - 2] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 1][field->shipLocation.x - 1] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 1][field->shipLocation.x + 1] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 1][field->shipLocation.x + 2] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 2][field->shipLocation.x] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 2][field->shipLocation.x - 1] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 2][field->shipLocation.x + 1] == BLOCK_LVL1) ||
        (field->values[field->shipLocation.y - 3][field->shipLocation.x])) {
        field->isGameover = 1;
    }
    field->values[field->shipLocation.y][field->shipLocation.x - 1] = SHIP;
    field->values[field->shipLocation.y][field->shipLocation.x + 1] = SHIP;
    field->values[field->shipLocation.y - 1][field->shipLocation.x] = SHIP;
    field->values[field->shipLocation.y - 1][field->shipLocation.x - 2] = SHIP;
    field->values[field->shipLocation.y - 1][field->shipLocation.x - 1] = SHIP;
    field->values[field->shipLocation.y - 1][field->shipLocation.x + 1] = SHIP;
    field->values[field->shipLocation.y - 1][field->shipLocation.x + 2] = SHIP;
    field->values[field->shipLocation.y - 2][field->shipLocation.x] = SHIP;
    field->values[field->shipLocation.y - 2][field->shipLocation.x - 1] = SHIP;
    field->values[field->shipLocation.y - 2][field->shipLocation.x + 1] = SHIP;
    field->values[field->shipLocation.y - 3][field->shipLocation.x] = SHIP;
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
