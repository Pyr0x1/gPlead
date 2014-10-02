#ifndef HANDLERS_H
#define HANDLERS_H

#include "gui.h"
#include "game.h"

void handlers_connect_all (GuiData* gui_data, GameData* game_data);
void on_buttonuser_toggled (GtkToggleButton* button, gpointer user_data);
void on_buttonfield_toggled (GtkToggleButton* button, gpointer user_data);
gint on_timeout_cpu_moves( gpointer user_data );

#endif /* HANDLERS_H */

