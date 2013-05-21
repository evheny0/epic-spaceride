#include <stdlib.h>
#include <pthread.h>

enum field_values {
    EMPTY,
    SHIP,
    BULLET,
    BLOCK_LVL1,
    BLOCK_LVL2,
    BLOCK_LVL3
};

typedef struct coord_t {
    int x;
    int y;
} coord_t;

typedef struct field_t {
    int sizeX;
    int sizeY;
    coord_t shipLocation;
    int **values;
    int score;
    int isGameover;
} field_t;


field_t *fieldInit();
void *generateBlocks(void *vptr_args);
