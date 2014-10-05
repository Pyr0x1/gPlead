#ifndef HANDLERS_H
#define HANDLERS_H

#include "gui.h"
#include "game.h"
#include "general.h"

void handlers_connect_all (GeneralData* general_data);
void handlers_new_game (GtkMenuItem* new_game_menu_item, gpointer user_data);
void show_about_popup (GtkMenuItem* about_menu_item, gpointer user_data);
void on_buttonuser_toggled (GtkToggleButton* button, gpointer user_data);
void on_buttonfield_toggled (GtkToggleButton* button, gpointer user_data);
gint on_timeout_cpu_moves( gpointer user_data );

#endif /* HANDLERS_H */

