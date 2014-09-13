#ifndef CARD_H
#define CARD_H

#include <glib.h>

enum position {

	TOP,
	RIGHT,
	DOWN,
	LEFT,
	SIDES_NUM

};

typedef struct card {

	guint top;
	guint right;
	guint down;
	guint left;

} Card;

Card* card_new_empty ();
Card* card_new_with_values (guint top, guint down, guint left, guint right);
Card* card_new_random (guint max);
void card_set_values (Card* card, guint top, guint down, guint left, guint right);
guint card_get_top_value (Card* card);
guint card_get_down_value (Card* card);
guint card_get_left_value (Card* card);
guint card_get_right_value (Card* card);
gint card_compare (Card* card1, Card* card2, guint position);
void card_switch_content (Card* card1, Card* card2);
void card_clear (Card* card);
void card_free (Card* card);

#endif /* CARD_H */