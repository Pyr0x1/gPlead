#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gui.h"
#include "handlers.h"

GuiData* 
gui_create (guint cards_num, guint field_num)
{
	/*------ Gui variables ------*/
	GtkWidget* window;
	GtkWidget* hbox;
	GtkWidget* vbox;
	GtkWidget* grid;
	GtkWidget* separator;
	GtkWidget* fake_label;
	GtkWidget** player_buttons;
    GtkWidget*** field_buttons;
    GtkWidget** cpu_buttons;
    GtkWidget* player_score_label;
    GtkWidget* cpu_score_label;
	GtkWidget* move_teller;
    GtkSizeGroup* size_group;

    /*------ Menu --------*/
    GtkWidget* menu_bar;
	GtkWidget* file_menu;
	GtkWidget* file_menu_item;
	GtkWidget* new_game_menu_item;
	GtkWidget* exit_menu_item;
	GtkWidget* help_menu;
	GtkWidget* help_menu_item;
	GtkWidget* about_menu_item;

    GuiData* gui_data;
    /*---------------------------*/

    /*---------- CSS ---------*/
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*------------------------*/

    /*-------- Other variables ---------*/
    guint i, j;
    guint label_padding;
    /*----------------------------------*/

    gtk_init (0, NULL);

    // Initialize Gtk
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "TripleTriad");
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    // Allocate arrays for buttons and gui data
    gui_data = (GuiData*) calloc (1, sizeof (GuiData));

    player_buttons = (GtkWidget**) calloc (cards_num, sizeof (GtkWidget*));
    cpu_buttons = (GtkWidget**) calloc (cards_num, sizeof (GtkWidget*));
    field_buttons = (GtkWidget***) calloc (field_num, sizeof (GtkWidget**));
    for (i = 0; i < field_num; i++)
    	field_buttons[i] = (GtkWidget**) calloc (field_num, sizeof (GtkWidget*));

    // Create menu
    menu_bar = gtk_menu_bar_new ();
	file_menu = gtk_menu_new ();
	file_menu_item = gtk_menu_item_new_with_label ("File");
	new_game_menu_item = gtk_menu_item_new_with_label ("New Game");
	exit_menu_item = gtk_menu_item_new_with_label ("Exit");
	help_menu = gtk_menu_new ();
	help_menu_item = gtk_menu_item_new_with_label ("Help");
	about_menu_item = gtk_menu_item_new_with_label ("About");

	gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), file_menu_item);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (file_menu_item), file_menu);
	gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), new_game_menu_item);
	gtk_menu_shell_append (GTK_MENU_SHELL (file_menu), exit_menu_item);

	gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), help_menu_item);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (help_menu_item), help_menu);
	gtk_menu_shell_append (GTK_MENU_SHELL (help_menu), about_menu_item);

	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add (GTK_CONTAINER (window), vbox);
	gtk_box_pack_start (GTK_BOX (vbox), menu_bar, TRUE, FALSE, 5);

    // Create horizontal box to place game elements (player cards, game field, cpu cards)
    hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous (GTK_BOX (hbox), FALSE);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, FALSE, 5);

    // Creates size group to let all buttons have the same size
    size_group = gtk_size_group_new (GTK_SIZE_GROUP_BOTH);

    // Create vertical box for player cards
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous (GTK_BOX (vbox), TRUE);

    // Pack widgets into vertical box
    for (i = 0; i < cards_num; i++){
	    player_buttons[i] = gtk_toggle_button_new_with_label (NULL);
	    gtk_box_pack_start (GTK_BOX (vbox), player_buttons[i], TRUE, FALSE, 5);
	    gtk_widget_set_name (player_buttons[i], "togglebuttonuser");
	    gtk_size_group_add_widget (size_group, player_buttons[i]);
	}

	// Adds player cards to horizontal box
	gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, FALSE, 5);

	// Adds vertical separator between player cards and game field
	separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start (GTK_BOX (hbox), separator, TRUE, FALSE, 5);

	// Creates grid for game field
	grid = gtk_grid_new ();
	gtk_grid_set_row_spacing (GTK_GRID (grid), 10);
	gtk_grid_set_column_spacing (GTK_GRID (grid), 10);
	gtk_grid_set_row_homogeneous (GTK_GRID (grid), TRUE);
	gtk_grid_set_column_homogeneous (GTK_GRID (grid), TRUE);

	label_padding = (cards_num - field_num) / 2;

	for (i = 0; i < field_num; i++){
		for (j = 0; j < field_num; j++){
			field_buttons[i][j] = gtk_toggle_button_new_with_label (NULL);
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (field_buttons[i][j]), TRUE);
			gtk_size_group_add_widget (size_group, field_buttons[i][j]);
			gtk_grid_attach (GTK_GRID (grid), field_buttons[i][j], j, i, 1, 1);
		}
	}

	// Fake labels to have space on top and bottom of game field

	for (i = 0; i < label_padding; i++){

		gtk_grid_insert_row (GTK_GRID (grid), 0);

		// add "move teller"
		move_teller = gtk_toggle_button_new_with_label (NULL);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (move_teller), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (move_teller), FALSE);
		gtk_size_group_add_widget (size_group, move_teller);
		gtk_grid_attach (GTK_GRID (grid), move_teller, 1, 0, 1, 1);
		
		/*
		fake_label = gtk_label_new (NULL);
    	gtk_widget_set_name (fake_label, "togglebuttoncpuplayed");
		gtk_size_group_add_widget (size_group, fake_label);
		gtk_grid_attach (GTK_GRID (grid), fake_label, 1, 0, 1, 1);
		*/
		gtk_grid_insert_row (GTK_GRID (grid), (field_num + 2 * label_padding - 1));

		fake_label = gtk_label_new (NULL);
		gtk_grid_attach (GTK_GRID (grid), fake_label, 1, (field_num + 2 * label_padding - 1), 1, 1);
	}
	
	// Add labels for score
	player_score_label = gtk_label_new (NULL);
	gtk_size_group_add_widget (size_group, player_score_label);
	gtk_grid_attach (GTK_GRID (grid), player_score_label, 0, 0, 1, 1);

	cpu_score_label = gtk_label_new (NULL);
	gtk_size_group_add_widget (size_group, cpu_score_label);
	gtk_grid_attach (GTK_GRID (grid), cpu_score_label, field_num - 1, 0, 1, 1);



	// Adds grid to horizontal box
	gtk_box_pack_start (GTK_BOX (hbox), grid, TRUE, FALSE, 5);

	// Adds vertical separator between game field and cpu cards
	separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start (GTK_BOX (hbox), separator, TRUE, FALSE, 5);

	// Create vertical box for cpu cards
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous (GTK_BOX (vbox), TRUE);

	// Pack widgets into vertical box
    for (i = 0; i < cards_num; i++){
	    cpu_buttons[i] = gtk_toggle_button_new_with_label (NULL);
	    gtk_widget_set_name (cpu_buttons[i], "togglebuttoncpu");
	    gtk_widget_set_sensitive (cpu_buttons[i], FALSE);
	    gtk_size_group_add_widget (size_group, cpu_buttons[i]);
	    gtk_box_pack_start (GTK_BOX (vbox), cpu_buttons[i], TRUE, FALSE, 5);
	}

    // Adds cpu cards to horizontal box
    gtk_box_pack_start (GTK_BOX (hbox), vbox, TRUE, FALSE, 5);	

    // CSS part
	provider = gtk_css_provider_new ();
	display = gdk_display_get_default ();
	screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	gsize bytes_written, bytes_read;

	const gchar* home = "style.css";

	GError *error = 0;

	gtk_css_provider_load_from_path (provider,
	                                  g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),
	                                  NULL);
	g_object_unref (provider);

	// Fill Gui data structure and return it
	gui_data->window = window;
	gui_data->cards_num = cards_num;
	gui_data->field_num = field_num;
    gui_data->player_buttons = player_buttons;
	gui_data->field_buttons = field_buttons;
	gui_data->cpu_buttons = cpu_buttons; 
	gui_data->player_score_label = player_score_label;
	gui_data->cpu_score_label = cpu_score_label;
	gui_data->move_teller = move_teller;

	gui_data->new_game_menu_item = new_game_menu_item;
	gui_data->exit_menu_item = exit_menu_item;
	gui_data->about_menu_item = about_menu_item;

	return gui_data;
}

GtkWidget*
gui_data_get_main_window (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	
	return gui_data->window;
}

GtkWidget**
gui_data_get_player_buttons (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	
	return gui_data->player_buttons;
}

GtkWidget**
gui_data_get_cpu_buttons (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	
	return gui_data->cpu_buttons;
}

GtkWidget***
gui_data_get_field_buttons (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	
	return gui_data->field_buttons;
}

GtkWidget*
gui_data_get_player_score_label (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	
	return gui_data->player_score_label;
}

GtkWidget*
gui_data_get_cpu_score_label (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	
	return gui_data->cpu_score_label;
}

gint 
gui_data_get_cards_num (GuiData* gui_data)
{
	if (!gui_data)
		return -1;
	
	return gui_data->cards_num;
}

gint
gui_data_get_field_num (GuiData* gui_data)
{
	if (!gui_data)
		return -1;
	
	return gui_data->field_num;
}

GtkWidget*
gui_data_get_player_button_nth (GuiData* gui_data, guint n)
{
	if (!gui_data)
		return NULL;
	
	if (n < gui_data->cards_num)
		return gui_data->player_buttons[n];
	else
		return NULL;

}

GtkWidget*
gui_data_get_cpu_button_nth (GuiData* gui_data, guint n)
{
	if (!gui_data)
		return NULL;
	
	if (n < gui_data->cards_num)
		return gui_data->cpu_buttons[n];
	else
		return NULL;
}

GtkWidget* 
gui_data_get_field_button_nth (GuiData* gui_data, guint row, guint col)
{
	if (!gui_data)
		return NULL;
	
	if (row < gui_data->field_num && col < gui_data->field_num)
		return gui_data->field_buttons[row][col];
	else
		return NULL;
}

GtkWidget*
gui_data_get_new_game_menu_item (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	else
		return gui_data->new_game_menu_item;
}

GtkWidget*
gui_data_get_exit_menu_item (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	else
		return gui_data->exit_menu_item;
}

GtkWidget*
gui_data_get_about_menu_item (GuiData* gui_data)
{
	if (!gui_data)
		return NULL;
	else
		return gui_data->about_menu_item;
}

void
gui_data_free (GuiData* gui_data)
{
	if (!gui_data)
		return;
	
	// Only free allocated arrays, widgets should be handled by Gtk itself
	free (gui_data->player_buttons);
	free (gui_data->field_buttons); 
	free (gui_data->cpu_buttons); 
	free (gui_data);

	return ;
}

