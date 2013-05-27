#include "GUI.h"

int main(int argc, char **argv)
{
    field_t *field;
    field = fieldInit();
    engineInit(field);
    GUIInit(field);
    return 0;
}
