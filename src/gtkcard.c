#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtkcard.h"

GtkCard*
gtk_card_new_empty (GtkToggleButton* button)
{
	guint i;
	
	if (!button)
		return NULL;

	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));

	new->button = button;
	new->card = card_new_empty ();
	new->full = FALSE;
	
	for (i = 0; i < 4; i++)
		new->value_augmented[i] = 0;

	_gtk_card_create_labels (new);

	//gtk_button_set_label (GTK_BUTTON (new->button), "\t \n\n \t\t  \n\n\t ");

	return new;
}

GtkCard*
gtk_card_new_with_values (GtkToggleButton* button, guint top, guint down, guint left, guint right, guint element, gboolean show)
{
	guint i;
	
	if (!button)
		return NULL;

	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));

	new->button = button;
	new->card = card_new_with_values (top, down, left, right, element);
	new->full = TRUE;

	for (i = 0; i < 4; i++)
		new->value_augmented[i] = 0;
	
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
	guint i;
	
	if (!button)
		return NULL;

	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));

	new->button = button;
	new->card = card_new_random (max);
	new->full = TRUE;

	for (i = 0; i < 4; i++)
		new->value_augmented[i] = 0;

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
	guint i;
	
	if (!button || !card_collection)
		return NULL;

	CardRange* card_range = NULL;
	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));
	guint num_cards = collection_get_card_number (card_collection, level);
	if (num_cards == -1){	// level could be not available in collection
		free (new);
		return NULL;
	}
	guint rand_i = rand() % num_cards;

	card_range = collection_get_card_range (card_collection, level, rand_i); // not freed because collection is entirely freed later

	new->button = button;
	//new->card = card_new_from_ranges (card_range_get_top (card_range),
	//								  card_range_get_down (card_range),
	//								  card_range_get_left (card_range),
	//								  card_range_get_right (card_range));
	new->card = card_range_get_random_card (card_range);
	new->full = TRUE;

	for (i = 0; i < 4; i++)
		new->value_augmented[i] = 0;

	if (!new->card){
		free (new);
		return NULL;
	}

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

gint
gtk_card_set_from_collection (GtkCard* gcard, Collection* card_collection, guint level, gboolean show)
{
	Card* tmp_card = NULL;
	guint i;

	if (!gcard || !card_collection)
		return -1;

	CardRange* card_range = NULL;
	guint num_cards = collection_get_card_number (card_collection, level);

	if (num_cards == -1)	// level could be not available in collection
		return -1;

	guint rand_i = rand() % num_cards;

	card_range = collection_get_card_range (card_collection, level, rand_i); // not freed because collection is entirely freed later

	tmp_card = card_range_get_random_card (card_range);

	card_switch_content (gtk_card_get_card (gcard), tmp_card);

	card_free (tmp_card);

	gcard->full = TRUE;

	for (i = 0; i < 4; i++)
		gcard->value_augmented[i] = 0;
	
	return 0;
}

gint
gtk_card_set_full (GtkCard* gcard, gboolean value)
{
	if (!gcard)
		return -1;

	gcard->full = value;

	return 0;
}

GtkToggleButton*
gtk_card_get_button (GtkCard* gcard)
{
	if (!gcard)
		return NULL;

	return gcard->button;
}

Card*
gtk_card_get_card (GtkCard* gcard)
{
	if (!gcard)
		return NULL;

	return gcard->card;
}

gboolean
gtk_card_is_selected (GtkCard* gcard)
{
	if (!gcard)
		return FALSE;

	return gtk_toggle_button_get_active (gcard->button);
}

gboolean
gtk_card_is_full (GtkCard* gcard)
{
	if (!gcard)
		return FALSE;

	return gcard->full;
}

gint
gtk_card_compare (GtkCard* gcard1, GtkCard* gcard2, guint position)
{
	gint first_augmented, second_augmented;
	
	if (!gcard1 || !gcard2)
		return -10000;
	
	switch (position){
		case TOP:	// card1 on the top of card2
			first_augmented = gcard1->value_augmented[DOWN];
			second_augmented = gcard2->value_augmented[TOP];
			break;
		case RIGHT:	// card1 on the right of card2
			first_augmented = gcard1->value_augmented[LEFT];
			second_augmented = gcard2->value_augmented[RIGHT];
			break;
		case DOWN:	// card1 below card2
			first_augmented = gcard1->value_augmented[TOP];
			second_augmented = gcard2->value_augmented[DOWN];
			break;
		case LEFT:	// card1 on the left of card2
			first_augmented = gcard1->value_augmented[RIGHT];
			second_augmented = gcard2->value_augmented[LEFT];
			break;
		default:
			fprintf(stderr, "Warning: invalid position passed to function \"gtk_card_compare\"");
			return -10000;
	}
	
	return card_compare (gcard1->card, gcard2->card, position, first_augmented, second_augmented);
}

gint
gtk_card_switch_content (GtkCard* gcard1, GtkCard* gcard2)
{
	if (!gcard1 || !gcard2)
		return -1;

	gboolean tmp_full, tmp_augmented[4];
	guint i;

	if (card_switch_content (gcard1->card, gcard2->card) == -1)
		return -1;

	tmp_full = gcard1->full;
	gcard1->full = gcard2->full;
	gcard2->full = tmp_full;
	
	for (i = 0; i < 4; i++){
		tmp_augmented[i] = gcard1->value_augmented[i];
		gcard1->value_augmented[i] = gcard2->value_augmented[i];
		gcard2->value_augmented[i] = tmp_augmented[i];
	}

	return 0;
}

gint
gtk_card_switch_content_label (GtkCard* gcard1, GtkCard* gcard2)
{
	if (gtk_card_switch_content (gcard1, gcard2) == -1)
		return -1;

	if (gcard1->full == TRUE)
		gtk_card_write_label (gcard1);
	else
		gtk_card_clear (gcard1);

	if (gcard2->full == TRUE)
		gtk_card_write_label (gcard2);
	else
		gtk_card_clear (gcard2);

	return 0;
}

gint
gtk_card_write_label (GtkCard* gcard)
{
	if (!gcard)
		return -1;

	guint value, i, elem;
	gchar buff[256];


	for (i = 0; i < 4; i++)
		if (gcard->value_augmented[i] == 1)
	    	gtk_widget_set_name (GTK_WIDGET (gcard->labels[i]), "augmentedLabel");
		else if (gcard->value_augmented[i] == -1)
	    	gtk_widget_set_name (GTK_WIDGET (gcard->labels[i]), "decreasedLabel");
		else
	    	gtk_widget_set_name (GTK_WIDGET (gcard->labels[i]), "cardLabel");

	value = card_get_top_value (gcard->card);
	value += gcard->value_augmented[TOP];
	if (value == 0)
		sprintf (buff, "%s", "1");
	else if (value == 10)
		sprintf (buff, "%s", "A");
	else if (value == 11)
		sprintf (buff, "%s", "S");
	else
		sprintf (buff, "%d", value);
	gtk_label_set_label (gcard->labels[TOP], buff);

	value = card_get_left_value (gcard->card);
	value += gcard->value_augmented[LEFT];
	if (value == 0)
		sprintf (buff, "%s", "1");
	else if (value == 10)
		sprintf (buff, "%s", "A");
	else if (value == 11)
		sprintf (buff, "%s", "S");
	else
		sprintf (buff, "%d", value);
	gtk_label_set_label (gcard->labels[LEFT], buff);

	value = card_get_right_value (gcard->card);
	value += gcard->value_augmented[RIGHT];
	if (value == 0)
		sprintf (buff, "%s", "1");
	else if (value == 10)
		sprintf (buff, "%s", "A");
	else if (value == 11)
		sprintf (buff, "%s", "S");
	else
		sprintf (buff, "%d", value);
	gtk_label_set_label (gcard->labels[RIGHT], buff);

	value = card_get_down_value (gcard->card);
	value += gcard->value_augmented[DOWN];
	if (value == 0)
		sprintf (buff, "%s", "1");
	else if (value == 10)
		sprintf (buff, "%s", "A");
	else if (value == 11)
		sprintf (buff, "%s", "S");
	else
		sprintf (buff, "%d", value);
	gtk_label_set_label (gcard->labels[DOWN], buff);
	
	GdkPixbuf *pixbuf;
	GdkPixbuf *pixbuf2;

	elem = card_get_element (gcard->card);
	switch (elem){
		case ET_BLUE:
			//gtk_widget_set_name (GTK_WIDGET (gcard->element_label), "bluerune");
			//gtk_image_set_from_file (GTK_IMAGE (gcard->element_label), "blue_rune.bmp");
			
			
			pixbuf = gdk_pixbuf_new_from_file_at_scale ("data/blue_rune.png", 20, 20, FALSE, NULL);	// the size here does not matter, can be anything
			pixbuf2 = gdk_pixbuf_scale_simple (pixbuf, 20, 20, GDK_INTERP_NEAREST);	// this actually change the size
			
			gtk_image_set_from_pixbuf (GTK_IMAGE (gcard->element_label), pixbuf2);
			g_object_unref (pixbuf);
			g_object_unref (pixbuf2);
	
			break;
		case ET_GREEN:
			//gtk_widget_set_name (GTK_WIDGET (gcard->element_label), "greenrune");
			//gtk_image_set_from_file (GTK_IMAGE (gcard->element_label), "green_rune.bmp");
			
			
			pixbuf = gdk_pixbuf_new_from_file_at_scale ("data/green_rune.png", 20, 20, FALSE, NULL);	// the size here does not matter, can be anything
			pixbuf2 = gdk_pixbuf_scale_simple (pixbuf, 20, 20, GDK_INTERP_NEAREST);	// this actually change the size
			
			gtk_image_set_from_pixbuf (GTK_IMAGE (gcard->element_label), pixbuf2);
			g_object_unref (pixbuf);
			g_object_unref (pixbuf2);
	
			break;
		case ET_YELLOW:
			//gtk_widget_set_name (GTK_WIDGET (gcard->element_label), "yellowrune");
			//gtk_image_set_from_file (GTK_IMAGE (gcard->element_label), "yellow_rune.bmp");
			
			pixbuf = gdk_pixbuf_new_from_file_at_scale ("data/yellow_rune.png", 20, 20, FALSE, NULL);	// the size here does not matter, can be anything
			pixbuf2 = gdk_pixbuf_scale_simple (pixbuf, 20, 20, GDK_INTERP_NEAREST);	// this actually change the size
			
			gtk_image_set_from_pixbuf (GTK_IMAGE (gcard->element_label), pixbuf2);
			g_object_unref (pixbuf);
			g_object_unref (pixbuf2);
			break;
		case ET_RED:
			//gtk_widget_set_name (GTK_WIDGET (gcard->element_label), "redrune");
			//gtk_image_set_from_file (GTK_IMAGE (gcard->element_label), "red_rune.bmp");
			
			pixbuf = gdk_pixbuf_new_from_file_at_scale ("data/red_rune.png", 20, 20, FALSE, NULL);	// the size here does not matter, can be anything
			pixbuf2 = gdk_pixbuf_scale_simple (pixbuf, 20, 20, GDK_INTERP_NEAREST);	// this actually change the size
			
			gtk_image_set_from_pixbuf (GTK_IMAGE (gcard->element_label), pixbuf2);
			g_object_unref (pixbuf);
			g_object_unref (pixbuf2);
			
			break;
	}

	gtk_card_set_full (gcard, TRUE);

	return 0;
}

gint
gtk_card_clear_element_label (GtkCard* gcard)
{
	if (!gcard)
		return -1;

	//gtk_widget_set_name (GTK_WIDGET(gcard->element_label), "");
	//gtk_image_set_from_file (GTK_IMAGE (gcard->element_label), "void_rune.bmp");
	
	GdkPixbuf *pixbuf, *pixbuf2;
	
	pixbuf = gdk_pixbuf_new_from_file_at_scale ("data/void_rune.png", 20, 20, FALSE, NULL);	// the size here does not matter, can be anything
	pixbuf2 = gdk_pixbuf_scale_simple (pixbuf, 20, 20, GDK_INTERP_NEAREST);	// this actually change the size
	
	gtk_image_set_from_pixbuf (GTK_IMAGE (gcard->element_label), pixbuf2);
	g_object_unref (pixbuf);
	g_object_unref (pixbuf2);

	return 0;
}

gint
gtk_card_clear (GtkCard* gcard)
{
	guint i;
	
	if (!gcard)
		return -1;

	if (card_clear (gcard->card) == -1)
		return -1;

	gtk_label_set_label (gcard->labels[TOP], " ");
	gtk_label_set_label (gcard->labels[LEFT], " ");
	gtk_label_set_label (gcard->labels[RIGHT], " ");
	gtk_label_set_label (gcard->labels[DOWN], " ");
	//gtk_widget_set_name (GTK_WIDGET(gcard->element_label), "");
	//gtk_image_set_from_file (GTK_IMAGE (gcard->element_label), "void_rune.bmp");
	
	GdkPixbuf *pixbuf, *pixbuf2;
	
	pixbuf = gdk_pixbuf_new_from_file_at_scale ("data/void_rune.png", 20, 20, FALSE, NULL);	// the size here does not matter, can be anything
	pixbuf2 = gdk_pixbuf_scale_simple (pixbuf, 20, 20, GDK_INTERP_NEAREST);	// this actually change the size
	
	gtk_image_set_from_pixbuf (GTK_IMAGE (gcard->element_label), pixbuf2);
	g_object_unref (pixbuf);
	g_object_unref (pixbuf2);


	for (i = 0; i < 4; i++)
	    gtk_widget_set_name (GTK_WIDGET (gcard->labels[i]), "");
	
	gcard->full = FALSE;

	return 0;
}

void
gtk_card_unselect (GtkCard* gcard)
{
	if (!gcard)
		return;

	gtk_toggle_button_set_active (gcard->button, FALSE);

	return;
}

void
gtk_card_free (GtkCard* gcard)
{
	if (!gcard)
		return;

	card_free (gcard->card);
	free (gcard);

	return ;
}

/* Private functions */

gint
_gtk_card_create_labels (GtkCard* gcard)
{
	if (!gcard)
		return -1;

	GtkWidget* grid = NULL;

	grid = gtk_grid_new ();

	gtk_grid_set_row_spacing (GTK_GRID (grid), 4);
	gtk_grid_set_column_spacing (GTK_GRID (grid), 2);
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


	GdkPixbuf *pixbuf, *pixbuf2;
	
	pixbuf = gdk_pixbuf_new_from_file_at_scale ("data/void_rune.png", 20, 20, FALSE, NULL);	// the size here does not matter, can be anything
	pixbuf2 = gdk_pixbuf_scale_simple (pixbuf, 20, 20, GDK_INTERP_NEAREST);	// this actually change the size
	
	gcard->element_label = gtk_image_new_from_pixbuf (pixbuf2);
	g_object_unref (pixbuf);
	g_object_unref (pixbuf2);
	
	//gcard->element_label = GTK_LABEL (gtk_label_new (" "));
	//gcard->element_label = gtk_image_new_from_file ("void_rune.bmp");
	gtk_grid_attach (GTK_GRID (grid), GTK_WIDGET (gcard->element_label), 1, 1, 1, 1);

	return 0;
}

