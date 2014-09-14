#ifndef COLLECTION_H
#define COLLECTION_H

#include "cardrange.h"

typedef struct collection_ {

	CardRange*** card_list;	// matrix of cards, card_list [level][card]
	guint level_num;		// number of levels
	guint* card_num;		// number of cards for each level, card_num [level] (each level can have a different number of card)

} Collection;

Collection* collection_load_file (gchar* filename);
guint collection_get_level_number (Collection* collection);
guint collection_get_card_number (Collection* collection, guint level);
CardRange* collection_get_card_range (Collection* collection, guint level, guint i);
void collection_free (Collection* collection);

#endif /* COLLECTION_H */

