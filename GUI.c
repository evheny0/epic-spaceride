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
    freeField(field);
}

gboolean keyPress(GtkWidget *window, GdkEventKey *event, field_t *field)
{
    switch (field->gameStatus) {
    case START_MENU:
        startMenuKeys(event->keyval, field);
        break;
    case GAME_IN_PROCESS:
        gameKeys(event->keyval, field);
        break;
    case GAMEOVER:
        gameoverKeys(event->keyval, field);
        break;
    }
    return TRUE;
}

void startMenuKeys(int keyval, field_t *field)
{
    switch (keyval) {
    case GDK_KEY_Up:
        if (field->shipType - 1 < ARCANE) {
            field->shipType = SKULL;
        } else {
            (field->shipType)--;
        }
        break;
    case GDK_KEY_Down:
        if (field->shipType + 1 > SKULL) {
            field->shipType = ARCANE;
        } else {
            (field->shipType)++;
        }
        break;
    case GDK_KEY_z:
        field->gameStatus = GAME_IN_PROCESS;
        break;
    }
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
        if (field->gameStatus == GAME_IN_PROCESS) {
            pthread_create(&bulletThread, NULL, bulletStart, (void *) field);
        }
        break;
    }
}

void gameoverKeys(int keyval, field_t *field)
{
    if (keyval == GDK_KEY_z) {
        field->gameStatus = START_MENU;
    }
}

void *bulletStart(void *vptr_args)
{
    field_t *field;
    field = vptr_args;

    int i = field->shipLocation.y - 5, j = field->shipLocation.x;
    if (i < 0) {
        return NULL;
    }
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
    field->gameStatus = EXIT;
    graphicsDestroy();
    gtk_main_quit();
}
