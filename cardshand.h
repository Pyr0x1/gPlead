#ifndef CARDSHAND_H
#define CARDSHAND_H

#include <glib.h>
#include "gtkcard.h"

typedef struct cardshand {

	guint cards_num;
	GtkCard** gcards;

} CardsHand;

CardsHand* cards_hand_new (guint cards_num);
void cards_hand_add_empty (CardsHand* hand, GtkToggleButton* button);
void cards_hand_add_random (CardsHand* hand, GtkToggleButton* button, guint rand_value, gboolean show);

GtkCard* cards_hand_get_nth (CardsHand* hand, guint num);
GtkCard* cards_hand_get_random (CardsHand* hand); // actually gets the first not played card
GtkCard* cards_hand_get_selected (CardsHand* hand);
guint cards_hand_get_cards_num (CardsHand* hand);
void cards_hand_free (CardsHand* hand);

#endif /* CARDSHAND_H */