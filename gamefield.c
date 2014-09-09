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

void
game_field_add (GameField* game_field, GtkToggleButton* button)
{
	guint i, j;

	for (i = 0; i < game_field->rows; i++)
		for (j = 0; j < game_field->cols; j++)
			if (game_field_get_nth (game_field, i, j) == NULL)
				goto outofloop;

	outofloop:

	game_field->gfield[i][j] = gtk_field_card_new_empty (button, i, j);

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

GtkFieldCard*
game_field_get_nth (GameField* game_field, guint row, guint col)
{
	return game_field->gfield[row][col];
}

GtkFieldCard*
game_field_get_random (GameField* game_field)
{
	GtkFieldCard* tmp_card;
	guint i, j;

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

	for (i = 0; i < game_field_get_rows (game_field); i++){
        for (j = 0; j < game_field_get_cols (game_field); j++){
            field_card = game_field_get_nth (game_field, i, j);
            if (gtk_card_is_selected (gtk_field_card_get_gtk_card (field_card)) == FALSE && gtk_widget_is_sensitive (GTK_WIDGET(gtk_card_get_button (gtk_field_card_get_gtk_card (field_card))))) // game field is selected when button is raised
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
			gtk_field_card_free (game_field->gfield[i][j]);
		}
	}

	for (i = 0; i < game_field_get_rows (game_field); i++)
		free (game_field->gfield[i]);

	free (game_field->gfield);
	free (game_field);

	return ;
}