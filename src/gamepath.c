#include <stdlib.h>
#include "gamepath.h"

// return a vector of coordinates row-column (int[num_col*num_row][2], equivalent to int[num_cards_in_field][2])
// the path can be used to scan the field in an unordered way
GamePath*
game_path_new_random (guint num_col, guint num_row)
{

	GamePath* game_path;
	guint i;
	guint choice;
	
	game_path = (GamePath*) calloc (1, sizeof(GamePath));

	game_path->path = (gint **) calloc (num_col*num_row, sizeof(gint*));
	
	for (i = 0; i < num_col*num_row; i++)
		game_path->path[i] = (gint *) calloc (2, sizeof(gint));
	
	game_path->num_row = num_row;
	game_path->num_col = num_col;

	choice = rand() % 3;
	
	
	switch (choice){
		case 0:	// ordered
			for (i = 0; i < num_col * num_row; i++){
				game_path->path[i][0] = i / num_col;	// row
				game_path->path[i][1] = i % num_col;	// col
			}
			break;

		case 1: // ordered inverse
			for (i = 0; i < num_col * num_row; i++){
				game_path->path[i][0] = (num_col * num_row - i - 1) / num_col;	// row
				game_path->path[i][1] = (num_col * num_row - i - 1) % num_col;	// col
			}
			break;

		case 2: // column ordered, from bottom left to top right
			for (i = 0; i < num_col * num_row; i++){
				game_path->path[i][0] = (num_col * num_row - i - 1) % num_row;	// row
				game_path->path[i][1] = (i) / num_col;	// col
			}
			break;
	}
	
	return game_path;
}

gint
game_path_get_nth_row (GamePath* game_path, guint n)
{
	if (n < game_path->num_row * game_path->num_col)
		return game_path->path[n][0];
	else
		return -1;
}

gint
game_path_get_nth_col (GamePath* game_path, guint n)
{
	if (n < game_path->num_row * game_path->num_col)
		return game_path->path[n][1];
	else
		return -1;
}

void
game_path_free (GamePath* game_path)
{
	guint i;

	for (i = 0; i < game_path->num_col * game_path->num_row; i++)
		free (game_path->path[i]);
	free (game_path->path);
	free (game_path);

	return ;
}
