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
handlers_connect_all (GeneralData* general_data)
{
    guint i, j;
    GuiData* gui_data = NULL;
    GameData* game_data = NULL;

	if (!general_data)
		return;

    gui_data = general_data_get_gui_data (general_data);
    game_data = general_data_get_game_data (general_data);
	
    // handlers for player buttons
    for (i = 0; i < gui_data_get_cards_num (gui_data); i++)
        g_signal_connect (G_OBJECT (gui_data_get_player_button_nth (gui_data, i)), "toggled", G_CALLBACK (on_buttonuser_toggled), (gpointer) game_data);

    // handlers for field buttons
    for (i = 0; i < gui_data_get_field_num (gui_data); i++){
        for (j = 0; j < gui_data_get_field_num (gui_data); j++){
            g_signal_connect (G_OBJECT (gui_data_get_field_button_nth (gui_data, i, j)), "toggled", G_CALLBACK (on_buttonfield_toggled), (gpointer) general_data);

        }
    }

    // handlers for menu entries
    g_signal_connect (G_OBJECT (gui_data_get_new_game_menu_item (gui_data)), "activate", G_CALLBACK (handlers_new_game), (gpointer) general_data);
    g_signal_connect (G_OBJECT (gui_data_get_exit_menu_item (gui_data)), "activate", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (gui_data_get_about_menu_item (gui_data)), "activate", G_CALLBACK (show_about_popup), NULL);

    return;
}

void
handlers_new_game (GtkMenuItem* new_game_menu_item, gpointer user_data)
{
    GeneralData* general_data = (GeneralData*) user_data;

    game_data_set (general_data->game_data);

	if (game_teller_set_first (general_data->game_data) == 0){ // if CPU starts
        guint i;
        
        for (i = 0; i < cards_hand_get_cards_num (general_data->game_data->player_hand); i++)
            gtk_widget_set_sensitive (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth (general_data->game_data->player_hand, i))), FALSE);

        g_timeout_add (1000, // 1 second
                       on_timeout_cpu_moves,
                       (gpointer) general_data);
    }
    
    return ;
}

void
show_about_popup (GtkMenuItem* about_menu_item, gpointer user_data)
{
    GtkWidget* dialog = gtk_about_dialog_new ();
    const gchar* authors[] = {"Loris \"Pyrox\" Gabriele", "Davide \"Unwlelt\" Benotto", NULL};
    const gchar* comments = "A Final Fantasy 8 card game clone written in C and Gtk+";
    const gchar* license = "The MIT License (MIT)\n\nCopyright (c) 2014 Loris \"Pyrox\" Gabriele, Davide \"Unwlelt\" Benotto\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files (the \"Software\"), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in\nall copies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\nTHE SOFTWARE.";

    gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG(dialog), "gPlead");
    gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(dialog), "0.1");
    gtk_about_dialog_set_website (GTK_ABOUT_DIALOG(dialog), "https://github.com/Pyr0x1/TripleTriad");
    gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(dialog), authors);
    gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG(dialog), comments);
    gtk_about_dialog_set_license (GTK_ABOUT_DIALOG(dialog), license);

    gtk_dialog_run (GTK_DIALOG (dialog));

    gtk_widget_destroy (dialog);

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

    return;
}

void
on_buttonfield_toggled (GtkToggleButton* button, gpointer user_data)
{
	GeneralData* general_data = (GeneralData*) user_data;
    GameData* game_data = (GameData*) general_data_get_game_data (general_data);
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
            
            game_data->timer_id = g_timeout_add (1000,	// 1 second
                           on_timeout_cpu_moves,
                           (gpointer) user_data);
            
            game_teller_switch_player (game_data);
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
	GeneralData* general_data = (GeneralData*) user_data;
    GameData* game_data = (GameData*) general_data_get_game_data (general_data);
    GuiData* gui_data = (GuiData*) general_data_get_gui_data (general_data);
    CardsHand* player_hand = (CardsHand*) game_data->player_hand;
    GameField* game_field = (GameField*) game_data->game_field;
    CardsHand* cpu_hand = (CardsHand*) game_data->cpu_hand;
    GtkScore* player_score = (GtkScore*) game_data->player_score;
    GtkScore* cpu_score = (GtkScore*) game_data->cpu_score;
	
    guint i;

	game_data->timer_id = 0;

	game_play_cpu_card_greedy (game_field, cpu_hand, player_score, cpu_score);
    
    // after the cpu moves, the player can newly select cards (only not void cards)
    for (i = 0; i < cards_hand_get_cards_num (player_hand); i++)
    	if (strcmp (gtk_widget_get_name (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth ( player_hand, i)))), "togglebuttonuser") == 0)
			gtk_widget_set_sensitive (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth (player_hand, i))), TRUE);
    
    game_teller_switch_player (game_data);
    
    if (game_is_over (game_data)){
		gint response;
		{
            // create game over popup
            GtkWidget *dialog;
            char buff[256];

            if (game_get_winner (game_data) == 1)
                sprintf (buff, "Player wins!\nRestart?");
            else
                sprintf (buff, "CPU wins!\nRestart?");

            dialog = gtk_message_dialog_new ( GTK_WINDOW (gui_data_get_main_window (gui_data)),
                                              GTK_DIALOG_DESTROY_WITH_PARENT,
                                              GTK_MESSAGE_QUESTION,
                                              GTK_BUTTONS_YES_NO,
                                              "%s", buff);
            
            gtk_window_set_title (GTK_WINDOW (dialog), "Game Over");

            response = gtk_dialog_run (GTK_DIALOG (dialog));

            gtk_widget_destroy (dialog);
		}

		if (response == GTK_RESPONSE_YES){
            game_data_set (game_data);  // start a new game
			
			if (game_teller_set_first (general_data->game_data) == 0){ // if CPU starts
                guint i;
                
                for (i = 0; i < cards_hand_get_cards_num (general_data->game_data->player_hand); i++)
                    gtk_widget_set_sensitive (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth (general_data->game_data->player_hand, i))), FALSE);

                g_timeout_add (1000, // 1 second
                               on_timeout_cpu_moves,
                               (gpointer) general_data);
            }
		}
	}
    
	return FALSE;	// if true this function would be called at regular timing, with false it will execute only once
}

