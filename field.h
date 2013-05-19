#include <stdlib.h>
#include <pthread.h>

enum field_values {
    EMPTY,
    SHIP,
    BULLET,
    BLOCK,
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
static void *generateBlocks(void *vptr_args);
