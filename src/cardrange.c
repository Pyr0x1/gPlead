#include <stdio.h>
#include <stdlib.h>
#include "cardrange.h"

CardRange*
card_range_new (Range* top, Range* right, Range* down, Range* left)
{
	if (!top || !right || !down || !left)
		return NULL;
	
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
	if (!card_range)
		return NULL;
	
	return card_range->top;
}

Range*
card_range_get_right (CardRange* card_range)
{
	if (!card_range)
		return NULL;
	
	return card_range->right;
}

Range*
card_range_get_down (CardRange* card_range)
{
	if (!card_range)
		return NULL;
	
	return card_range->down;
}

Range*
card_range_get_left (CardRange* card_range)
{
	if (!card_range)
		return NULL;
	
	return card_range->left;
}

gint
card_range_get_random_value_top (CardRange* card_range)
{
	if (!card_range)
		return -1;
	
	return range_get_random_value (card_range->top);
}

gint
card_range_get_random_value_right (CardRange* card_range)
{
	if (!card_range)
		return -1;
	
	return range_get_random_value (card_range->right);
}

gint
card_range_get_random_value_down (CardRange* card_range)
{
	if (!card_range)
		return -1;
	
	return range_get_random_value (card_range->down);
}

gint
card_range_get_random_value_left (CardRange* card_range)
{
	if (!card_range)
		return -1;
	
	return range_get_random_value (card_range->left);
}

Card*
card_range_get_random_card (CardRange* card_range)
{
	if (!card_range)
		return NULL;
	
	gint top_, down_, left_, right_;
	top_ = range_get_random_value (card_range->top);
	down_ = range_get_random_value (card_range->down);
	left_ = range_get_random_value (card_range->left);
	right_ = range_get_random_value (card_range->right);
	
	if ( top_ == -1 || down_ == -1 || left_ == -1 || right_ == -1)
		return NULL;
	
	return card_new_with_values ( top_, down_, left_, right_);
}

void
card_range_free (CardRange* card_range)
{
	if (!card_range)
		return;

	range_free (card_range->top);
	range_free (card_range->right);
	range_free (card_range->down);
	range_free (card_range->left);
	free (card_range);

	return;
}

