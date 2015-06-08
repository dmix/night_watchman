#include "window.c"

int main (int argc, char *argv[])
{
    printf("-------- Night Watchman ----------\n");

    // Parse settings config
    read_config_file();

    // Create GTK Window
    GtkWidget *window;
    gtk_init (&argc, &argv);
    window = create_window ();
    gtk_widget_show (window);
    gtk_main ();

    return 0;
}
