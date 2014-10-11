#ifndef CARDRANGE_H
#define CARDRANGE_H

#include "range.h"
#include "card.h"

typedef struct cardrange {

	Range* top;
	Range* right;
	Range* down;
	Range* left;
	
	Range* element;

} CardRange;

CardRange* card_range_new (Range* top, Range* right, Range* down, Range* left, Range* element);
Range* card_range_get_top (CardRange* card_range);
Range* card_range_get_right (CardRange* card_range);
Range* card_range_get_down (CardRange* card_range);
Range* card_range_get_left (CardRange* card_range);
gint card_range_get_random_value_top (CardRange* card_range);
gint card_range_get_random_value_right (CardRange* card_range);
gint card_range_get_random_value_down (CardRange* card_range);
gint card_range_get_random_value_left (CardRange* card_range);
Card* card_range_get_random_card (CardRange* card_range);
void card_range_free (CardRange* card_range);

#endif /* CARDRANGE_H */
