#include <gtk/gtk.h>
#include <pthread.h>
#include "graphics.h"

void GUIInit(field_t *field);
gboolean keyPress(GtkWidget *window, GdkEventKey *event, field_t *field);
void startMenuKeys(int keyval, field_t *field);
void gameKeys(int keyval, field_t *field);
void *bulletStart(void *vptr_args);
void closeButton(GtkWidget *window, field_t *field);
