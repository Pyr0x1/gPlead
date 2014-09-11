#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	    game_conquer_cards (game_field, field_card, TRUE);

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

gboolean 
game_play_cpu_card_greedy (GameField* game_field, CardsHand* cpu_hand)
{
	GtkCard* cpu_card = NULL;
	GtkFieldCard* field_card = NULL;
	gboolean find;
	guint r,c,i;
	
	
	find = FALSE;
	// if it's the first turn (no card on the field) choose a random move
	for (r = 0; r < game_field_get_rows (game_field) && !find; r++)
		for (c = 0; c < game_field_get_cols (game_field) && !find; c++){
			// get a place on the field
			field_card = game_field_get_nth (game_field, r, c);
			
			// if it's full
			if( gtk_card_is_full ( gtk_field_card_get_gtk_card ( field_card))){
				find = TRUE;		// end the search
			}
		}
	
	//if find is stil false no card has been found, so make a random move
	if (!find)
		return game_play_cpu_card_random (game_field, cpu_hand);
	
	
	// otherwise make a greedy choice (first card with gain will be played)
	find = FALSE;
	for (i = 0; i < cpu_hand->cards_num && !find; i++){
		if (gtk_card_is_full (cpu_hand->gcards[i])){ // if it's a card which hasn't been played yet
			
			// get a card on cpu hand
			cpu_card = cards_hand_get_nth (cpu_hand, i);
			
			for (r = 0; r < game_field_get_rows (game_field) && !find; r++)
				for (c = 0; c < game_field_get_cols (game_field) && !find; c++){
					// get a place on the field
					field_card = game_field_get_nth (game_field, r, c);
					
					// if it's free
					if ( !gtk_card_is_full ( gtk_field_card_get_gtk_card ( field_card))){
						
						// find if there is a card near, compare values and check if can be obtained (gain)
						gint near_r[4], near_c[4], position[4];
						guint near_i;
						
						// 4 positions to check: up, down, left, right
						near_r[0] = r-1;
						near_c[0] = c;
						position[0] = DOWN;
						near_r[1] = r+1;
						near_c[1] = c;
						position[1] = TOP;
						near_r[2] = r;
						near_c[2] = c-1;
						position[2] = RIGHT;
						near_r[3] = r;
						near_c[3] = c+1;
						position[3] = LEFT;
						
						for (near_i = 0; near_i < 4 && !find; near_i++){
							if (near_r[near_i] >= 0 && near_r[near_i] < game_field_get_rows (game_field) &&
								near_c[near_i] >= 0 && near_c[near_i] < game_field_get_cols (game_field)){
								
								if (gtk_card_is_full ( gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]))) ){
									
									// compare values
									if (card_compare ((*cpu_card).card,
										(*gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]))).card ,
										position[near_i]) > 0 ){	//  if cpu card beats the card on the field
										
										const gchar *card_name = gtk_widget_get_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))));
										
										if (strcmp( (char*)card_name, "togglebuttonuser") == 0 ){	// if the card is of the player
											
											find=TRUE;
											
											// play the card
											if (cpu_card != NULL && field_card != NULL){
												gtk_card_write_label (cpu_card);
												gtk_card_switch_content (cpu_card, gtk_field_card_get_gtk_card (field_card));
											    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (cpu_card)), "");
											    gtk_widget_set_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), FALSE);
											    gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))), "togglebuttoncpuplayed");
										
												
												// obtain the near cards
												
												// get the near card
												gtk_widget_set_name (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))), "togglebuttoncpuplayed");
												
												
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
												
												game_conquer_cards( game_field, field_card, FALSE);
												
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
	
	// if there is no gain play a random card
	return game_play_cpu_card_random( game_field, cpu_hand);
	

	return FALSE;
}


gboolean 
game_play_cpu_card_best (GameField* game_field, CardsHand* cpu_hand)
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


void
game_conquer_cards (GameField* game_field, GtkFieldCard* field_card, gboolean is_player_card)
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
					
					
					if(is_player_card)
						if( strcmp( (char*) card_name, "togglebuttoncpuplayed") == 0 ){	// if the card is of the cpu
							
							// get the near card
							gtk_widget_set_name (GTK_WIDGET (gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))), "togglebuttonuser");
							
						}
					else
						if( strcmp( (char*) card_name, "togglebuttonuser") == 0 ){	// if the card is of the player
							
							// get the near card
							gtk_widget_set_name (GTK_WIDGET (gtk_card_get_button (gtk_field_card_get_gtk_card ( game_field_get_nth (game_field, near_r[near_i], near_c[near_i]) ))), "togglebuttoncpuplayed");
							
						}
				}
			}
		}
	}

	return ;
}
