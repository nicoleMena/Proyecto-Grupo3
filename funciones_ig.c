#include "funciones_ig.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int contar_botones_seleccionados_en_list_box(GtkWidget *list_box);
void mostrar_recomendaciones(GtkWidget *widget, const char *genres); // Declaración de la función

/*
 * Esta función cuenta cuántos botones están seleccionados en un ListBox.
 * @param list_box El widget ListBox del cual se cuentan los botones.
 * @return El número de botones seleccionados.
 */
static int contar_botones_seleccionados_en_list_box(GtkWidget *list_box) {
    int count = 0;
    GList *children = gtk_container_get_children(GTK_CONTAINER(list_box));
    for (GList *iter = children; iter != NULL; iter = iter->next) {
        GtkWidget *row = GTK_WIDGET(iter->data);
        GtkWidget *check_button = gtk_bin_get_child(GTK_BIN(row));
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button))) {
            count++;
        }
    }
    g_list_free(children);
    return count;
}

/*
 * Esta función es un callback que se llama cuando se responde a un diálogo GTK.
 * @param dialog El diálogo al cual se está respondiendo.
 * @param response_id El ID de la respuesta recibida.
 * @param user_data Datos adicionales pasados desde la señal.
 */
void al_responder_dialogo(GtkDialog *dialog, gint response_id, gpointer user_data) {
    if (response_id == GTK_RESPONSE_OK) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(user_data));
        GString *genres = g_string_new(NULL);

        for (GList *iter = children; iter != NULL; iter = iter->next) {
            GtkWidget *row = GTK_WIDGET(iter->data);
            GtkWidget *check_button = gtk_bin_get_child(GTK_BIN(row));
            if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button))) {
                const gchar *genre = gtk_button_get_label(GTK_BUTTON(check_button));
                if (genres->len > 0)
                    g_string_append(genres, " ");
                g_string_append(genres, genre);
            }
        }
        g_list_free(children);

        GtkWidget *recomendaciones_box = GTK_WIDGET(g_object_get_data(G_OBJECT(dialog), "recomendaciones_box"));
        mostrar_recomendaciones(recomendaciones_box, genres->str); // Cambio aquí

        g_string_free(genres, TRUE);
    }
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

/*
 * Esta función es un callback llamada cuando se cambia el estado del botón.
 * @param toggle_button El CheckButton que ha cambiado de estado.
 * @param user_data Datos adicionales pasados desde la señal.
 */
void al_cambiar_estado_check_button(GtkToggleButton *toggle_button, gpointer user_data) {
    GtkWidget *list_box = GTK_WIDGET(user_data);
    int selected_count = contar_botones_seleccionados_en_list_box(list_box);

    GList *children = gtk_container_get_children(GTK_CONTAINER(list_box));
    for (GList *iter = children; iter != NULL; iter = iter->next) {
        GtkWidget *row = GTK_WIDGET(iter->data);
        GtkWidget *check_button = gtk_bin_get_child(GTK_BIN(row));
        if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button))) {
            gtk_widget_set_sensitive(check_button, selected_count < 3);
        }
    }
    g_list_free(children);
}

/*
 * Esta función es para manejar el clic en el botón Género.
 * @param button El botón en el cual se ha hecho clic.
 * @param user_data Datos adicionales pasados desde la señal.
 */
void al_hacer_clic_en_boton_genero(GtkButton *button, gpointer user_data) {
    // Crear el diálogo
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Seleccionar Género", 
                                                    GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                    GTK_DIALOG_MODAL,
                                                    "Cancelar", GTK_RESPONSE_CANCEL,
                                                    "Seleccionar", GTK_RESPONSE_OK,
                                                    NULL);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *list_box = gtk_list_box_new();

    // Crear y añadir los géneros con check buttons al list box
    const gchar *generos[] = {"Animada", "Comedia", "Drama", "Accion", "Ficcion", "Thriller", "Terror"};
    for (int i = 0; i < G_N_ELEMENTS(generos); i++) {
        GtkWidget *row = gtk_list_box_row_new();
        GtkWidget *check_button = gtk_check_button_new_with_label(generos[i]);
        gtk_container_add(GTK_CONTAINER(row), check_button);
        gtk_container_add(GTK_CONTAINER(list_box), row);

        // Conectar la señal de toggle del check button
        g_signal_connect(check_button, "toggled", G_CALLBACK(al_cambiar_estado_check_button), list_box);
    }

    gtk_container_add(GTK_CONTAINER(content_area), list_box);
    gtk_widget_show_all(dialog);

    // Conectar la señal de respuesta del diálogo
    g_signal_connect(dialog, "response", G_CALLBACK(al_responder_dialogo), list_box);

    // Guardar la caja de recomendaciones en los datos del diálogo
    g_object_set_data(G_OBJECT(dialog), "recomendaciones_box", user_data);
}

/*
 * Muestra recomendaciones de películas en la interfaz grafica.
 * Esta funcion toma un widget y una cadena de generos seleccionados,
 * ejecuta un comando externo para obtener recomendaciones basadas en los generos,
 * y actualiza la interfaz grafica con los resultados obtenidos.
 * @param widget El widget de GTK donde se mostraran las recomendaciones.
 * @param genres Cadena que contiene los géneros seleccionados por el usuario.
 */
void mostrar_recomendaciones(GtkWidget *widget, const char *genres) {
    GtkWidget *recomendaciones_box = GTK_WIDGET(widget);
    GList *children = gtk_container_get_children(GTK_CONTAINER(recomendaciones_box));
    for (GList *iter = children; iter != NULL; iter = iter->next) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    char command[1024];
    sprintf(command, "./algoritmo_recomendacion %s", genres);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        g_print("Failed to run command\n");
        return;
    }

    char path[1035];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        GtkWidget *label = gtk_label_new(path);
        gtk_box_pack_start(GTK_BOX(recomendaciones_box), label, FALSE, FALSE, 0);
    }
    pclose(fp);
    gtk_widget_show_all(recomendaciones_box);
}
