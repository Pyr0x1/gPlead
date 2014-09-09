#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "gtkcard.h"

typedef struct gamefield {

	guint rows;
	guint cols;
	GtkCard*** gfield; // matrix of buttons

} GameField;

GameField* game_field_new (guint field_num); // game field is supposed to be square (3x3)
void game_field_add (GameField* game_field, GtkToggleButton* button);

guint game_field_get_rows (GameField* game_field);
guint game_field_get_cols (GameField* game_field);
GtkCard* game_field_get_nth (GameField* game_field, guint row, guint col);
GtkCard* game_field_get_random (GameField* game_field); // actually gets first free spot on game field
GtkCard* game_field_get_selected (GameField* game_field);
void game_field_free (GameField* game_field);

#endif