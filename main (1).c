#include <gtk/gtk.h>

#define MAX_GENRES 3

// Estructura para mantener el estado de la aplicación
typedef struct {
    GList *checkboxes;
    int selected_count;
} AppState;

// Prototipo de la función de recomendación
void recommend_movies(const char *selected_genres[], int num_genres);

// Callback para manejar la selección de géneros
void on_checkbox_toggled(GtkToggleButton *toggle_button, gpointer data) {
    AppState *app_state = (AppState *)data;
    
    if (gtk_toggle_button_get_active(toggle_button)) {
        app_state->selected_count++;
    } else {
        app_state->selected_count--;
    }

    if (app_state->selected_count > MAX_GENRES) {
        gtk_toggle_button_set_active(toggle_button, FALSE);
        app_state->selected_count--;
        g_print("You can select a maximum of %d genres.\n", MAX_GENRES);
    }
}

// Callback para manejar el envío de la selección de géneros al módulo de recomendación
void on_button_clicked(GtkWidget *widget, gpointer data) {
    AppState *app_state = (AppState *)data;
    GList *iterator = NULL;
    const char *selected_genres[MAX_GENRES];
    int genre_count = 0;

    for (iterator = app_state->checkboxes; iterator; iterator = iterator->next) {
        GtkToggleButton *checkbox = GTK_TOGGLE_BUTTON(iterator->data);
        if (gtk_toggle_button_get_active(checkbox)) {
            selected_genres[genre_count++] = gtk_button_get_label(GTK_BUTTON(checkbox));
        }
    }

    // Llamar al módulo de recomendación con la lista de géneros seleccionados
    recommend_movies(selected_genres, genre_count);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Movie Recommendation System");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Lista de géneros
    const char *genres[] = {"Action", "Comedy", "Drama", "Horror", "Romance"};
    GList *checkboxes = NULL;
    AppState app_state = {NULL, 0};

    // Crear checkboxes para cada género
    for (int i = 0; i < 5; i++) {
        GtkWidget *checkbox = gtk_check_button_new_with_label(genres[i]);
        g_signal_connect(checkbox, "toggled", G_CALLBACK(on_checkbox_toggled), &app_state);
        gtk_box_pack_start(GTK_BOX(vbox), checkbox, FALSE, FALSE, 0);
        checkboxes = g_list_append(checkboxes, checkbox);
    }

    app_state.checkboxes = checkboxes;

    GtkWidget *button = gtk_button_new_with_label("Recommend Movies");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), &app_state);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
