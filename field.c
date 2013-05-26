#include "field.h"
#include <stdio.h>

field_t *fieldInit()
{
    int i;
    pthread_t blocksThread;

    field_t *field;
    field = (field_t *) calloc(1, sizeof(field_t));
    field->size.x = 20;
    field->size.y = 40;

    field->values = (int **) calloc(field->size.y, sizeof(int *));
    for (i = 0; i < field->size.y; i++) {
        field->values[i] = (int *) calloc(field->size.x, sizeof(int));
    }

    field->gameStatus = START_MENU;

    pthread_create(&blocksThread, NULL, generateBlocks, (void *) field);

    return field;
}
    
void *generateBlocks(void *vptr_args)  //move to game engine
{
    field_t *field;
    field = vptr_args;
    int direction = 1;
    while (field->gameStatus == START_MENU) {
        if ((field->shipLocation.x + 3) == field->size.x || (field->shipLocation.x - 3) < 0) {
            direction = -direction;
        }
        shipMove(field, 0, direction);
        usleep(100000);
    }
    removeShip(field, field->shipLocation.y, field->shipLocation.x);
    shipInit(field);

    int i, j;
    int modifierTime;
    const int timeConst = 2000000;
    for (modifierTime = 0; (modifierTime < timeConst) && (field->gameStatus != GAMEOVER); modifierTime += 10000) {  //need to more powerful time algorithm
        /* checking last line for blocks */
        for (i = 0; i < field->size.x; i++) {
            if ((field->values[field->size.y - 2][i] == BLOCK_LVL1) ||
                (field->values[field->size.y - 2][i] == BLOCK_LVL2) ||
                (field->values[field->size.y - 2][i] == BLOCK_LVL3)) {
                field->gameStatus = GAMEOVER;
                return NULL;
            }
        }
        /* moving blocks */
        for (i = field->size.y - 2; i > 0; i--) {
            for (j = 0; j < field->size.x; j++) {
                switch (field->values[i][j]) {
                case SHIP:
                    if (field->values[i - 1][j] == BLOCK_LVL1 ||
                        field->values[i - 1][j] == BLOCK_LVL2 ||
                        field->values[i - 1][j] == BLOCK_LVL3) {
                        field->gameStatus = GAMEOVER;
                        return NULL;
                    }
                    break;
                case BULLET:
                    break;
                case EMPTY:
                    if (field->values[i - 1][j] == BLOCK_LVL1 ||
                        field->values[i - 1][j] == BLOCK_LVL2 ||
                        field->values[i - 1][j] == BLOCK_LVL3) {
                        field->values[i][j] = field->values[i - 1][j];
                    }
                    break;
                default:
                    switch (field->values[i - 1][j]) {
                    case SHIP:
                        field->values[i][j] = EMPTY;
                        break;
                    case BULLET:
                        field->values[i][j] = EMPTY;
                        break;
                    case EMPTY:
                        field->values[i][j] = EMPTY;
                        break;
                    default:
                        field->values[i][j] = field->values[i - 1][j];
                        break;
                    }
                    break;
                }
            }
        }
        /* generation the new line of blocks */
        for (i = 0; i < field->size.x; i++) {
            if (field->values[0][i] == SHIP) {
                field->gameStatus = GAMEOVER;
            }
            if (rand() % 2) {
                if (!(rand() % 5)) {
                    if (!(rand() % 3)) {
                        field->values[0][i] = BLOCK_LVL3;
                    } else {
                        field->values[0][i] = BLOCK_LVL2;
                    }
                } else {
                    field->values[0][i] = BLOCK_LVL1;
                }
            } else {
                field->values[0][i] = EMPTY;
            }
        }
        usleep(timeConst - modifierTime);
    }
    //field->gameStatus = WIN;
    return NULL;
}
