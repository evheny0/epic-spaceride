#include "graphics.h"

const int pixelConst = 16;  //need move to header

void graphicsInit(GtkWidget *frame, field_t *field)
{
    GtkWidget *darea;
    darea = gtk_drawing_area_new();
    gtk_fixed_put(GTK_FIXED(frame), darea, 0, 0);
    gtk_widget_set_size_request(darea, field->sizeX * pixelConst + 10 + 100, field->sizeY * pixelConst + 10);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), field);
    g_timeout_add(10, (GSourceFunc) screenUpdate, darea);  //condition required to complete 
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
    if (field->isGameover) {
        gameoverDraw(cairoDrawPlace, field);
    } else {
        fieldDraw(cairoDrawPlace, field);
    }
    menuDraw(cairoDrawPlace, field);
    cairo_stroke(cairoDrawPlace);
}

gboolean screenUpdate(GtkWidget *darea)
{
    gtk_widget_queue_draw(darea);
    return TRUE;
}

void fieldDraw(cairo_t *cairoDrawPlace, field_t *field)
{
    int i, j;
    for (i = 0; i < field->sizeY; i++) {
        for (j = 0; j < field->sizeX; j++) {
            switch (field->values[i][j]) {
            case SHIP:
                cairo_set_source_rgba(cairoDrawPlace, 1, 0.85, 0, 1);
                cairo_rectangle(cairoDrawPlace, j * pixelConst, i * pixelConst, pixelConst, pixelConst);
                //cairo_fill(cairoDrawPlace);
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
                //cairo_rectangle(cairoDrawPlace, j * pixelConst, i * pixelConst, pixelConst, pixelConst);
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

void menuDraw(cairo_t *cairoDrawPlace, field_t *field)
{
    /*cairo_surface_t *image;
    image = cairo_image_surface_create_from_png("score.gif");
    cairo_set_source_surface(cairoDrawPlace, image, 10, 10);
    cairo_paint(cairoDrawPlace);
    cairo_surface_destroy(image);*/
    char score[20];
    sprintf(score, "%d", field->score);

    cairo_set_source_rgba(cairoDrawPlace, 1, 1, 1, 1);
    cairo_move_to(cairoDrawPlace, pixelConst * field->sizeX + 5, 0);
    cairo_line_to(cairoDrawPlace, pixelConst * field->sizeX + 5, pixelConst * field->sizeY);
    cairo_translate(cairoDrawPlace, pixelConst * field->sizeX + 10, 5);
    cairo_set_font_size(cairoDrawPlace, 16);
    cairo_move_to(cairoDrawPlace, pixelConst, 16);
    cairo_show_text(cairoDrawPlace, "Score:"); 
    cairo_move_to(cairoDrawPlace, pixelConst, 32);
    cairo_show_text(cairoDrawPlace, score); 
}

void gameoverDraw(cairo_t *cairoDrawPlace, field_t *field)
{
    cairo_set_source_rgba(cairoDrawPlace, 1, 1, 1, 1);
    cairo_set_font_size(cairoDrawPlace, 16);
    cairo_move_to(cairoDrawPlace, ((field->sizeX / 2 - 3)) * pixelConst, (field->sizeY / 2) * pixelConst);
    cairo_show_text(cairoDrawPlace, "GAME OVER");  
}
