#include <gtk/gtk.h>

void destroy (GtkWidget *widget, gpointer data)
void update_status(char *text)
void update_location(char *text)
static GtkWidget* create_window (void)
void connect_clicked (GtkButton *button, gpointer user_data)
void disconnect_clicked (GtkButton *button, gpointer user_data)
void config_selected (GtkFileChooser *button, gpointer user_data)
