#include <gtk/gtk.h>
#include "funciones_ig.h"

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *menu_box;
    GtkWidget *generos_button, *usuario_button, *cerrar_sesion_button;
    GtkWidget *content_box, *header_box, *label;
    GtkWidget *recomendaciones_box;  // Nueva caja para las recomendaciones

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

    // Se crea el botón "Usuario"
    usuario_button = gtk_button_new_with_label("Usuario");
    gtk_box_pack_start(GTK_BOX(menu_box), usuario_button, FALSE, FALSE, 10);

    // Se crea el botón "Géneros"
    generos_button = gtk_button_new_with_label("Géneros");
    gtk_widget_set_size_request(generos_button, 200, -1); 
    gtk_box_pack_start(GTK_BOX(menu_box), generos_button, FALSE, FALSE, 0);

    // Se crea el botón "Cerrar sesión"
    cerrar_sesion_button = gtk_button_new_with_label("Cerrar Sesión");
    gtk_box_pack_start(GTK_BOX(menu_box), cerrar_sesion_button, FALSE, FALSE, 200);

    // Contenedor vertical para el contenido a la derecha
    content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(main_box), content_box, TRUE, TRUE, 10);

    // Contenedor horizontal para el encabezado
    header_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(content_box), header_box, FALSE, FALSE, 10);

    // Texto "Mis Películas" en el encabezado
    label = gtk_label_new("Mis Películas");
    gtk_box_pack_start(GTK_BOX(header_box), label, FALSE, FALSE, 10);
    gtk_widget_set_margin_start(label, 20);

    // Caja para las recomendaciones
    recomendaciones_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(content_box), recomendaciones_box, TRUE, TRUE, 10);

    // Conectar la señal del botón para abrir el diálogo
    g_signal_connect(generos_button, "clicked", G_CALLBACK(al_hacer_clic_en_boton_genero), recomendaciones_box);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
