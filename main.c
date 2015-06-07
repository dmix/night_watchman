#include "window.c"

int main (int argc, char *argv[])
{
  printf("--------Night Watchman----------\n");
  read_config_file();
  GtkWidget *window;
  gtk_init (&argc, &argv);
  window = create_window ();
  gtk_widget_show (window);
  gtk_main ();
  return 0;
}
