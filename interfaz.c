#include <gtk/gtk.h>
#include "funciones_ig.h"

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *menu_box;
    GtkWidget *generos_button;

    gtk_init(&argc, &argv);

    // Crear la ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Movie Mentor");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Contenedor principal horizontal para alinear elementos a la izquierda
    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Contenedor vertical para el menú a la izquierda
    menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(main_box), menu_box, FALSE, FALSE, 10);

    // Se crea el botón "Géneros"
    generos_button = gtk_button_new_with_label("Géneros");
    gtk_widget_set_size_request(generos_button, 200, -1); 
    gtk_box_pack_start(GTK_BOX(menu_box), generos_button, FALSE, FALSE, 0);

    // Conectar la señal del botón para abrir el diálogo
    g_signal_connect(generos_button, "clicked", G_CALLBACK(al_hacer_clic_en_boton_genero), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
