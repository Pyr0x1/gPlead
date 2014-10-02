#include <stdio.h>
#include <stdlib.h>
#include "cardshand.h"
#include "gtkcard.h"

CardsHand* 
cards_hand_new (guint cards_num)
{
	CardsHand* new = (CardsHand*) calloc (1, sizeof (CardsHand));

	new->cards_num = cards_num;
	new->gcards = (GtkCard**) calloc (cards_num, sizeof (GtkCard*));

	return new;
}

gint
cards_hand_add_empty (CardsHand* hand, GtkToggleButton* button)
{
	guint i;
	
	if (!hand || !button)
		return -1;

	for (i = 0; i < hand->cards_num; i++)
		if (hand->gcards[i] == NULL)
			break;
	
	if(i >= hand->cards_num)
		return -1;
	
	hand->gcards[i] = gtk_card_new_empty (button);

	return 0;
}

gint
cards_hand_add_random (CardsHand* hand, GtkToggleButton* button, guint rand_value, gboolean show)
{
	guint i;

	if (!hand || !button)
		return -1;
	
	for (i = 0; i < hand->cards_num; i++)
		if (hand->gcards[i] == NULL)
			break;

	if (i >= hand->cards_num)
		return -1;

	hand->gcards[i] = gtk_card_new_random (button, rand_value, show);

	return 0;
}

gint
cards_hand_add_from_collection (CardsHand* hand, GtkToggleButton* button, Collection* collection, guint level, gboolean show)
{
	guint i;
	
	if (!hand || !button || !collection)
		return -1;

	for (i = 0; i < hand->cards_num; i++)
		if (hand->gcards[i] == NULL)
			break;

	if (i >= hand->cards_num)
		return -1;

	hand->gcards[i] = gtk_card_new_from_collection (button, collection, level, show);
	
	if (!hand->gcards[i])
		return -1;

	return 0;
}

GtkCard* 
cards_hand_get_nth (CardsHand* hand, guint num)
{
	if (!hand)
		return NULL;
	
	if (num < hand->cards_num)
		return hand->gcards[num];
	else
		return NULL;
}

GtkCard* 
cards_hand_get_random (CardsHand* hand)
{
	guint i;
	
	if (!hand)
		return NULL;

	for (i = 0; i < hand->cards_num; i++){
		if (gtk_card_is_full (hand->gcards[i])) // if it's a card which hasn't been played yet
			return hand->gcards[i];
	}

	return NULL;
}

GtkCard*
cards_hand_get_selected (CardsHand* hand)
{
	GtkCard* tmp_card = NULL;
	guint i;

	if (!hand)
		return NULL;
	
	for (i = 0; i < hand->cards_num; i++){
		tmp_card = cards_hand_get_nth (hand, i);
		
		if (gtk_card_is_selected (tmp_card) && gtk_widget_is_sensitive (GTK_WIDGET(gtk_card_get_button (tmp_card))))
			return tmp_card;
	}

	return NULL;
}

gint
cards_hand_get_cards_num (CardsHand* hand)
{
	if (!hand)
		return -1;
	
	return hand->cards_num;
}

void 
cards_hand_free (CardsHand* hand)
{
	guint i;

	if (!hand)
		return;
	
	for (i = 0; i < hand->cards_num; i++)
		gtk_card_free (cards_hand_get_nth (hand, i));

	free (hand->gcards);
	free (hand);

	return;
}

