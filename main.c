#include <stdlib.h>
#include <math.h>
#include "GUI.h"

int main(int argc, char **argv)
{
    field_t *field;
    field = fieldInit();
    shipInit(field);
    GUIInit(field);
    return 0;
}
