#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include "gui.h"
#include "cardshand.h"
#include "gamefield.h"
#include "game.h"
#include "handlers.h"

int
main (int argc, char *argv[])
{
	GeneralData* general_data;
	//GuiData* gui_data;
	//GameData* game_data;
	guint cards_num = 5, field_num = 3; // default values
	
	/* Parameters check */
	if (argc != 1 && argc != 3){
		fprintf (stderr, "Error, invalid arguments\n");
		return -1;
	}
	else {
		if (argc == 3){
	    	cards_num = atoi (argv[1]);
	    	field_num = atoi (argv[2]);
	        if (cards_num >= 5 && field_num >= 3){
	        	if ((cards_num * 2 - 1) != field_num * field_num){
	        		fprintf (stderr, "Error, size aren't good\n");
	        		return -2;
	        	}
	        }
	        else{
	            fprintf (stderr, "Error, size is too little\n");
	            return -3;
	        }
	    }
	}
	/* End of parameters check, here they should be valid */
	
	srand(time(NULL)); // random seed every time you run the program
	
	
	general_data = general_data_new ();
	general_data->gui_data = gui_create (cards_num, field_num);
	general_data->game_data = game_data_new (cards_num, 
							   field_num, 
							   general_data->gui_data);
	
	handlers_connect_all (general_data);
	
	gint choice;
	gint i;
	choice = rand() % 10000;
	if (choice >= 5000){
		// cpu has the first turn (otherwise the player keep the first move)
	    for (i = 0; i < cards_hand_get_cards_num (general_data->game_data->player_hand); i++)
			gtk_widget_set_sensitive (GTK_WIDGET (gtk_card_get_button (cards_hand_get_nth (general_data->game_data->player_hand, i))), FALSE);
	    
	    g_timeout_add (1000,	// 1 second
	                   on_timeout_cpu_moves,
	                   (gpointer) general_data);
	    
    	gtk_widget_set_name (general_data_get_gui_data (general_data)->move_teller, "togglebuttoncpuplayed");
	}
	else
    	gtk_widget_set_name (general_data_get_gui_data (general_data)->move_teller, "togglebuttonuser");

	// Start Gtk loop
	gtk_widget_show_all (gui_data_get_main_window (general_data->gui_data));    
	gtk_main ();
	
	general_data_free (general_data);
	
	return 0;
}

