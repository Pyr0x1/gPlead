#include <stdio.h>
#include <stdlib.h>
#include "gtkfieldcard.h"

GtkFieldCard*
gtk_field_card_new_empty (GtkToggleButton* button, guint row, guint col)
{
	if (!button)
		return NULL;
	
	GtkFieldCard* new = (GtkFieldCard*) calloc (1, sizeof(GtkFieldCard));

	new->row = row;
	new->col = col;
	new->gcard = gtk_card_new_empty (button);

	return new;
}

GtkFieldCard* 
gtk_field_card_new_with_values (GtkToggleButton* button, guint top, guint down, guint left, guint right, gboolean show, guint row, guint col)
{
	if (!button)
		return NULL;
	
	GtkFieldCard* new = (GtkFieldCard*) calloc (1, sizeof(GtkFieldCard));

	new->row = row;
	new->col = col;
	new->gcard = gtk_card_new_with_values (button, top, down, left, right, show);

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

void
gtk_field_card_free (GtkFieldCard* gfcard)
{
	if (!gfcard)
		return;
	
	gtk_card_free (gfcard->gcard);
	free (gfcard);
}

