#include <gtk/gtk.h>
#include <string.h>
void on_recommend_button_clicked(GtkWidget *widget, gpointer data);
void on_back_button_clicked(GtkWidget *widget, gpointer data);
void show_movie_details(GtkWidget *widget, gpointer data);
GtkWidget *main_window;
GtkWidget *details_window;
GtkWidget *recommendations_label;
typedef struct {
    char title[50];
    int year;
    char genres[100];
    char director[50];
    char studio[50];
} Movie;
Movie movies[] = {
    {"Movie 1", 2020, "Acción, Comedia", "Director 1", "Studio 1"},
    {"Movie 2", 2019, "Drama, Romance", "Director 2", "Studio 2"},
    {"Movie 3", 2018, "Ciencia Ficción, Fantasía", "Director 3", "Studio 3"},
    {"Movie 4", 2021, "Horror, Misterio", "Director 4", "Studio 4"},
    {"Movie 5", 2017, "Acción, Drama", "Director 5", "Studio 5"},
    
};
GtkWidget *genre_checkbuttons[8];
const char *genres[] = {"Acción", "Comedia", "Drama", "Fantasía", "Horror", "Misterio", "Romance", "Ciencia Ficción"};

void on_recommend_button_clicked(GtkWidget *widget, gpointer data) {
    char selected_genres[3][20];
    int selected_count = 0;

    for (int i = 0; i < 8 && selected_count < 3; i++) {
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(genre_checkbuttons[i]))) {
            strcpy(selected_genres[selected_count], genres[i]);
            selected_count++;
        }
    }
 
    char recommendations[500] = "Películas recomendadas:\n";
    int recommendation_count = 0;

    for (int i = 0; i < sizeof(movies)/sizeof(movies[0]) && recommendation_count < 5; i++) {
        for (int j = 0; j < selected_count; j++) {
            if (strstr(movies[i].genres, selected_genres[j]) != NULL) {
                strcat(recommendations, movies[i].title);
                strcat(recommendations, " (");
                strcat(recommendations, movies[i].genres);
                strcat(recommendations, ")\n");
                recommendation_count++;
                break;
            }
        }
    }
    gtk_label_set_text(GTK_LABEL(recommendations_label), recommendations);
    show_movie_details(widget, data);
}

void on_back_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(details_window);
    gtk_widget_show_all(main_window);
}

void show_movie_details(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(main_window);

    if (!details_window) {
        GtkWidget *vbox;
        GtkWidget *label;
        GtkWidget *back_button;

        details_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(details_window), "Detalles de la Película");
        gtk_window_set_default_size(GTK_WINDOW(details_window), 400, 300);
        g_signal_connect(details_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        
        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_container_add(GTK_CONTAINER(details_window), vbox);

        
        recommendations_label = gtk_label_new("Películas recomendadas aparecerán aquí...");
        gtk_box_pack_start(GTK_BOX(vbox), recommendations_label, FALSE, FALSE, 0);

        
        back_button = gtk_button_new_with_label("Volver");
        g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_button_clicked), NULL);
        gtk_box_pack_start(GTK_BOX(vbox), back_button, FALSE, FALSE, 0);
    }

    gtk_widget_show_all(details_window);
}

int main(int argc, char *argv[]) {
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *genre_list;
    GtkWidget *recommend_button;

    gtk_init(&argc, &argv);

    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Sistema de Recomendación de Películas");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 400, 300);
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(main_window), vbox);

    label = gtk_label_new("Seleccione sus géneros favoritos (hasta 3):");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    genre_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    for (int i = 0; i < 8; i++) {
        genre_checkbuttons[i] = gtk_check_button_new_with_label(genres[i]);
        gtk_box_pack_start(GTK_BOX(genre_list), genre_checkbuttons[i], FALSE, FALSE, 0);
    }
    gtk_box_pack_start(GTK_BOX(vbox), genre_list, FALSE, FALSE, 0);

    recommend_button = gtk_button_new_with_label("Recomendar");
    g_signal_connect(recommend_button, "clicked", G_CALLBACK(on_recommend_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), recommend_button, FALSE, FALSE, 0);

    gtk_widget_show_all(main_window);

    gtk_main();

    return 0;
}
