#ifndef CARDSHAND_H
#define CARDSHAND_H

#include <glib.h>
#include "gtkcard.h"

typedef struct cardshand {

	guint cards_num;
	GtkCard** gcards;

} CardsHand;

CardsHand* cards_hand_new (guint cards_num);
gint cards_hand_add_empty (CardsHand* hand, GtkToggleButton* button);
gint cards_hand_add_random (CardsHand* hand, GtkToggleButton* button, guint rand_value, gboolean show);
gint cards_hand_add_from_collection (CardsHand* hand, GtkToggleButton* button, Collection* collection, guint level, gboolean show);

GtkCard* cards_hand_get_nth (CardsHand* hand, guint num);
GtkCard* cards_hand_get_random (CardsHand* hand); // actually gets the first not played card
GtkCard* cards_hand_get_selected (CardsHand* hand);
gint cards_hand_get_cards_num (CardsHand* hand);
void cards_hand_free (CardsHand* hand);

#endif /* CARDSHAND_H */

