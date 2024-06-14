#ifndef FUNCIONES_IG_H
#define FUNCIONES_IG_H

#include <gtk/gtk.h>

// Declaración de la funciones
void al_responder_dialogo(GtkDialog *dialog, gint response_id, gpointer user_data);
void al_cambiar_estado_check_button(GtkToggleButton *toggle_button, gpointer user_data);
void al_hacer_clic_en_boton_genero(GtkButton *button, gpointer user_data);
#endif
