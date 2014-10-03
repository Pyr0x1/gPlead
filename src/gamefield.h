#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "gtkfieldcard.h"

typedef struct gamefield {

	guint rows;
	guint cols;
	GtkFieldCard*** gfield; // matrix of GtkFieldCards

} GameField;

GameField* game_field_new (guint field_num); // game field is supposed to be square (3x3)
gint game_field_add (GameField* game_field, GtkToggleButton* button);

gint game_field_get_rows (GameField* game_field);
gint game_field_get_cols (GameField* game_field);
GtkFieldCard* game_field_get_nth (GameField* game_field, guint row, guint col);
GtkFieldCard* game_field_get_random (GameField* game_field); // actually gets first free spot on game field
GtkFieldCard* game_field_get_selected (GameField* game_field);
gint game_field_clear (GameField* game_field);
void game_field_force_redraw (GameField* game_field);
void game_field_free (GameField* game_field);

#endif

