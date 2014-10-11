#ifndef GTKCARD_H
#define GTKCARD_H

#include <gtk/gtk.h>
#include "card.h"
#include "collection.h"

typedef struct gtkcard {

	gboolean full; // has values or is an "empty" card
	GtkToggleButton* button;
	Card* card;
	GtkLabel* labels[4];

} GtkCard;

GtkCard* gtk_card_new_empty (GtkToggleButton* button);
GtkCard* gtk_card_new_with_values (GtkToggleButton* button, guint top, guint down, guint left, guint right, guint element, gboolean show);
GtkCard* gtk_card_new_random (GtkToggleButton* button, guint max, gboolean show);
GtkCard* gtk_card_new_from_collection (GtkToggleButton* button, Collection* card_collection, guint level, gboolean show);
gint gtk_card_set_from_collection (GtkCard* gcard, Collection* card_collection, guint level, gboolean show);
gint gtk_card_set_full (GtkCard* gcard, gboolean value);
GtkToggleButton* gtk_card_get_button (GtkCard* gcard);
Card* gtk_card_get_card (GtkCard* gcard);
gboolean gtk_card_is_selected (GtkCard* gcard);
gboolean gtk_card_is_full (GtkCard* gcard);
gint gtk_card_compare (GtkCard* gcard1, GtkCard* gcard2, guint position);
gint gtk_card_switch_content (GtkCard* gcard1, GtkCard* gcard2);
gint gtk_card_switch_content_label (GtkCard* gcard1, GtkCard* gcard2);
gint gtk_card_write_label (GtkCard* gcard);
gint gtk_card_clear (GtkCard* gcard);
void gtk_card_unselect (GtkCard* gcard);
void gtk_card_free (GtkCard* gcard);

/* Private functions used only inside other ones */
gint _gtk_card_create_labels (GtkCard* gcard); // to be used AFTER creating new card

#endif /* GTKCARD_H */

