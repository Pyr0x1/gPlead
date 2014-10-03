#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "gamefield.h"
#include "gtkfieldcard.h"

GameField* 
game_field_new (guint field_num)
{
	GameField* new = (GameField*) calloc (1, sizeof (GameField));
	guint i;

	new->rows = field_num;
	new->cols = field_num;
	new->gfield = (GtkFieldCard***) calloc (field_num, sizeof (GtkFieldCard**));

	for (i = 0; i < new->rows; i++)
		new->gfield[i] = (GtkFieldCard**) calloc (field_num, sizeof (GtkFieldCard*));

	return new;
}

gint
game_field_add (GameField* game_field, GtkToggleButton* button)
{
	guint i, j;

	if (!game_field || !button)
		return -1;
	
	for (i = 0; i < game_field->rows; i++)
		for (j = 0; j < game_field->cols; j++)
			if (game_field_get_nth (game_field, i, j) == NULL)
				goto outofloop;

	outofloop:

	if (i >= game_field->rows || j >= game_field->cols)
		return -1;
	
	game_field->gfield[i][j] = gtk_field_card_new_empty (button, i, j);

	return 0;
}

gint
game_field_get_rows (GameField* game_field)
{
	if (!game_field)
		return -1;
	
	return game_field->rows;
}

gint
game_field_get_cols (GameField* game_field)
{
	if (!game_field)
		return -1;
	
	return game_field->cols;
}

GtkFieldCard*
game_field_get_nth (GameField* game_field, guint row, guint col)
{
	if (!game_field)
		return NULL;
	
	return game_field->gfield[row][col];
}

GtkFieldCard*
game_field_get_random (GameField* game_field)
{
	GtkFieldCard* tmp_card;
	guint i, j;

	if (!game_field)
		return NULL;
	
	for (i = 0; i < game_field_get_rows (game_field); i++){
		for (j = 0; j < game_field_get_cols (game_field); j++){
			tmp_card = game_field_get_nth (game_field, i, j);
			if (gtk_card_is_full (gtk_field_card_get_gtk_card (tmp_card)) == FALSE)
				return tmp_card;
		}
	}

	return NULL;
}

GtkFieldCard* 
game_field_get_selected (GameField* game_field)
{
	GtkFieldCard* field_card;
	guint i, j;

	if (!game_field)
		return NULL;
	
	for (i = 0; i < game_field_get_rows (game_field); i++){
        for (j = 0; j < game_field_get_cols (game_field); j++){
            field_card = game_field_get_nth (game_field, i, j);
            if (gtk_card_is_selected (gtk_field_card_get_gtk_card (field_card)) == FALSE && gtk_widget_is_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))))) // game field is selected when button is raised
                return field_card;
        }
    }
	
	return NULL; // "should" never return NULL
}

gint
game_field_clear (GameField* game_field)
{
	guint i, j;

	if (!game_field)
		return -1;

	for (i = 0; i < game_field_get_rows (game_field); i++){
		for (j = 0; j < game_field_get_cols (game_field); j++){
			if (gtk_field_card_clear (game_field_get_nth (game_field, i, j)) == -1)
				return -1;
		}
	}

	return 0;
}

void
game_field_force_redraw (GameField* game_field)
{
	guint i, j;

	if (!game_field)
		return;
	
	for (i = 0; i < game_field_get_rows (game_field); i++){
		for (j = 0; j < game_field_get_cols (game_field); j++){
			gtk_widget_queue_draw (GTK_WIDGET (gtk_card_get_button (gtk_field_card_get_gtk_card (game_field_get_nth (game_field, i, j)))));
		}
	}

	return ;
}

void 
game_field_free (GameField* game_field)
{
	guint i, j;

	if (!game_field)
		return ;
	
	for (i = 0; i < game_field_get_rows (game_field); i++){
		for (j = 0; j < game_field_get_cols (game_field); j++){
			gtk_field_card_free (game_field->gfield[i][j]);
		}
	}

	for (i = 0; i < game_field_get_rows (game_field); i++)
		free (game_field->gfield[i]);

	free (game_field->gfield);
	free (game_field);

	return ;
}

