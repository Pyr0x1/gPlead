#include <stdio.h>
#include <stdlib.h>
#include "game.h"

GameData* 
game_data_new (guint cards_num, guint field_num, GtkWidget** player_buttons, GtkWidget*** field_buttons, GtkWidget** cpu_buttons)
{
	GameData* game_data = (GameData *) calloc (1, sizeof (GameData));
	guint i, j;

	// Creates player hand and cpu hand
    game_data->player_hand = cards_hand_new (cards_num);
    game_data->cpu_hand = cards_hand_new (cards_num);

    for (i = 0; i < cards_num; i++){
    	cards_hand_add_random (game_data->player_hand, GTK_TOGGLE_BUTTON (player_buttons[i]), 9, TRUE);
    	cards_hand_add_random (game_data->cpu_hand, GTK_TOGGLE_BUTTON (cpu_buttons[i]), 9, FALSE);
    }

    // Creates game field
    game_data->game_field = game_field_new (field_num);

    for (i = 0; i < field_num; i++){
    	for (j = 0; j < field_num; j++){
    		game_field_add (game_data->game_field, GTK_TOGGLE_BUTTON (field_buttons[i][j]));
    	}
    }

	return game_data;
}

gboolean
game_play_player_card_selected (GameField* game_field, CardsHand* player_hand)
{
    GtkCard* player_card = cards_hand_get_selected (player_hand);
	GtkFieldCard* field_card = game_field_get_selected (game_field);

	if (player_card != NULL && field_card != NULL){
		gtk_card_unselect (player_card);
	    gtk_card_switch_content (player_card, gtk_field_card_get_gtk_card (field_card));
	    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (player_card)), FALSE);
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (player_card)), "");
	    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), FALSE);
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), "togglebuttonuser");

	    return TRUE;
	}

	return FALSE;
}

gboolean 
game_play_cpu_card_random (GameField* game_field, CardsHand* cpu_hand)
{
	GtkCard* cpu_card = cards_hand_get_random (cpu_hand);
	GtkFieldCard* field_card = game_field_get_random (game_field);

	if (cpu_card != NULL && field_card != NULL){
		gtk_card_write_label (cpu_card);
		gtk_card_switch_content (cpu_card, gtk_field_card_get_gtk_card (field_card));
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (cpu_card)), "");
	    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), FALSE);
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), "togglebuttoncpuplayed");

	    return TRUE;
	}

	return FALSE;
}

void 
game_data_free (GameData* game_data)
{
	game_field_free (game_data->game_field);
    cards_hand_free (game_data->player_hand);
    cards_hand_free (game_data->cpu_hand);
    free (game_data);

	return ;
}