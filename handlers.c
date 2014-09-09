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

    for (i = 0; i < gui_data_get_cards_num(gui_data); i++)
        g_signal_connect (G_OBJECT (gui_data_get_player_button_nth (gui_data, i)), "toggled", G_CALLBACK (on_buttonuser_toggled), (gpointer) game_data);

    for (i = 0; i < gui_data_get_field_num(gui_data); i++){
        for (j = 0; j < gui_data_get_field_num(gui_data); j++){
            g_signal_connect (G_OBJECT (gui_data_get_field_button_nth (gui_data, i, j)), "toggled", G_CALLBACK (on_buttonfield_toggled), (gpointer) game_data);

        }
    }

    return ;
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

    return ;
}

void
on_buttonfield_toggled (GtkToggleButton* button, gpointer user_data)
{
    GameData* game_data = (GameData*) user_data;
    CardsHand* player_hand = (CardsHand*) game_data->player_hand;
    GameField* game_field = (GameField*) game_data->game_field;
    CardsHand* cpu_hand = (CardsHand*) game_data->cpu_hand;
    gboolean clicked_state;

    clicked_state = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button));

    if (clicked_state == FALSE){ // this operates when you click on an empty place in the game field

        if (game_play_player_card_selected (game_field, player_hand) == TRUE)           
            game_play_cpu_card_random (game_field, cpu_hand);
        else
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
    }

    return ;
}