#ifndef GUI_H
#define GUI_H

#include "cardshand.h"
#include "gamefield.h"

typedef struct guielems {

	GtkWidget* window;
	guint cards_num;
	guint field_num;
	GtkWidget** player_buttons;
    GtkWidget*** field_buttons;
    GtkWidget** cpu_buttons; 
    GtkWidget* player_score_label;
    GtkWidget* cpu_score_label;

    // Menu elements
    GtkWidget* new_game_menu_item;
    GtkWidget* exit_menu_item;
    GtkWidget* about_menu_item; 

} GuiData;

GuiData* gui_create (guint cards_num, guint field_num);
GtkWidget* gui_data_get_main_window (GuiData* gui_data);
GtkWidget** gui_data_get_player_buttons (GuiData* gui_data);
GtkWidget** gui_data_get_cpu_buttons (GuiData* gui_data);
GtkWidget*** gui_data_get_field_buttons (GuiData* gui_data);
GtkWidget* gui_data_get_player_button_nth (GuiData* gui_data, guint n);
GtkWidget* gui_data_get_cpu_button_nth (GuiData* gui_data, guint n);
GtkWidget* gui_data_get_field_button_nth (GuiData* gui_data, guint row, guint col);
GtkWidget* gui_data_get_player_score_label (GuiData* gui_data);
GtkWidget* gui_data_get_cpu_score_label (GuiData* gui_data);
GtkWidget* gui_data_get_new_game_menu_item (GuiData* gui_data);
GtkWidget* gui_data_get_exit_menu_item (GuiData* gui_data);
GtkWidget* gui_data_get_about_menu_item (GuiData* gui_data);
gint gui_data_get_cards_num (GuiData* gui_data);
gint gui_data_get_field_num (GuiData* gui_data);
void gui_data_free (GuiData* gui_data);

#endif /* GUI_H */

