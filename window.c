#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "lib/jsmn.c"
#include "lib/json.c"
#include "lib/buf.c"
#include "lib/log.c"
#include "lib/helpers.c"
#include "openvpn.c"
#include "config.c"

#define IPINFO_URL "http://ipinfo.io/json"
#define UI_FILE "gui/night_watchman.ui"
#define TOP_WINDOW "connect_window"
#define CURRENT_DIR "/home/dmix/vpn/"

GtkWidget *window;
GtkBuilder *builder;
GtkWidget *connect_button;
GtkWidget *disconnect_button;
GtkWidget *file_chooser_widget;
GtkFileChooser *file_chooser;
GtkStatusbar *status;
GtkStatusbar *location;
char *config_path;

void update_status(char *text)
{
  gtk_statusbar_push (status,
                      0,
                      text);
}

void update_location(char *text)
{
  gtk_statusbar_push (location,
                      0,
                      text);
}

/**
 * Fetch ip/location info from ipinfo.org
 */
void *find_location()
{
  printf ("Fetching location\n");

  jsmntok_t *t;
  char *js;
  char *ip = "n/a";
  char *city = "n/a";
  char *state = "n/a";
  char *country = "n/a";
  char *org = "n/a";
  char *str_to_ret;

  js = json_fetch(IPINFO_URL);

  jsmntok_t *tokens = json_tokenise(js);
  t = &tokens[2];
  ip= json_token_tostr(js, t);
  t = &tokens[6];
  city = json_token_tostr(js, t);
  t = &tokens[8];
  state = json_token_tostr(js, t);
  t = &tokens[10];
  country = json_token_tostr(js, t);
  t = &tokens[14];
  org = json_token_tostr(js, t);

  char status_text[200];
  sprintf(status_text, "Location: %s, %s %s => %s", city, state, country, org);
  update_location(status_text);

  pthread_exit(NULL);
}

void run_location_finder()
{
  pthread_t thread[1];
  memset(thread, 0, sizeof(thread));
  pthread_create(&thread[0], NULL, find_location, NULL);
}

void destroy_window (GtkWidget *widget, gpointer data)
{
  printf("Exiting");
  gtk_main_quit ();
}

/**
 * Create GTK window
 */
static GtkWidget* create_window (void)
{
  GError* error = NULL;

  /* Load UI from file */
  builder = gtk_builder_new ();
  if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
  {
	  g_critical ("Couldn't load builder file: %s", error->message);
	  g_error_free (error);
  }

  /* Auto-connect signal handlers */
  gtk_builder_connect_signals (builder, NULL);

  /* Get the window object from the ui file */
  window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
  gtk_window_set_title (GTK_WINDOW (window), "Night Watchman VPN");

  /* Exit when the window is closed */
  g_signal_connect (window, "destroy", G_CALLBACK(destroy_window), NULL);

  /* Assign button signals */
  connect_button = (GtkWidget*)gtk_builder_get_object (builder, "connect");
  disconnect_button = (GtkWidget*)gtk_builder_get_object (builder, "disconnect");
  file_chooser_widget = (GtkWidget*)gtk_builder_get_object (builder, "config");
  file_chooser = (GtkFileChooser*)gtk_builder_get_object (builder, "config");
  gtk_file_chooser_set_filename(file_chooser,
				config_path);

  status = (GtkStatusbar*)gtk_builder_get_object (builder, "status");
  update_status ("Status: Disconnected");
  location = (GtkStatusbar*)gtk_builder_get_object (builder, "location");
  update_location("Location: Checking...");

  /* fetch initial location */
  run_location_finder();

  g_object_unref (builder);

  return window;
}

void message_alert(char text[])
{
  GtkWidget *dialog;
  GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
  dialog = gtk_message_dialog_new (NULL,
                                   flags,
                                   GTK_MESSAGE_ERROR,
                                   GTK_BUTTONS_OK,
                                   NULL);
  gtk_message_dialog_set_markup (GTK_MESSAGE_DIALOG (dialog),
                                 text);

  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

void connect_clicked (GtkButton *button, gpointer user_data)
{
  bool is_connected;
  printf("connected clicked\n");
  update_status ("Status: Connecting...");
  is_connected = spawn_openvpn(config_path);
  if (is_connected) {
    gtk_widget_set_sensitive(file_chooser_widget, false);
    gtk_widget_set_sensitive(connect_button, false);
    gtk_widget_set_sensitive(disconnect_button, true);
  }
  else {
    message_alert("Please select an OpenVPN config path");
  }
}

void disconnect_clicked (GtkButton *button, gpointer user_data)
{
  update_status ("Status: Disconnected");
  gtk_widget_set_sensitive(file_chooser_widget, true);
  gtk_widget_set_sensitive(connect_button, true);
  gtk_widget_set_sensitive(disconnect_button, false);
  run_location_finder();
}

void config_selected (GtkFileChooser *button, gpointer user_data)
{
  config_path = gtk_file_chooser_get_filename (file_chooser);
  write_config_file(config_path);
  printf("config selected: %s\n", config_path);
}

