#include "graphics.h"

const int pixelConst = 16;  //need move to header
int isExit = 0;

void graphicsInit(GtkWidget *frame, field_t *field)
{
    GtkWidget *darea;
    darea = gtk_drawing_area_new();
    gtk_fixed_put(GTK_FIXED(frame), darea, 0, 0);
    gtk_widget_set_size_request(darea, field->size.x * pixelConst + 10 + 100, field->size.y * pixelConst + 10);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), field);
    g_timeout_add(10, (GSourceFunc) screenUpdate, darea);  //condition to stop
}

void graphicsDestroy()
{
    isExit = 1;
}

gboolean screenUpdate(GtkWidget *darea)
{
    if (isExit) {
        return FALSE;
    }
    gtk_widget_queue_draw(darea);
    return TRUE;
}

gboolean on_draw_event(GtkWidget *darea, cairo_t *cairoDrawPlace, field_t *field)
{
    cairoDrawPlace = gdk_cairo_create(gtk_widget_get_window(darea));
    do_drawing(cairoDrawPlace, darea, field);
    cairo_destroy(cairoDrawPlace);
    return FALSE;
}

void do_drawing(cairo_t *cairoDrawPlace, GtkWidget *darea, field_t *field)
{
    cairo_set_source_rgb(cairoDrawPlace, 0.26, 0.07, 0.69);
    cairo_paint(cairoDrawPlace);
    cairo_set_line_width(cairoDrawPlace, 2);
    cairo_set_line_cap(cairoDrawPlace, CAIRO_LINE_CAP_ROUND);
    cairo_translate(cairoDrawPlace, 5, 5);

    switch (field->gameStatus) {
    case START_MENU:
        startMenuDraw(cairoDrawPlace, field);
        break;
    case GAME_IN_PROCESS:
        fieldDraw(cairoDrawPlace, field);
        break;
    case GAMEOVER:
        gameoverDraw(cairoDrawPlace, field);
        break;
    }
    rightMenuDraw(cairoDrawPlace, field);
    //cairo_stroke(cairoDrawPlace);
}

void startMenuDraw(cairo_t *cairoDrawPlace, field_t *field)
{
    int i, j;
    char shipName[20][20] = {"ARCANE",
                             "WING",
                             "VERTIGO",
                             "YOMEN",
                             "OMEGA", 
                             "HERO",
                             "SKULL"};
    cairo_set_source_rgba(cairoDrawPlace, 1, 1, 1, 1);
    cairo_set_font_size(cairoDrawPlace, 16);
    cairo_move_to(cairoDrawPlace, 7 * pixelConst, 2 * pixelConst);
    cairo_show_text(cairoDrawPlace, "Choose ship:"); 
    for (i = 0; i <= SKULL; i++) {
        if (field->shipType == i) {
            cairo_rectangle(cairoDrawPlace, 6 * pixelConst, 2 * (i + 2) * pixelConst, pixelConst, -pixelConst);
        }
        cairo_move_to(cairoDrawPlace, 8 * pixelConst, 2 * (i + 2) * pixelConst - 1);
        cairo_show_text(cairoDrawPlace, shipName[i]); 
    }
    cairo_move_to(cairoDrawPlace, pixelConst, 2 * (i + 4) * pixelConst);
    cairo_show_text(cairoDrawPlace, "Arrows - move."); 
    cairo_move_to(cairoDrawPlace,  pixelConst, 2 * (i + 5) * pixelConst);
    cairo_show_text(cairoDrawPlace, "'z' - fire/start."); 
    cairo_stroke(cairoDrawPlace);

    for (i = 0; i < field->size.y; i++) {
        for (j = 0; j < field->size.x; j++) {
            if (field->values[i][j] == SHIP) {
                cairo_set_source_rgba(cairoDrawPlace, 1, 0.85, 0, 1);
                cairo_rectangle(cairoDrawPlace, j * pixelConst, i * pixelConst, pixelConst, pixelConst);
                cairo_fill(cairoDrawPlace);
                cairo_stroke(cairoDrawPlace);
            }
        }
    }
    cairo_stroke(cairoDrawPlace);
}

void fieldDraw(cairo_t *cairoDrawPlace, field_t *field)
{
    int i, j;
    for (i = 0; i < field->size.y; i++) {
        for (j = 0; j < field->size.x; j++) {
            switch (field->values[i][j]) {
            case SHIP:
                cairo_set_source_rgba(cairoDrawPlace, 1, 0.85, 0, 1);
                cairo_rectangle(cairoDrawPlace, j * pixelConst, i * pixelConst, pixelConst, pixelConst);
                cairo_fill(cairoDrawPlace);
                cairo_stroke(cairoDrawPlace);
                break;
            case BLOCK_LVL1:
                cairo_set_source_rgba(cairoDrawPlace, 1, 1, 1, 1);
                cairo_rectangle(cairoDrawPlace, j * pixelConst, i * pixelConst, pixelConst, pixelConst);
                cairo_fill(cairoDrawPlace);
                cairo_stroke(cairoDrawPlace);
                break;
            case BLOCK_LVL2:
                cairo_set_source_rgba(cairoDrawPlace, 0.5 , 0.5, 0.5, 1);  //127
                cairo_rectangle(cairoDrawPlace, j * pixelConst, i * pixelConst, pixelConst, pixelConst);
                cairo_fill(cairoDrawPlace);
                cairo_stroke(cairoDrawPlace);
                break;
            case BLOCK_LVL3:
                cairo_set_source_rgba(cairoDrawPlace, 0.25, 0.25, 0.25, 1);  //64
                cairo_rectangle(cairoDrawPlace, j * pixelConst, i * pixelConst, pixelConst, pixelConst);
                cairo_fill(cairoDrawPlace);
                cairo_stroke(cairoDrawPlace);
                break;
            case BULLET:
                cairo_set_source_rgba(cairoDrawPlace, 0, 0, 0, 1);
                cairo_arc(cairoDrawPlace, j * pixelConst + (pixelConst / 2), 
                                          i * pixelConst + (pixelConst / 2), 
                                          pixelConst / 4, 0, 2 * 3.14);
                cairo_fill(cairoDrawPlace);
                cairo_stroke(cairoDrawPlace);
                break;
            }
        }
    }
}

void rightMenuDraw(cairo_t *cairoDrawPlace, field_t *field)
{
    cairo_set_source_rgba(cairoDrawPlace, 1, 1, 1, 1);
    cairo_move_to(cairoDrawPlace, pixelConst * field->size.x + 5, 0);
    cairo_line_to(cairoDrawPlace, pixelConst * field->size.x + 5, pixelConst * field->size.y);
    cairo_translate(cairoDrawPlace, pixelConst * field->size.x + 10, 5);
    cairo_set_font_size(cairoDrawPlace, 16);
    setImage(cairoDrawPlace, "image/score.png", 4, 0);
    setImageOfNumber(cairoDrawPlace, field->score, 5, 2, 32);
    cairo_stroke(cairoDrawPlace);
}

void gameoverDraw(cairo_t *cairoDrawPlace, field_t *field)
{
    cairo_set_source_rgba(cairoDrawPlace, 1, 1, 1, 1);
    cairo_set_font_size(cairoDrawPlace, 16);
    cairo_move_to(cairoDrawPlace, ((field->size.x / 2) - 3) * pixelConst, (field->size.y / 2) * pixelConst);
    cairo_show_text(cairoDrawPlace, "GAME OVER");  
    cairo_move_to(cairoDrawPlace, ((field->size.x / 2) - 3) * pixelConst + 3, (field->size.y / 2 + 3) * pixelConst);
    cairo_show_text(cairoDrawPlace, "Z to restart.");  
    cairo_stroke(cairoDrawPlace);
}

void setImage(cairo_t *cairoDrawPlace, char *path, int x, int y)
{
    cairo_stroke(cairoDrawPlace);

    cairo_surface_t *surface;
    surface = cairo_image_surface_create_from_png(path);
    cairo_set_source_surface(cairoDrawPlace, surface, x, y);
    cairo_rectangle(cairoDrawPlace, x, y, cairo_image_surface_get_width(surface), cairo_image_surface_get_height(surface));
    cairo_fill(cairoDrawPlace);
    cairo_stroke(cairoDrawPlace);
    cairo_surface_destroy(surface);
}

void setImageOfNumber(cairo_t *cairoDrawPlace, int number, int numberLength, int x, int y)
{
    cairo_stroke(cairoDrawPlace);

    int i, digit;
    cairo_surface_t *surface;
    surface = cairo_image_surface_create_from_png("image/numbers.png");
    for (i = 0; i < numberLength; i++) {
        digit = (number / (int) pow(10, numberLength - i - 1)) % 10;
        cairo_set_source_surface(cairoDrawPlace, surface, x + (i * 18) - (15 * digit), y);
        cairo_rectangle(cairoDrawPlace, x + (i * 18), y, cairo_image_surface_get_width(surface) / 10, cairo_image_surface_get_height(surface));
        cairo_fill(cairoDrawPlace);
    }
    cairo_stroke(cairoDrawPlace);
    cairo_surface_destroy(surface);
}
