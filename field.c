#include "field.h"
#include <stdio.h>

field_t *fieldInit()
{
    int i;
    pthread_t blocksThread;

    field_t *field;
    field = (field_t *) calloc(1, sizeof(field_t));
    field->sizeX = 20;
    field->sizeY = 40;

    field->values = (int **) calloc(field->sizeY, sizeof(int *));
    for (i = 0; i < field->sizeY; i++) {
        field->values[i] = (int *) calloc(field->sizeX, sizeof(int));
    }

    pthread_create(&blocksThread, NULL, generateBlocks, (void *) field);

    return field;
}
    
void *generateBlocks(void *vptr_args)
{
    field_t *field;
    field = vptr_args;

    int i, j;
    int modifierTime;
    const int timeConst = 2000000;

    for (modifierTime = 0; modifierTime < timeConst && !field->isGameover; modifierTime += 10000) {  //need to more powerful time algorithm
        /* finding the line without the blocks */
        for (i = 0; i < field->sizeX; i++) {
            if ((field->values[field->sizeY - 2][i] == BLOCK_LVL1) ||
                (field->values[field->sizeY - 2][i] == BLOCK_LVL2) ||
                (field->values[field->sizeY - 2][i] == BLOCK_LVL3)) {
                field->isGameover = 1;
                return NULL;
            }
        }
        /* moving blocks */
        for (i = field->sizeY - 2; i > 0; i--) {
            for (j = 0; j < field->sizeX; j++) {
                switch (field->values[i][j]) {
                case SHIP:
                    if (field->values[i - 1][j] == BLOCK_LVL1 ||
                        field->values[i - 1][j] == BLOCK_LVL2 ||
                        field->values[i - 1][j] == BLOCK_LVL3) {
                        field->isGameover = 1;
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
        for (i = 0; i < field->sizeX; i++) {
            if (field->values[0][i] == SHIP) {
                field->isGameover = 1;
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
    field->isGameover = 2;
    return NULL;
}
