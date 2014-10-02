#ifndef GAMEPATH_H
#define GAMEPATH_H

#include <glib.h>

typedef struct gamepath {

	gint** path;
	guint num_row;
	guint num_col;

} GamePath;

GamePath* game_path_new_random (guint num_col, guint num_row);
gint game_path_get_nth_row (GamePath* game_path, guint n);
gint game_path_get_nth_col (GamePath* game_path, guint n);
void game_path_free (GamePath* game_path);

#endif /* GAMEPATH_H */

