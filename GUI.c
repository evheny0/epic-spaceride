#include "GUI.h"

void GUIInit(field_t *field) 
{
    GtkWidget *window;
    GtkWidget *frame;

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
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
}

gboolean keyPress(GtkWidget *window, GdkEventKey *event, field_t *field)
{
    gameKeys(event->keyval, field);
    return TRUE;
}

void gameKeys(int keyval, field_t *field)
{
    pthread_t bulletThread;
    switch (keyval) {
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
        break;
    }
}

void *bulletStart(void *vptr_args)
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
