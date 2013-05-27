#include "ship.h"
#include <pthread.h>
#include <unistd.h>

void engineInit(field_t *field);
void *gameEngine(void *vptr_args);
void motionOfShipAtStart(field_t *field);
void *generateBlocks(void *vptr_args);
