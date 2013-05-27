#include "engine.h"

void engineInit(field_t *field)
{
    pthread_t engineThread;
    field->gameStatus = START_MENU;
    pthread_create(&engineThread, NULL, gameEngine, (void *) field);
}

void *gameEngine(void *vptr_args)
{
    field_t *field;
    field = vptr_args;
    pthread_t blocksThread;
    while (field->gameStatus != EXIT) {
        switch (field->gameStatus) {
        case START_MENU:
            clearField(field);
            shipInit(field);
            motionOfShipAtStart(field);
            removeShip(field, field->shipLocation.y, field->shipLocation.x);
            shipInit(field);
            break;
        case GAME_IN_PROCESS:
            pthread_create(&blocksThread, NULL, generateBlocks, (void *) field);
            pthread_join(blocksThread, NULL);
            break;
        case GAMEOVER:
            clearField(field);
            break;
        case EXIT:
            clearField(field);
            return NULL;
        }
    }
    return NULL;
}

void motionOfShipAtStart(field_t *field)
{
    int direction = 1;
    while (field->gameStatus == START_MENU) {
        if ((field->shipLocation.x + 3) == field->size.x || (field->shipLocation.x - 3) < 0) {
            direction = -direction;
        }
        shipMove(field, 0, direction);
        usleep(100000);
    }
}

void *generateBlocks(void *vptr_args)
{
    field_t *field;
    field = vptr_args;

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
