#include <gtk/gtk.h>
#include <iostream>
#include <dirent.h>
#include <vector>

// Function to list files in a directory
std::vector<std::string> listFilesInDirectory(const std::string &directory) {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                files.push_back(std::string(ent->d_name));
            }
        }
        closedir(dir);
    } else {
        perror("Failed to open directory");
    }
    return files;
}

// Callback function for when the "Open Folder" button is clicked
void on_open_folder_clicked(GtkWidget *widget, gpointer data) {
    g_print("Opening folder...\n");
    // Code to open a folder and populate the sidebar with files
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open Folder",
                                          NULL,
                                          action,
                                          "_Cancel",
                                          GTK_RESPONSE_CANCEL,
                                          "_Open",
                                          GTK_RESPONSE_ACCEPT,
                                          NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *folder_path;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        folder_path = gtk_file_chooser_get_filename (chooser);
        g_print ("Folder selected: %s\n", folder_path);

        // List files in the selected folder
        std::vector<std::string> files = listFilesInDirectory(folder_path);

        // Add files to the sidebar
        GtkTreeIter iter;
        GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(data));
        gtk_tree_store_clear(GTK_TREE_STORE(model));
        for (const auto &file : files) {
            gtk_tree_store_append(GTK_TREE_STORE(model), &iter, NULL);
            gtk_tree_store_set(GTK_TREE_STORE(model), &iter, 0, file.c_str(), -1);
        }

        g_free (folder_path);
    }

    gtk_widget_destroy (dialog);
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kilt IDE (VSC Style)");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a box layout
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Create a vertical box layout for the sidebar
    GtkWidget *sidebar_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(box), sidebar_box, FALSE, TRUE, 0);

    // Create buttons
    GtkWidget *button_open_folder = gtk_button_new_with_label("Open Folder");

    // Connect signals to button clicks
    g_signal_connect(button_open_folder, "clicked", G_CALLBACK(on_open_folder_clicked), NULL);

    // Add buttons to the sidebar
    gtk_box_pack_start(GTK_BOX(sidebar_box), button_open_folder, FALSE, FALSE, 0);

    // Create a scrolled window for the file tree view
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);

    // Create the tree view
    GtkTreeStore *tree_store = gtk_tree_store_new(1, G_TYPE_STRING);
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(tree_store));
    g_object_unref(tree_store); // Free tree store when the view is destroyed

    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Files", gtk_cell_renderer_text_new(), "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
