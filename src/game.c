#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "gamepath.h"

GameData*
game_data_new (guint cards_num, guint field_num, GuiData* gui_data)
{
	if (!gui_data)
		return NULL;

	GameData* game_data = (GameData *) calloc (1, sizeof (GameData));
	GtkWidget** player_buttons = gui_data_get_player_buttons (gui_data);
    GtkWidget*** field_buttons = gui_data_get_field_buttons (gui_data);
    GtkWidget** cpu_buttons = gui_data_get_cpu_buttons (gui_data);
    GtkWidget* player_score_label = gui_data_get_player_score_label (gui_data);
    GtkWidget* cpu_score_label = gui_data_get_cpu_score_label (gui_data);
    GtkWidget* teller_label = gui_data_get_teller_label (gui_data);

	guint i, j;

	game_data->timer_id = 0;

	// Creates player hand and cpu hand
    game_data->player_hand = cards_hand_new (cards_num);
    game_data->cpu_hand = cards_hand_new (cards_num);


	// creates collection of cards from file
	Collection *coll = NULL;
	coll = collection_load_file ("data/collection_1.txt");

	if (coll == NULL)
		return NULL;

    for (i = 0; i < cards_num; i++){
    	cards_hand_add_from_collection (game_data->player_hand, GTK_TOGGLE_BUTTON (player_buttons[i]), coll, i, TRUE);
    	cards_hand_add_from_collection (game_data->cpu_hand, GTK_TOGGLE_BUTTON (cpu_buttons[i]), coll, i, FALSE);
    }

	// collection no more needed
	collection_free (coll);

    // Creates game field
    game_data->game_field = game_field_new (field_num);

    for (i = 0; i < field_num; i++){
    	for (j = 0; j < field_num; j++){
    		game_field_add (game_data->game_field, GTK_TOGGLE_BUTTON (field_buttons[i][j]));
    	}
    }

    // Creates scores
    game_data->player_score = gtk_score_new (GTK_LABEL (player_score_label));
    game_data->cpu_score = gtk_score_new (GTK_LABEL (cpu_score_label));

    // Creates teller
    game_data->teller = gtk_teller_new_with_values (GTK_LABEL (teller_label), 1, "movetellerplayer", "movetellercpu");

    // shuffle decks
    cards_hand_shuffle (game_data->player_hand, 10, 0);
    cards_hand_shuffle (game_data->cpu_hand, 10, 1);

	return game_data;
}

gint
game_data_set (GameData* game_data)
{
	if (!game_data)
		return -1;

    guint cards_num, field_num;

	guint i, j;

	cards_num = game_data->player_hand->cards_num;
	field_num = game_data->game_field->cols;

	// creates collection of cards from file
	Collection *coll = NULL;
	coll = collection_load_file ("data/collection_1.txt");

	if (coll == NULL)
		return -1;

    for (i = 0; i < cards_num; i++){
    	GtkCard* gcp = cards_hand_get_nth (game_data->player_hand, i);
    	GtkCard* gcc = cards_hand_get_nth (game_data->cpu_hand, i);

    	gtk_card_set_from_collection (gcp, coll, i, TRUE);
    	gtk_card_set_from_collection (gcc, coll, i, FALSE);

    	gtk_card_write_label (gcp);

	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gcp)), "togglebuttonuser");
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gcc)), "togglebuttoncpu");

		gtk_widget_set_sensitive (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth (game_data->player_hand, i))), TRUE);

    	//cards_hand_add_from_collection (game_data->player_hand, GTK_TOGGLE_BUTTON (player_buttons[i]), coll, i, TRUE);
    	//cards_hand_add_from_collection (game_data->cpu_hand, GTK_TOGGLE_BUTTON (cpu_buttons[i]), coll, i, FALSE);
    }

	// collection no more needed
	collection_free (coll);

    for (i = 0; i < field_num; i++){
    	for (j = 0; j < field_num; j++){
    		GtkFieldCard* gcf = game_field_get_nth (game_data->game_field, i, j);

    		gtk_field_card_clear (gcf);

	    	gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gcf->gcard)), "fieldbutton");

			gtk_widget_set_sensitive (GTK_WIDGET (gtk_card_get_button (gtk_field_card_get_gtk_card (game_field_get_nth (game_data->game_field, i, j)))), TRUE);
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gtk_card_get_button (gtk_field_card_get_gtk_card (game_field_get_nth (game_data->game_field, i, j)))), TRUE);

    		//game_field_add (game_data->game_field, GTK_TOGGLE_BUTTON (field_buttons[i][j]));
    	}
    }

    // Creates scores
    gtk_score_reset (game_data->player_score);
    gtk_score_reset (game_data->cpu_score);

    // shuffle decks
    cards_hand_shuffle (game_data->player_hand, 10, 0);
    cards_hand_shuffle (game_data->cpu_hand, 10, 1);

	if (game_data->timer_id > 0)
		g_source_remove (game_data->timer_id);
	game_data->timer_id = 0;

	return 0;
}

gboolean
game_play_player_card_selected (GameField* game_field, CardsHand* player_hand, GtkScore* player_score, GtkScore* cpu_score)
{
    GtkCard* player_card = cards_hand_get_selected (player_hand);
	GtkFieldCard* field_card = game_field_get_selected (game_field);

	if (player_card != NULL && field_card != NULL){
		
		// must be called before any exchange, the values of player_card are modified
	    gtk_field_card_augment_values_from_runes (field_card, player_card);
	    
		gtk_card_unselect (player_card);
	    gtk_card_switch_content_label (player_card, gtk_field_card_get_gtk_card (field_card));
	    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (player_card)), FALSE);
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (player_card)), "");
	    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), FALSE);
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), "togglebuttonuser");
		gtk_card_clear_element_label (player_card);
		gtk_card_clear_element_label (gtk_field_card_get_gtk_card (field_card));

	    gtk_score_inc (player_score);

	    game_conquer_cards (game_field, field_card, TRUE, player_score, cpu_score);

	    return TRUE;
	}

	return FALSE;
}

gboolean
game_play_cpu_card_random (GameField* game_field, CardsHand* cpu_hand, GtkScore* player_score, GtkScore* cpu_score)
{
	GtkCard* cpu_card = cards_hand_get_random (cpu_hand);
	GtkFieldCard* field_card = game_field_get_random (game_field);

	if (cpu_card != NULL && field_card != NULL){
		
		// must be called before any exchange, the values of player_card are modified
	    gtk_field_card_augment_values_from_runes (field_card, cpu_card);
	    
		gtk_card_write_label (cpu_card);
		gtk_card_switch_content_label (cpu_card, gtk_field_card_get_gtk_card (field_card));
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (cpu_card)), "");
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), "togglebuttoncpuplayed");
	    gtk_toggle_button_set_active (gtk_card_get_button (gtk_field_card_get_gtk_card (field_card)), FALSE);
	    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), FALSE);
	    //printf ("Active random: %d\n", gtk_toggle_button_get_active (gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))));
		gtk_card_clear_element_label (cpu_card);
		gtk_card_clear_element_label (gtk_field_card_get_gtk_card (field_card));


	    gtk_score_inc (cpu_score);

	    return TRUE;
	}

	// if there is no card in hand, or no place in field, return with false

	return FALSE;
}

gboolean
game_play_cpu_card_greedy (GameField* game_field, CardsHand* cpu_hand, GtkScore* player_score, GtkScore* cpu_score)
{
	GtkCard* cpu_card = NULL;
	GtkFieldCard* field_card = NULL;
	GamePath* game_path;
	gboolean find;
	guint r, c, i, j;

	find = FALSE;

	// if it's the first turn (no card on the field) choose a random move
	for (r = 0; r < game_field_get_rows (game_field) && !find; r++)
		for (c = 0; c < game_field_get_cols (game_field) && !find; c++){
			// get a place on the field
			field_card = game_field_get_nth (game_field, r, c);

			// if it's full
			if( gtk_card_is_full ( gtk_field_card_get_gtk_card (field_card))){
				find = TRUE;		// end the search
			}
		}

	//if find is stil false no card has been found, so make a random move
	if (!find)
		return game_play_cpu_card_random (game_field, cpu_hand, player_score, cpu_score);

	// get a path to scan the field in a non obvious way
	game_path = game_path_new_random (game_field_get_cols (game_field), game_field_get_rows (game_field));

	// otherwise make a greedy choice (first card with gain will be played)
	find = FALSE;
	for (i = 0; i < cards_hand_get_cards_num (cpu_hand) && !find; i++){
		if (gtk_card_is_full (cards_hand_get_nth (cpu_hand, i))){ // if it's a card which hasn't been played yet

			// get a card on cpu hand
			cpu_card = cards_hand_get_nth (cpu_hand, i);
			/*
			for (r = 0; r < game_field_get_rows (game_field) && !find; r++){
				for (c = 0; c < game_field_get_cols (game_field) && !find; c++){*/
			for (j = 0; j < game_field_get_rows (game_field) * game_field_get_cols (game_field); j++){

					r = game_path_get_nth_row (game_path, j);
					c = game_path_get_nth_col (game_path, j);

					// get a place on the field
					field_card = game_field_get_nth (game_field, r, c);

					// if it's free
					if ( !gtk_card_is_full ( gtk_field_card_get_gtk_card ( field_card))){

						// find if there is a card near, compare values and check if can be obtained (gain)
						gint near_r[4], near_c[4], position[4], opposite_position[4];
						guint near_i;

						// 4 positions to check: up, down, left, right
						near_r[0] = r-1;
						near_c[0] = c;
						position[0] = DOWN;
						opposite_position[0] = TOP;
						near_r[1] = r+1;
						near_c[1] = c;
						position[1] = TOP;
						opposite_position[1] = DOWN;
						near_r[2] = r;
						near_c[2] = c-1;
						position[2] = RIGHT;
						opposite_position[2] = LEFT;
						near_r[3] = r;
						near_c[3] = c+1;
						position[3] = LEFT;
						opposite_position[3] = RIGHT;

						for (near_i = 0; near_i < 4 && !find; near_i++){
							if (near_r[near_i] >= 0 && near_r[near_i] < game_field_get_rows (game_field) &&
								near_c[near_i] >= 0 && near_c[near_i] < game_field_get_cols (game_field)){

								if (gtk_card_is_full ( gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]))) ){

									// compare values
									if (card_compare ((*cpu_card).card,
										(*gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]))).card ,
										position[near_i],
										cpu_card->value_augmented[opposite_position[near_i]],
										(*gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]))).value_augmented[position[near_i]]) > 0 ){	//  if cpu card beats the card on the field

										const gchar *card_name = gtk_widget_get_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))));

										if (strcmp( (char*)card_name, "togglebuttonuser") == 0 ){	// if the card is of the player

											find = TRUE;

											// play the card
											if (cpu_card != NULL && field_card != NULL){
												
												// must be called before any exchange, the values of player_card are modified
											    gtk_field_card_augment_values_from_runes (field_card, cpu_card);
	    
												gtk_card_write_label (cpu_card);
												gtk_card_switch_content_label (cpu_card, gtk_field_card_get_gtk_card (field_card));
											    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (cpu_card)), "");
											    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), "togglebuttoncpuplayed");
											    gtk_toggle_button_set_active (gtk_card_get_button (gtk_field_card_get_gtk_card (field_card)), FALSE);
											    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), FALSE);
											    //printf ("Active greedy: %d\n", gtk_toggle_button_get_active (gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))));
												gtk_card_clear_element_label (cpu_card);
												gtk_card_clear_element_label (gtk_field_card_get_gtk_card (field_card));

												gtk_score_inc (cpu_score);

												// obtain the near cards


												// get the near card
												//gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))), "togglebuttoncpuplayed");


												/*
												{
												// check if the other positions contains player card that can be obtained
												int index;

												for (index = near_i+1; index < 4; index++)
													if (near_r[index] >= 0 && near_r[index] < game_field_get_rows (game_field) &&
														near_c[index] >= 0 && near_c[index] < game_field_get_cols (game_field))

														if (gtk_card_is_full ( gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[index], near_c[index]))) ){
															const gchar *card_name2 = gtk_widget_get_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[index], near_c[index]) ))));

															if (strcmp ( (char*) card_name2, "togglebuttonuser") == 0 )
																if (gtk_card_compare (cpu_card, gtk_field_card_get_gtk_card (game_field_get_nth (game_field, near_r[index], near_c[index])), position[index]) > 0)
																		gtk_widget_set_name (GTK_WIDGET (gtk_card_get_button (gtk_field_card_get_gtk_card (game_field_get_nth (game_field, near_r[index], near_c[index]) ))), "togglebuttoncpuplayed");
														}

												}
												*/

												game_conquer_cards (game_field, field_card, FALSE, player_score, cpu_score);

												// free path
												/*for (i = 0; i < game_field_get_rows (game_field) * game_field_get_cols (game_field); i++)
													free (path[i]);
												free (path);*/
												game_path_free (game_path);

											    return TRUE;
											}

										}
									}
								}

							}
						}
					}
			}
		}
	}

	// free path
	/*for (i = 0; i < game_field_get_rows (game_field) * game_field_get_cols (game_field); i++)
		free (path[i]);
	free (path);*/
	game_path_free (game_path);

	// if there is no gain play a random card (when there is no card to play nor zone free on the field cpu_random will return false)
	return game_play_cpu_card_random (game_field, cpu_hand, player_score, cpu_score);

	return FALSE;
}


gboolean
game_play_cpu_card_best (GameField* game_field, CardsHand* cpu_hand)
{
	GtkCard* cpu_card = cards_hand_get_random (cpu_hand);
	GtkFieldCard* field_card = game_field_get_random (game_field);

	if (cpu_card != NULL && field_card != NULL){
		gtk_card_write_label (cpu_card);
		gtk_card_switch_content_label (cpu_card, gtk_field_card_get_gtk_card (field_card));
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (cpu_card)), "");
	    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), FALSE);
	    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), "togglebuttoncpuplayed");

	    return TRUE;
	}

	return FALSE;
}

gint
game_is_over (GameData* game_data)
{
	guint rows;
	guint cols;
	guint player_score;
	guint cpu_score;

	if (!game_data)
		return -1;

	rows = game_field_get_rows (game_data->game_field);
	cols = game_field_get_cols (game_data->game_field);
	player_score = gtk_score_get (game_get_player_score (game_data));
	cpu_score = gtk_score_get (game_get_cpu_score (game_data));

	if (player_score + cpu_score == rows * cols)
		return TRUE; // game over
	else
		return FALSE; // not game over yet
}

void
game_conquer_cards (GameField* game_field, GtkFieldCard* field_card, gboolean is_player_card, GtkScore* player_score, GtkScore* cpu_score)
{
	// find if there is a card near, compare values and check if can be obtained (gain)
	gint near_r[4], near_c[4], position[4];
	guint near_i;

	guint r, c;

	// start from the selected field zone and check near zones
	r = gtk_field_card_get_row (field_card);
	c = gtk_field_card_get_col (field_card);

	// 4 positions to check: up, down, left, right
	near_r[0]= r-1;
	near_c[0]= c;
	position[0]=DOWN;
	near_r[1]= r+1;
	near_c[1]= c;
	position[1]=TOP;
	near_r[2]= r;
	near_c[2]= c-1;
	position[2]=RIGHT;
	near_r[3]= r;
	near_c[3]= c+1;
	position[3]=LEFT;

	for (near_i = 0; near_i < 4; near_i++){
		if (near_r[near_i] >= 0 && near_r[near_i] < game_field_get_rows (game_field) &&
			near_c[near_i] >= 0 && near_c[near_i] < game_field_get_cols (game_field)) {

			if (gtk_card_is_full ( gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]))) ){

				// compare values
				if (gtk_card_compare (gtk_field_card_get_gtk_card (field_card), gtk_field_card_get_gtk_card (game_field_get_nth (game_field, near_r[near_i], near_c[near_i])), position[near_i]) > 0) {	//  if player card beats the card on the field

					const gchar *card_name = gtk_widget_get_name (GTK_WIDGET (gtk_card_get_button (gtk_field_card_get_gtk_card (game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))));

					if (is_player_card){
						if ( strcmp( (char*) card_name, "togglebuttoncpuplayed") == 0 ){	// if the card is of the cpu

							// get the near card
							gtk_widget_set_name (GTK_WIDGET (gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))), "togglebuttonuser");

							// update score
							gtk_score_inc (player_score);
							gtk_score_dec (cpu_score);

						}
					}
					else{
						if ( strcmp( (char*) card_name, "togglebuttonuser") == 0 ){	// if the card is of the player

							// get the near card
							gtk_widget_set_name (GTK_WIDGET (gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))), "togglebuttoncpuplayed");

							// update score
							gtk_score_inc (cpu_score);
							gtk_score_dec (player_score);

						}
					}
				}
			}
		}
	}

	return ;
}

GtkScore*
game_get_player_score (GameData* game_data)
{
	if (!game_data)
		return NULL;

	return game_data->player_score;
}

GtkScore*
game_get_cpu_score (GameData* game_data)
{
	if (!game_data)
		return NULL;

	return game_data->cpu_score;
}

gint
game_get_winner (GameData* game_data)
{
	guint player_score;
	guint cpu_score;

	if (!game_data)
		return -1;

	player_score = gtk_score_get (game_get_player_score (game_data));
	cpu_score =  gtk_score_get (game_get_cpu_score (game_data));

	if (player_score > cpu_score)
		return 1;
	else
		return 0;
}

gint
game_teller_set_first (GameData* game_data)
{
	if (!game_data)
		return -1;

	return gtk_teller_set_first_player (game_data->teller);
}

gint
game_teller_switch_player (GameData* game_data)
{
	if (!game_data)
		return -1;

	return gtk_teller_switch_player (game_data->teller);
}

void
game_data_free (GameData* game_data)
{
	if (!game_data)
		return;

	game_field_free (game_data->game_field);
    cards_hand_free (game_data->player_hand);
    cards_hand_free (game_data->cpu_hand);
    gtk_score_free (game_data->player_score);
    gtk_score_free (game_data->cpu_score);
    gtk_teller_free (game_data->teller);
    free (game_data);

	return;
}
