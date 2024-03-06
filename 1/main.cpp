#include <gtk/gtk.h>

// Callback function for when the "New File" button is clicked
void on_new_file_clicked(GtkWidget *widget, gpointer data) {
    g_print("Creating a new file...\n");
}

// Callback function for when the "Open File" button is clicked
void on_open_file_clicked(GtkWidget *widget, gpointer data) {
    g_print("Opening a file...\n");
}

// Callback function for when the "Save File" button is clicked
void on_save_file_clicked(GtkWidget *widget, gpointer data) {
    g_print("Saving a file...\n");
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kilt IDE");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a box layout
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Create buttons
    GtkWidget *button_new = gtk_button_new_with_label("New File");
    GtkWidget *button_open = gtk_button_new_with_label("Open File");
    GtkWidget *button_save = gtk_button_new_with_label("Save File");

    // Connect signals to button clicks
    g_signal_connect(button_new, "clicked", G_CALLBACK(on_new_file_clicked), NULL);
    g_signal_connect(button_open, "clicked", G_CALLBACK(on_open_file_clicked), NULL);
    g_signal_connect(button_save, "clicked", G_CALLBACK(on_save_file_clicked), NULL);

    // Add buttons to the box layout
    gtk_box_pack_start(GTK_BOX(box), button_new, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), button_open, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), button_save, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
