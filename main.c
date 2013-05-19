#include <stdlib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <math.h>
//#include "ship.h"
#include "graphics.h"

/*
const int sizeX = 8;
const int sizeY = 20;*/
char windowTitle[20];

static gboolean fieldClick(GtkWidget *window, GdkEventButton *event, field_t *field);
static gboolean keyPress(GtkWidget *window, GdkEventKey *event, field_t *field);
static gboolean generateEnemies(field_t *field);
static void *bulletStart(void *vptr_args);
void closeButton(GtkWidget *window, field_t *field);

static void *outputProcessOfSolving(void *vptr_args);

int main(int argc, char **argv)
{
    GtkWidget *window;
    GtkWidget *frame;

    field_t *field;

    field = fieldInit();
    gtk_init(&argc, &argv);

    /* need to rewrite using threads */
    //g_timeout_add(2000, (GSourceFunc) generateEnemies, field);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //gtk_window_resize(GTK_WINDOW(window), 485, 510);  /*need to fix*/
    gtk_window_set_title(GTK_WINDOW(window), "Epic Spaceride");

    frame = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), frame);
    gtk_container_set_border_width(GTK_CONTAINER(frame), 10);

    graphicsInit(frame, field);

    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    g_signal_connect (window, "key-press-event", G_CALLBACK (keyPress), field);
    g_signal_connect(window, "destroy", G_CALLBACK(closeButton), field);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

static gboolean keyPress(GtkWidget *window, GdkEventKey *event, field_t *field)
{
    pthread_t bulletThread;
    switch (event->keyval) {
    case GDK_KEY_Up:
        shipMove(field, -1, 0);
        break;
    case GDK_KEY_Down:
        shipMove(field, 1, 0);
        break;
    case GDK_KEY_Left:
        shipMove(field, 0, -1);
        break;
    case GDK_KEY_Right:
        shipMove(field, 0, 1);
        break;
    case GDK_KEY_z:
        if (!field->isGameover) {
            pthread_create(&bulletThread, NULL, bulletStart, (void *) field);
        }
        //pthread_cancel(outputThread);
        //g_timeout_add(100, (GSourceFunc) bulletStart, field);
        break;
    }
    //gtk_widget_queue_draw(window);
    return TRUE;
}

static void *bulletStart(void *vptr_args)
{
    field_t *field;
    field = vptr_args;

    int i = field->shipLocation.y - 4, j = field->shipLocation.x;
    field->values[i][j] = BULLET;
    for (i--; ; i--) {
        usleep(40000);
        if (bulletMove(field, i, j)) {
            break;
        }
    }
    return NULL;
}

void closeButton(GtkWidget *window, field_t *field)
{
    gtk_main_quit();
}
