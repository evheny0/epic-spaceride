#include "ship.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include <math.h>

gboolean on_draw_event(GtkWidget *darea, cairo_t *cairoDrawPlace, field_t *field);
void do_drawing(cairo_t *cairoDrawPlace, GtkWidget *darea, field_t *field);
void startMenuDraw(cairo_t *cairoDrawPlace, field_t *field);
void fieldDraw(cairo_t *cairoDrawPlace, field_t *field);
void rightMenuDraw(cairo_t *cairoDrawPlace, field_t *field);
void gameoverDraw(cairo_t *cairoDrawPlace, field_t *field);
void graphicsInit(GtkWidget *frame, field_t *field);
gboolean screenUpdate(GtkWidget *darea);

void setImage(cairo_t *cairoDrawPlace, char *path, int x, int y);
void setImageOfNumber(cairo_t *cairoDrawPlace, int number, int numberLength, int x, int y);
