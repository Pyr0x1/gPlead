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

	gtk_button_set_label (GTK_BUTTON (new->button), "\t \n\n \t\t  \n\n\t ");

	return new;
}

GtkCard* 
gtk_card_new_with_values (GtkToggleButton* button, guint top, guint down, guint left, guint right, gboolean show)
{
	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));
	gchar buff[256];
	
	new->button = button;
	new->card = card_new_with_values (top, down, left, right);
	new->full = TRUE;

	if (show){
		sprintf (buff, "\t%d\n\n%d\t\t%d\n\n\t%d", card_get_top_value (new->card),
												   card_get_left_value (new->card),
												   card_get_right_value (new->card),
												   card_get_down_value (new->card));

		gtk_button_set_label (GTK_BUTTON (new->button), buff);
	}
	else
		gtk_button_set_label (GTK_BUTTON (new->button), "\t \n\n \t\t  \n\n\t ");
	
	return new;
}

GtkCard* 
gtk_card_new_random (GtkToggleButton* button, guint max, gboolean show)
{
	GtkCard* new = (GtkCard*) calloc (1, sizeof(GtkCard));
	gchar buff[256];
	
	new->button = button;
	new->card = card_new_random (max);
	new->full = TRUE;

	if (show){
		sprintf (buff, "\t%d\n\n%d\t\t%d\n\n\t%d", card_get_top_value (new->card),
												   card_get_left_value (new->card),
												   card_get_right_value (new->card),
												   card_get_down_value (new->card));

		gtk_button_set_label (GTK_BUTTON (new->button), buff);
	}
	else
		gtk_button_set_label (GTK_BUTTON (new->button), "\t \n\n \t\t  \n\n\t ");

	return new;
}

void
gtk_card_set_full (GtkCard* gcard)
{
	gcard->full = TRUE;

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

void 
gtk_card_switch_content (GtkCard* gcard1, GtkCard* gcard2)
{
	gchar* label1 = strdup(gtk_button_get_label (GTK_BUTTON (gtk_card_get_button (gcard1))));
	gchar* label2 = strdup(gtk_button_get_label (GTK_BUTTON (gtk_card_get_button (gcard2))));
	gboolean tmp_full;

	gtk_button_set_label (GTK_BUTTON (gtk_card_get_button (gcard1)), label2);
	gtk_button_set_label (GTK_BUTTON (gtk_card_get_button (gcard2)), label1);
	card_switch_content (gcard1->card, gcard2->card);

	tmp_full = gcard1->full;
	gcard1->full = gcard2->full;
	gcard2->full = tmp_full;

	free (label1);
	free (label2);

	return ;
}

void 
gtk_card_write_label (GtkCard* gcard)
{
	gchar buff[256];

	sprintf (buff, "\t%d\n\n%d\t\t%d\n\n\t%d", card_get_top_value (gcard->card),
											   card_get_left_value (gcard->card),
											   card_get_right_value (gcard->card),
											   card_get_down_value (gcard->card));

	gtk_button_set_label (GTK_BUTTON (gcard->button), buff);

	return ;
}

void 
gtk_card_clear (GtkCard* gcard)
{
	card_clear (gcard->card);

	gtk_button_set_label (GTK_BUTTON (gcard->button), "\t \n\n \t\t \n\n\t ");

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