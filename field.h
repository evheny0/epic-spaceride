#include <stdlib.h>

enum field_values {
    EMPTY,
    CURSOR,
    SHIP,
    BULLET,
    BLOCK_LVL1,
    BLOCK_LVL2,
    BLOCK_LVL3
};

enum GAME_STATUS {
    START_MENU,
    GAME_IN_PROCESS,
    GAMEOVER,
    WIN,
    EXIT
};

typedef struct coord_t {
    int x;
    int y;
} coord_t;

typedef struct field_t {
    coord_t size;
    coord_t shipLocation;
    int shipType;
    int **values;
    int score;
    int gameStatus;
} field_t;


field_t *fieldInit();
void clearField(field_t *field);
void freeField(field_t *field);
