#include <stdio.h>
#include <stdlib.h>
#include "gtkfieldcard.h"

GtkFieldCard*
gtk_field_card_new_empty (GtkToggleButton* button, guint row, guint col)
{
	guint i;
	guint n[ELEMENTS_NUM];

	if (!button)
		return NULL;

	GtkFieldCard* new = (GtkFieldCard*) calloc (1, sizeof(GtkFieldCard));

	new->row = row;
	new->col = col;
	new->gcard = gtk_card_new_empty (button);

	for (i = 0; i < ELEMENTS_NUM; i++)
		n[i] = 0;
	
	for (i = 0; i < 4; i++){
		new->elements[i] = rand() % ELEMENTS_NUM;
		if (n[new->elements[i]] == 2)
			new->elements[i] = (new->elements[i] + 1) % ELEMENTS_NUM;
		n[new->elements[i]]++;
	}

	for (i = 0; i < 4; i++)
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
	guint n[ELEMENTS_NUM];

	if (!gfcard)
		return -1;
	if (gtk_card_clear (gfcard->gcard) == -1)
		return -1;
	
	for (i = 0; i < ELEMENTS_NUM; i++)
		n[i] = 0;
	
	for (i = 0; i < 4; i++){
		gfcard->elements[i] = rand() % ELEMENTS_NUM;
		if (n[gfcard->elements[i]] == 2)
			gfcard->elements[i] = (gfcard->elements[i] + 1) % ELEMENTS_NUM;
		n[gfcard->elements[i]]++;
	}

	for (i = 0; i < 4; i++)
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
	
	guint player_rune = player_card->card->element;
	
	for (i = 0; i < 4; i++)
		if (gfcard->elements[i] == player_rune)
			player_card->value_augmented[i] = 1;
		else if (card_get_opposite_element(gfcard->elements[i]) == player_rune)
			player_card->value_augmented[i] = -1;
	
	return 0;
}

// return the expected augmentation on the value in the required position when gcard is played on gfcard field space
gint
gtk_field_card_get_expected_augmentation (GtkFieldCard* gfcard, GtkCard* gcard, guint position){
	
	if (gfcard->elements[position] == gcard->card->element)
		return 1;
	if (card_get_opposite_element(gfcard->elements[position]) == gcard->card->element)
		return -1;
	
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
