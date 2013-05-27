#include "field.h"
#include <stdio.h>

field_t *fieldInit()
{
    int i;
    field_t *field;

    field = (field_t *) calloc(1, sizeof(field_t));
    field->size.x = 20;
    field->size.y = 40;

    field->values = (int **) calloc(field->size.y, sizeof(int *));
    for (i = 0; i < field->size.y; i++) {
        field->values[i] = (int *) calloc(field->size.x, sizeof(int));
    }

    return field;
}

void clearField(field_t *field)
{
    int i, j;
    field->score = 0;
    for (i = 0; i < field->size.y; i++) {
        for (j = 0; j < field->size.x; j++) {
            field->values[i][j] = EMPTY;
        }
    }
}

void freeField(field_t *field)
{
    int i;
    for (i = 0; i < field->size.y; i++) {
        free(field->values[i]);
    }
    free(field);
}
