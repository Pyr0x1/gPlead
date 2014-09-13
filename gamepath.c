#include <stdio.h>
#include <stdlib.h>
#include "gamepath.h"

// return a vector of coordinates row-column (int[num_col*num_row][2], equivalent to int[num_cards_in_field][2])
// the path can be used to scan the field in an unordered way
gint**
generate_random_path (guint num_col, guint num_row)
{

	gint ** path;
	guint i;
	guint choice;
	
	path = (gint **) calloc (num_col*num_row, sizeof(gint*));
	
	for (i = 0; i < num_col*num_row; i++)
		path[i] = (gint *) calloc (2, sizeof(gint));
	
	choice = rand() % 3;
	
	switch (choice){
		case 0:	// ordered
			for (i = 0; i < num_col * num_row; i++){
				path[i][0] = i / num_col;	// row
				path[i][1] = i % num_col;	// col
			}
			break;

		case 1: // ordered inverse
			for (i = 0; i < num_col * num_row; i++){
				path[i][0] = (num_col * num_row - i - 1) / num_col;	// row
				path[i][1] = (num_col * num_row - i - 1) % num_col;	// col
			}
			break;

		case 2: // column ordered, from bottom left to top right
			for (i = 0; i < num_col * num_row; i++){
				path[i][0] = (num_col * num_row - i - 1) % num_row;	// row
				path[i][1] = (i) / num_col;	// col
			}
			break;
	}
	
	return path;
}

void
free_path (gint** path, guint num_col, guint num_row)
{
	guint i;

	for (i = 0; i < num_col * num_row; i++)
		free (path[i]);
	free (path);

	return ;
}