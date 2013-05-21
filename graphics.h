#include "ship.h"
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

gboolean on_draw_event(GtkWidget *darea, cairo_t *cairoDrawPlace, field_t *field);
void do_drawing(cairo_t *cairoDrawPlace, GtkWidget *darea, field_t *field);
void fieldDraw(cairo_t *cairoDrawPlace, field_t *field);
void menuDraw(cairo_t *cairoDrawPlace, field_t *field);
void gameoverDraw(cairo_t *cairoDrawPlace, field_t *field);
void graphicsInit(GtkWidget *frame, field_t *field);
gboolean screenUpdate(GtkWidget *darea);
