#ifndef CARD_H
#define CARD_H

#include <glib.h>
#include "range.h"

enum position {

	TOP,
	LEFT,
	RIGHT,
	DOWN,
	SIDES_NUM

};

enum element_type {

	ET_BLUE,
	ET_GREEN,
	ET_YELLOW,
	ET_RED,
	ELEMENTS_NUM

};

typedef struct card {

	guint top;
	guint right;
	guint down;
	guint left;
	guint element;

} Card;

Card* card_new_empty ();
Card* card_new_with_values (guint top, guint down, guint left, guint right, guint element);
Card* card_new_random (guint max);
Card* card_new_from_ranges (Range* range_top, Range* range_down, Range* range_left, Range* range_right);
gint card_set_values (Card* card, guint top, guint down, guint left, guint right, guint element);
gint card_get_top_value (Card* card);
gint card_get_down_value (Card* card);
gint card_get_left_value (Card* card);
gint card_get_right_value (Card* card);
gint card_get_element (Card* card);
gint card_get_opposite_element (gint element);
gint card_compare (Card* card1, Card* card2, guint position, gint first_augmented, gint second_augmented);
gint card_switch_content (Card* card1, Card* card2);
gint card_clear (Card* card);
void card_free (Card* card);

#endif /* CARD_H */
