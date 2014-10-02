#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include "handlers.h"
#include "gui.h"
#include "cardshand.h"
#include "gamefield.h"
#include "game.h"


void
handlers_connect_all (GuiData* gui_data, GameData* game_data)
{
    guint i, j;

	if (!gui_data || !game_data)
		return;
	
    for (i = 0; i < gui_data_get_cards_num(gui_data); i++)
        g_signal_connect (G_OBJECT (gui_data_get_player_button_nth (gui_data, i)), "toggled", G_CALLBACK (on_buttonuser_toggled), (gpointer) game_data);

    for (i = 0; i < gui_data_get_field_num(gui_data); i++){
        for (j = 0; j < gui_data_get_field_num(gui_data); j++){
            g_signal_connect (G_OBJECT (gui_data_get_field_button_nth (gui_data, i, j)), "toggled", G_CALLBACK (on_buttonfield_toggled), (gpointer) game_data);

        }
    }

    return;
}

void
on_buttonuser_toggled (GtkToggleButton* button, gpointer user_data)
{
    GameData* game_data = (GameData*) user_data;
    CardsHand* hand = (CardsHand*) game_data->player_hand;
    GtkCard* tmp_card;
    gboolean clicked_state;
    guint i;

    clicked_state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));

    if(clicked_state == TRUE){
        for (i = 0; i < cards_hand_get_cards_num (hand); i++){

            tmp_card = cards_hand_get_nth (hand, i);

            if (gtk_card_get_button (tmp_card) != button)
                gtk_toggle_button_set_active (gtk_card_get_button (tmp_card), FALSE);
        }
    }

    return;
}

void
on_buttonfield_toggled (GtkToggleButton* button, gpointer user_data)
{
    GameData* game_data = (GameData*) user_data;
    CardsHand* player_hand = (CardsHand*) game_data->player_hand;
    GameField* game_field = (GameField*) game_data->game_field;
    GtkScore* player_score = (GtkScore*) game_data->player_score;
    GtkScore* cpu_score = (GtkScore*) game_data->cpu_score;

    gboolean clicked_state;
    guint i;

    clicked_state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));

    if (clicked_state == FALSE){ // this operates when you click on an empty place in the game field

        if (game_play_player_card_selected (game_field, player_hand, player_score, cpu_score) == TRUE) {
        	/*
            game_field_force_redraw (game_field); // sets field widgets in "redraw" state
            while (gtk_events_pending ()) // used to redraw widgets
                gtk_main_iteration ();
            Sleep (1000);
            */
            
            // set insensitive to prevent player from move twice
            for (i = 0; i < cards_hand_get_cards_num (player_hand); i++)
	    		gtk_widget_set_sensitive (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth (player_hand, i))), FALSE);
            
            g_timeout_add (1000,	// 1 second
                           on_timeout_cpu_moves,
                           (gpointer) user_data);
            
            //game_play_cpu_card_greedy (game_field, cpu_hand, player_score, cpu_score);
        }
        else
        	if (strcmp (gtk_widget_get_name (GTK_WIDGET (button)), "togglebuttoncpuplayed") !=0 && strcmp (gtk_widget_get_name (GTK_WIDGET (button)), "togglebuttonuser") !=0)
            	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
        
    }

    return ;
}

// this function will be called at end of the timeout, so to leave some time between player move and cpu move
gint
on_timeout_cpu_moves (gpointer user_data)
{

    GameData* game_data = (GameData*) user_data;
    CardsHand* player_hand = (CardsHand*) game_data->player_hand;
    GameField* game_field = (GameField*) game_data->game_field;
    CardsHand* cpu_hand = (CardsHand*) game_data->cpu_hand;
    GtkScore* player_score = (GtkScore*) game_data->player_score;
    GtkScore* cpu_score = (GtkScore*) game_data->cpu_score;
	
    guint i;

	game_play_cpu_card_greedy (game_field, cpu_hand, player_score, cpu_score);
    
    // after the cpu moves, the player can newly select cards (only not void cards)
    for (i = 0; i < cards_hand_get_cards_num (player_hand); i++)
    	if (strcmp (gtk_widget_get_name (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth ( player_hand, i)))), "togglebuttonuser") == 0)
			gtk_widget_set_sensitive (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth (player_hand, i))), TRUE);
    
	return FALSE;	// if true this function would be called at regular timing, with false it will execute only once
}

