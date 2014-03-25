#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "lib/jsmn.c"
#include "lib/json.c"
#include "lib/buf.c"
#include "lib/log.c"
#include "lib/helpers.c"
#include "openvpn.h"
#include "config.h"

void update_status(char *text)
void update_location(char *text)
void *find_location()
void run_location_finder()
void destroy_window (GtkWidget *widget, gpointer data)
static GtkWidget* create_window (void)
void message_alert(char text[])
void connect_clicked (GtkButton *button, gpointer user_data)
void disconnect_clicked (GtkButton *button, gpointer user_data)
void config_selected (GtkFileChooser *button, gpointer user_data)
