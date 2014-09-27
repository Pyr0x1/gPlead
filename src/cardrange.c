#include <stdio.h>
#include <stdlib.h>
#include "cardrange.h"

CardRange*
card_range_new (Range* top, Range* right, Range* down, Range* left)
{
	CardRange* new = (CardRange*) calloc (1, sizeof(CardRange));

	new->top = top;
	new->right = right;
	new->down = down;
	new->left = left;

	return new;
}

Range*
card_range_get_top (CardRange* card_range)
{
	return card_range->top;
}

Range*
card_range_get_right (CardRange* card_range)
{
	return card_range->right;
}

Range*
card_range_get_down (CardRange* card_range)
{
	return card_range->down;
}

Range*
card_range_get_left (CardRange* card_range)
{
	return card_range->left;
}

guint
card_range_get_random_value_top (CardRange* card_range)
{
	return range_get_random_value (card_range->top);
}

guint
card_range_get_random_value_right (CardRange* card_range)
{
	return range_get_random_value (card_range->right);
}

guint
card_range_get_random_value_down (CardRange* card_range)
{
	return range_get_random_value (card_range->down);
}

guint
card_range_get_random_value_left (CardRange* card_range)
{
	return range_get_random_value (card_range->left);
}

Card* card_range_get_random_card (CardRange* card_range){
	return card_new_with_values (	range_get_random_value (card_range->top),
			range_get_random_value (card_range->down),
			range_get_random_value (card_range->left),
			range_get_random_value (card_range->right));
}

void
card_range_free (CardRange* card_range)
{
	range_free (card_range->top);
	range_free (card_range->right);
	range_free (card_range->down);
	range_free (card_range->left);
	free (card_range);

	return ;
}
