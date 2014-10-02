#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

Card* 
card_new_empty ()
{
	Card* new = (Card*) calloc (1, sizeof(Card));

	return new;
}

Card* 
card_new_with_values (guint top, guint down, guint left, guint right)
{
	Card* new = (Card*) calloc (1, sizeof(Card));

	new->top = top;
	new->down = down;
	new->left = left;
	new->right = right;

	return new;
}

Card* 
card_new_random (guint max)
{
	Card* new = (Card*) calloc (1, sizeof(Card));

	//srand(time(NULL));
	
	if (max == 0)
		max = 1;
	
	new->top = rand() % max + 1;
	new->down = rand() % max + 1;
	new->left = rand() % max + 1;
	new->right = rand() % max + 1;
	
	
	return new;
}

Card*
card_new_from_ranges (Range* range_top, Range* range_down, Range* range_left, Range* range_right)
{
	if (!range_top || !range_down || !range_left || !range_right)
		return NULL;
	
	Card* new = (Card*) calloc (1, sizeof(Card));
	gint t, d, l, r;

	t = range_get_random_value (range_top);
	d = range_get_random_value (range_down);
	l = range_get_random_value (range_left);
	r = range_get_random_value (range_right);

	if ( t == -1 || d == -1 || l == -1 || r == -1){
		free (new);
		return NULL;
	}
	
	new->top = t;
	new->down = d;
	new->left = l;
	new->right = r;
	
	return new;
}

gint
card_set_values (Card* card, guint top, guint down, guint left, guint right)
{
	if (!card)
		return -1;
	
	card->top = top;
	card->down = down;
	card->left = left;
	card->right = right;

	return 0;
}

gint 
card_get_top_value (Card* card)
{
	if (!card)
		return -1;
	
	return card->top;
}

gint 
card_get_down_value (Card* card)
{
	if (!card)
		return -1;
	
	return card->down;
}

gint 
card_get_left_value (Card* card)
{
	if (!card)
		return -1;
	
	return card->left;
}

gint 
card_get_right_value (Card* card)
{
	if (!card)
		return -1;
	
	return card->right;
}

gint 
card_compare (Card* card1, Card* card2, guint position)
{
	gint result;
	
	if (!card1 || !card2)
		return -10000;
	

	switch (position){
		case TOP:	// card1 on the top of card2
			result = card_get_down_value (card1) - card_get_top_value (card2);		
			break;
		case RIGHT:	// card1 on the right of card2
			result = card_get_left_value (card1) - card_get_right_value (card2);
			break;
		case DOWN:	// card1 below card2
			result = card_get_top_value (card1) - card_get_down_value (card2);
			break;
		case LEFT:	// card1 on the left of card2
			result = card_get_right_value (card1) - card_get_left_value (card2);
			break;
		default:
			fprintf(stderr, "Warning: invalid position passed to function \"card_compare\"");
			result = -10000;
	}

	return result;
}

gint
card_switch_content (Card* card1, Card* card2)
{
	Card tmp;
	
	if (!card1 || !card2)
		return -1;
	

	tmp.top = card1->top;
	tmp.down = card1->down;
	tmp.left = card1->left;
	tmp.right = card1->right;

	card1->top = card2->top;
	card1->down = card2->down;
	card1->left = card2->left;
	card1->right = card2->right;

	card2->top = tmp.top;
	card2->down = tmp.down;
	card2->left = tmp.left;
	card2->right = tmp.right;

	return 0;
}

gint
card_clear (Card* card)
{
	if (!card)
		return -1;
	
	card->top = 0;
	card->down = 0;
	card->left = 0;
	card->right = 0;

	return 0;
}

void
card_free (Card* card)
{
	if (!card)
		return;
	
	free(card);

	return;
}
