#include <stdio.h>
#include <stdlib.h>
#include "collection.h"


Collection*
collection_load_file (gchar* filename)
{
	Collection* col;
	FILE *in;
	guint i, j;
	
	guint id, min_top, max_top, min_left, max_left, min_right, max_right, min_bottom, max_bottom;
	
	
	if (filename == NULL)
		return NULL;
	
	in = fopen (filename, "r");
	if (!in)
		return NULL;
	
	col = (Collection*) calloc (1, sizeof (Collection));
	
	fscanf (in, "%d", &col->level_num);
	col->card_num = (guint*) calloc ( col->level_num, sizeof (guint));
	for (i = 0; i < col->level_num; i++)
		fscanf (in, "%d", &col->card_num[i]);
	
	col->card_list = (CardRange***) calloc (col->level_num, sizeof(CardRange**));
	for (i = 0; i < col->level_num; i++)
		col->card_list[i] = (CardRange**) calloc (col->card_num[i], sizeof(CardRange*));
	
	for (i = 0; i < col->level_num; i++)
		for (j = 0; j < col->card_num[i]; j++){
			Range *range_top, *range_left, *range_right, *range_bottom;
			
			fscanf (in, "%d%d%d%d%d%d%d%d%d", &id, &min_top, &max_top, &min_left, &max_left, &min_right, &max_right, &min_bottom, &max_bottom);
			
			range_top = range_new ( min_top, max_top);
			range_left = range_new ( min_left, max_left);
			range_right = range_new ( min_right, max_right);
			range_bottom = range_new ( min_bottom, max_bottom);
			
			col->card_list[i][j] = card_range_new (range_top, range_right, range_bottom, range_left);
		}
	
	fclose(in);
	
	return col;
}


guint
collection_get_level_number (Collection* collection)
{
	if (collection == NULL)
		return 0;
	return collection->level_num;
}

guint
collection_get_card_number (Collection* collection, guint level)
{
	if (collection == NULL)
		return 0;
	if (level < collection->level_num)
		return collection->card_num [level];
	else
		return collection->card_num [0];
}

CardRange*
collection_get_card_range (Collection* collection, guint level, guint i)
{
	if (collection == NULL)
		return NULL;
	if (level < collection->level_num && i < collection->card_num [level])
		return collection->card_list[level][i];
	else
		return collection->card_list [0][0];
}

void
collection_free (Collection* collection)
{
	guint i, j;
	
	if (collection == NULL)
		return;
	
	for (i = 0; i < collection->level_num; i++){
		for (j = 0; j < collection->card_num[i]; j++)
			card_range_free (collection->card_list[i][j]);
		
		free (collection->card_list[i]);
	}

	free (collection->card_list);
	free (collection->card_num);
}

