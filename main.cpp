#include <gtk/gtk.h>
#include <iostream>
#include <dirent.h>
#include <vector>

// Struct to hold file information
struct FileData {
    std::string name;
    std::string path;
};

// Function to list files in a directory
std::vector<FileData> listFilesInDirectory(const std::string &directory) {
    std::vector<FileData> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                FileData file;
                file.name = std::string(ent->d_name);
                file.path = directory + "/" + file.name;
                files.push_back(file);
            }
        }
        closedir(dir);
    } else {
        perror("Failed to open directory");
    }
    return files;
}

// Callback function for when a file is selected
void on_file_selected(GtkWidget *widget, gpointer data) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
    GtkTreeIter iter;
    if (gtk_tree_selection_get_selected(selection, NULL, &iter)) {
        GtkTreeModel *model;
        gchar *file_path;
        model = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));
        gtk_tree_model_get(model, &iter, 1, &file_path, -1);
        std::cout << "Opening file: " << file_path << std::endl;

        // Read the file content and display in text view
        void on_open_folder_clicked(GtkWidget *widget, gpointer data);
        if (file_stream) {
            std::string content((std::istreambuf_iterator<char>(file_stream)), (std::istreambuf_iterator<char>()));
            GtkWidget *text_view = GTK_WIDGET(data);
            GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            gtk_text_buffer_set_text(buffer, content.c_str(), -1);
        }
    }
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

    // Create the tree view
    GtkTreeStore *tree_store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(tree_store));
    g_object_unref(tree_store); // Free tree store when the view is destroyed

    // Connect signals to button clicks
    g_signal_connect(button_open_folder, "clicked", G_CALLBACK(on_open_folder_clicked), tree_store);

    // Add buttons to the sidebar
    gtk_box_pack_start(GTK_BOX(sidebar_box), button_open_folder, FALSE, FALSE, 0);

    // Create a scrolled window for the file tree view
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);

    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Files", gtk_cell_renderer_text_new(), "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);

    // Create a text view for editing files
    GtkWidget *text_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(box), text_view, TRUE, TRUE, 0);

    // Connect signal for file selection
    g_signal_connect(tree_view, "cursor-changed", G_CALLBACK(on_file_selected), text_view);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
