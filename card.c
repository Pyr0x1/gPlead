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

	new->top = rand() % max + 1;
	new->down = rand() % max + 1;
	new->left = rand() % max + 1;
	new->right = rand() % max + 1;

	return new;
}

void 
card_set_values (Card* card, guint top, guint down, guint left, guint right)
{
	card->top = top;
	card->down = down;
	card->left = left;
	card->right = right;

	return ;
}

guint 
card_get_top_value (Card* card)
{
	return card->top;
}

guint 
card_get_down_value (Card* card)
{
	return card->down;
}

guint 
card_get_left_value (Card* card)
{
	return card->left;
}

guint 
card_get_right_value (Card* card)
{
	return card->right;
}

gint 
card_compare (Card* card1, Card* card2, guint position)
{
	gint result;

	switch (position){
		case TOP: // card1 on the top of card2
			result = card_get_down_value (card1) - card_get_top_value (card2);		
			break;
		case RIGHT: // card1 on the right of card2
			result = card_get_left_value (card1) - card_get_right_value (card2);
			break;
		case DOWN: // card1 below card2
			result = card_get_top_value (card1) - card_get_down_value (card2);
			break;
		case LEFT: // card1 on the left of card2
			result = card_get_right_value (card1) - card_get_left_value (card2);
			break;
		default:
			fprintf(stderr, "Warning: invalid position passed to function \"card_compare\"");
	}

	return result;
}

void
card_switch_content (Card* card1, Card* card2)
{
	Card tmp;

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

	return ;
}

void 
card_clear (Card* card)
{
	card->top = 0;
	card->down = 0;
	card->left = 0;
	card->right = 0;

	return ;
}

void
card_free (Card* card)
{
	free(card);

	return ;
}