#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtkcard.h"

GtkCard* 
gtk_card_new_empty (GtkToggleButton* button)
{
	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));

	new->button = button;
	new->card = card_new_empty ();
	new->full = FALSE;

	_gtk_card_create_labels (new);

	//gtk_button_set_label (GTK_BUTTON (new->button), "\t \n\n \t\t  \n\n\t ");

	return new;
}

GtkCard* 
gtk_card_new_with_values (GtkToggleButton* button, guint top, guint down, guint left, guint right, gboolean show)
{
	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));
	
	new->button = button;
	new->card = card_new_with_values (top, down, left, right);
	new->full = TRUE;

	_gtk_card_create_labels (new);

	if (show)
		gtk_card_write_label (new);

	/*
	if (show){
		sprintf (buff, "\t%d\n\n%d\t\t%d\n\n\t%d", card_get_top_value (new->card),
												   card_get_left_value (new->card),
												   card_get_right_value (new->card),
												   card_get_down_value (new->card));

		gtk_button_set_label (GTK_BUTTON (new->button), buff);
	}
	else
		gtk_button_set_label (GTK_BUTTON (new->button), "\t \n\n \t\t  \n\n\t ");
	*/

	return new;
}

GtkCard* 
gtk_card_new_random (GtkToggleButton* button, guint max, gboolean show)
{
	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));
	
	new->button = button;
	new->card = card_new_random (max);
	new->full = TRUE;

	_gtk_card_create_labels (new);

	if (show)
		gtk_card_write_label (new);

	/*
	if (show){
		sprintf (buff, "\t%d\n\n%d\t\t%d\n\n\t%d", card_get_top_value (new->card),
												   card_get_left_value (new->card),
												   card_get_right_value (new->card),
												   card_get_down_value (new->card));

		gtk_button_set_label (GTK_BUTTON (new->button), buff);
	}
	else
		gtk_button_set_label (GTK_BUTTON (new->button), "\t \n\n \t\t  \n\n\t ");
	*/

	return new;
}

GtkCard*
gtk_card_new_from_collection (GtkToggleButton* button, Collection* card_collection, guint level, gboolean show)
{
	CardRange* card_range = NULL;
	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));
	guint num_cards = collection_get_card_number (card_collection, level);
	guint rand_i = rand() % num_cards; 

	card_range = collection_get_card_range (card_collection, level, rand_i);

	new->button = button;
	new->card = card_new_from_ranges (card_range_get_top (card_range), 
									  card_range_get_down (card_range),
									  card_range_get_left (card_range),
									  card_range_get_right (card_range));
	new->full = TRUE;

	_gtk_card_create_labels (new);

	if (show)
		gtk_card_write_label (new);

	/*
	if (show){
		sprintf (buff, "\t%d\n\n%d\t\t%d\n\n\t%d", card_get_top_value (new->card),
												   card_get_left_value (new->card),
												   card_get_right_value (new->card),
												   card_get_down_value (new->card));

		gtk_button_set_label (GTK_BUTTON (new->button), buff);
	}
	else
		gtk_button_set_label (GTK_BUTTON (new->button), "\t \n\n \t\t  \n\n\t ");
	
	*/

	return new;
}

void
gtk_card_set_full (GtkCard* gcard, gboolean value)
{
	gcard->full = value;

	return ;
}

GtkToggleButton* 
gtk_card_get_button (GtkCard* gcard)
{
	return gcard->button;
}

gboolean 
gtk_card_is_selected (GtkCard* gcard)
{
	return gtk_toggle_button_get_active (gcard->button);
}

gboolean
gtk_card_is_full (GtkCard* gcard)
{
	return gcard->full;
}

gint
gtk_card_compare (GtkCard* gcard1, GtkCard* gcard2, guint position)
{
	return card_compare (gcard1->card, gcard2->card, position);
}

void 
gtk_card_switch_content (GtkCard* gcard1, GtkCard* gcard2)
{
	gboolean tmp_full;

	card_switch_content (gcard1->card, gcard2->card);

	tmp_full = gcard1->full;
	gcard1->full = gcard2->full;
	gcard2->full = tmp_full;

	if (gcard1->full == TRUE)
		gtk_card_write_label (gcard1);
	else
		gtk_card_clear (gcard1);

	if (gcard2->full == TRUE)
		gtk_card_write_label (gcard2);
	else
		gtk_card_clear (gcard2);

	return ;
}

void 
gtk_card_write_label (GtkCard* gcard)
{
	guint value;
	gchar buff[256];

	value = card_get_top_value (gcard->card);
	if (value == 10)
		sprintf (buff, "%s", "A");
	else
		sprintf (buff, "%d", value);
	gtk_label_set_label (gcard->labels[TOP], buff);

	value = card_get_left_value (gcard->card);
	if (value == 10)
		sprintf (buff, "%s", "A");
	else
		sprintf (buff, "%d", value);
	gtk_label_set_label (gcard->labels[LEFT], buff);

	value = card_get_right_value (gcard->card);
	if (value == 10)
		sprintf (buff, "%s", "A");
	else
		sprintf (buff, "%d", value);
	gtk_label_set_label (gcard->labels[RIGHT], buff);

	value = card_get_down_value (gcard->card);
	if (value == 10)
		sprintf (buff, "%s", "A");
	else
		sprintf (buff, "%d", value);
	gtk_label_set_label (gcard->labels[DOWN], buff);

	gtk_card_set_full (gcard, TRUE);

	return ;
}

void 
gtk_card_clear (GtkCard* gcard)
{
	card_clear (gcard->card);

	gtk_label_set_label (gcard->labels[TOP], " ");
	gtk_label_set_label (gcard->labels[LEFT], " ");
	gtk_label_set_label (gcard->labels[RIGHT], " ");
	gtk_label_set_label (gcard->labels[DOWN], " ");

	gcard->full = FALSE;

	return ;
}

void 
gtk_card_unselect (GtkCard* gcard)
{
	gtk_toggle_button_set_active (gcard->button, FALSE);

	return ;
}

void 
gtk_card_free (GtkCard* gcard)
{
	card_free (gcard->card);
	free (gcard);

	return ;
}

/* Private functions */

void
_gtk_card_create_labels (GtkCard* gcard)
{
	GtkWidget* grid = NULL;

	grid = gtk_grid_new ();

	gtk_grid_set_row_spacing (GTK_GRID (grid), 10);
	gtk_grid_set_column_spacing (GTK_GRID (grid), 15);
	gtk_grid_set_row_homogeneous (GTK_GRID (grid), TRUE);
	gtk_grid_set_column_homogeneous (GTK_GRID (grid), TRUE);
	gtk_container_add (GTK_CONTAINER (gcard->button), grid);

	gcard->labels[0] = GTK_LABEL (gtk_label_new (" "));
	gtk_grid_attach (GTK_GRID (grid), GTK_WIDGET (gcard->labels[TOP]), 1, 0, 1, 1);

	gcard->labels[1] = GTK_LABEL (gtk_label_new (" "));
	gtk_grid_attach (GTK_GRID (grid), GTK_WIDGET (gcard->labels[LEFT]), 0, 1, 1, 1);

	gcard->labels[2] = GTK_LABEL (gtk_label_new (" "));
	gtk_grid_attach (GTK_GRID (grid), GTK_WIDGET (gcard->labels[RIGHT]), 2, 1, 1, 1);

	gcard->labels[3] = GTK_LABEL (gtk_label_new (" "));
	gtk_grid_attach (GTK_GRID (grid), GTK_WIDGET (gcard->labels[DOWN]), 1, 2, 1, 1);

	return ;
}
