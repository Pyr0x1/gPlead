#include <stdio.h>
#include <stdlib.h>
#include "gtkfieldcard.h"

GtkFieldCard*
gtk_field_card_new_empty (GtkToggleButton* button, guint row, guint col)
{
	guint i;

	if (!button)
		return NULL;

	GtkFieldCard* new = (GtkFieldCard*) calloc (1, sizeof(GtkFieldCard));

	new->row = row;
	new->col = col;
	new->gcard = gtk_card_new_empty (button);

	for (i=0; i<4; i++)
		new->elements[i] = rand() % ELEMENTS_NUM;

	for (i=0; i<4; i++)
		switch (new->elements[i]){
			case ET_BLUE:
	    		gtk_widget_set_name (GTK_WIDGET (new->gcard->labels[i]), "bluerune");	// ET_BLUE
				break;
			case ET_GREEN:
	    		gtk_widget_set_name (GTK_WIDGET (new->gcard->labels[i]), "greenrune");	// ET_GREEN
				break;
			case ET_YELLOW:
	    		gtk_widget_set_name (GTK_WIDGET (new->gcard->labels[i]), "yellowrune");	// ET_YELLOW
				break;
			case ET_RED:
	    		gtk_widget_set_name (GTK_WIDGET (new->gcard->labels[i]), "redrune");	// ET_RED
				break;
		}


	return new;
}

GtkFieldCard*
gtk_field_card_new_with_values (GtkToggleButton* button, guint top, guint down, guint left, guint right, guint element, gboolean show, guint row, guint col)
{
	if (!button)
		return NULL;

	GtkFieldCard* new = (GtkFieldCard*) calloc (1, sizeof(GtkFieldCard));

	new->row = row;
	new->col = col;
	new->gcard = gtk_card_new_with_values (button, top, down, left, right, element, show);

	return new;
}

GtkFieldCard*
gtk_field_card_new_random (GtkToggleButton* button, guint max, gboolean show, guint row, guint col)
{
	if (!button)
		return NULL;

	GtkFieldCard* new = (GtkFieldCard*) calloc (1, sizeof(GtkFieldCard));

	new->row = row;
	new->col = col;
	new->gcard = gtk_card_new_random (button, max, show);

	return new;
}

GtkCard*
gtk_field_card_get_gtk_card (GtkFieldCard* gfcard)
{
	if (!gfcard)
		return NULL;

	return gfcard->gcard;
}

gint
gtk_field_card_get_row (GtkFieldCard* gfcard)
{
	if (!gfcard)
		return -1;

	return gfcard->row;
}

gint
gtk_field_card_get_col (GtkFieldCard* gfcard)
{
	if (!gfcard)
		return -1;

	return gfcard->col;
}

gint
gtk_field_card_clear (GtkFieldCard* gfcard)
{
	guint i;
	if (!gfcard)
		return -1;
	if (gtk_card_clear (gfcard->gcard) == -1)
		return -1;


	for (i=0; i<4; i++)
		gfcard->elements[i] = rand() % ELEMENTS_NUM;

	for (i=0; i<4; i++)
		switch (gfcard->elements[i]){
			case ET_BLUE:
	    		gtk_widget_set_name (GTK_WIDGET (gfcard->gcard->labels[i]), "bluerune");	// ET_BLUE
				break;
			case ET_GREEN:
	    		gtk_widget_set_name (GTK_WIDGET (gfcard->gcard->labels[i]), "greenrune");	// ET_GREEN
				break;
			case ET_YELLOW:
	    		gtk_widget_set_name (GTK_WIDGET (gfcard->gcard->labels[i]), "yellowrune");	// ET_YELLOW
				break;
			case ET_RED:
	    		gtk_widget_set_name (GTK_WIDGET (gfcard->gcard->labels[i]), "redrune");	// ET_RED
				break;
		}


	return 0;
}

// improve player card values if card rune is the same of field colors
gint
gtk_field_card_augment_values_from_runes (GtkFieldCard* gfcard, GtkCard* player_card){
	guint i;
	
	if (!gfcard || !player_card)
		return -1;
	
	// TODO
	// insert check for A value (cannot go to 11) or insert S value
	// insert array flag for each value, like bool GtkCard->value_augmented[4];
	// if value_augmented[i] is true, the label of that value is set appropriately (in bold or with a specific color) using css
	// with value_augmented flag the value increase may be delayed to another function, or completely avoided (with a check that write a increased value if the flag is true, leaving the original value unchanged)
	
	guint player_rune = player_card->card->element;
	
	for (i = 0; i < 4; i++)
		if (gfcard->elements[i] == player_rune)
			switch (i){
				case TOP:
					player_card->card->top++;
					break;
				case LEFT:
					player_card->card->left++;
					break;
				case RIGHT:
					player_card->card->right++;
					break;
				case DOWN:
					player_card->card->down++;
					break;
			}
	
	
	return 0;
}

void
gtk_field_card_free (GtkFieldCard* gfcard)
{
	if (!gfcard)
		return ;

	gtk_card_free (gfcard->gcard);
	free (gfcard);
}
