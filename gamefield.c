#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "gamefield.h"
#include "gtkcard.h"

GameField* 
game_field_new (guint field_num)
{
	GameField* new = (GameField*) calloc (1, sizeof (GameField));
	guint i;

	new->rows = field_num;
	new->cols = field_num;
	new->gfield = (GtkCard***) calloc (field_num, sizeof (GtkCard**));

	for (i = 0; i < new->rows; i++)
		new->gfield[i] = (GtkCard**) calloc (field_num, sizeof (GtkCard*));

	return new;
}

void
game_field_add (GameField* game_field, GtkToggleButton* button)
{
	guint i, j;

	for (i = 0; i < game_field->rows; i++)
		for (j = 0; j < game_field->cols; j++)
			if (game_field_get_nth (game_field, i, j) == NULL)
				goto outofloop;

	outofloop:

	game_field->gfield[i][j] = gtk_card_new_empty (button);

	return ;
}

guint 
game_field_get_rows (GameField* game_field)
{
	return game_field->rows;
}

guint 
game_field_get_cols (GameField* game_field)
{
	return game_field->cols;
}

GtkCard*
game_field_get_nth (GameField* game_field, guint row, guint col)
{
	return game_field->gfield[row][col];
}

GtkCard*
game_field_get_random (GameField* game_field)
{
	GtkCard* tmp_card;
	guint i, j;

	for (i = 0; i < game_field_get_rows (game_field); i++){
		for (j = 0; j < game_field_get_cols (game_field); j++){
			tmp_card = game_field_get_nth (game_field, i, j);
			if (gtk_card_is_full (tmp_card) == FALSE)
				return tmp_card;
		}
	}

	return NULL;
}

GtkCard* 
game_field_get_selected (GameField* game_field)
{
	GtkCard* field_card;
	guint i, j;

	for (i = 0; i < game_field_get_rows (game_field); i++){
        for (j = 0; j < game_field_get_cols (game_field); j++){
            field_card = game_field_get_nth (game_field, i, j);
            if (gtk_card_is_selected (field_card) == FALSE && gtk_widget_is_sensitive (GTK_WIDGET(gtk_card_get_button (field_card)))) // game field is selected when button is raised
                return field_card;
        }
    }
	
	return NULL; // "should" never return NULL
}

void 
game_field_free (GameField* game_field)
{
	guint i, j;

	for (i = 0; i < game_field_get_rows (game_field); i++){
		for (j = 0; j < game_field_get_cols (game_field); j++){
			gtk_card_free (game_field->gfield[i][j]);
		}
	}

	for (i = 0; i < game_field_get_rows (game_field); i++)
		free (game_field->gfield[i]);

	free (game_field->gfield);
	free (game_field);

	return ;
}