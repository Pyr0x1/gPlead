#ifndef GTKCARD_H
#define GTKCARD_H

#include <gtk/gtk.h>
#include "card.h"

typedef struct gtkcard {

	gboolean full; // has values or is an "empty" card
	GtkToggleButton* button;
	Card* card;

} GtkCard;

GtkCard* gtk_card_new_empty (GtkToggleButton* button);
GtkCard* gtk_card_new_with_values (GtkToggleButton* button, guint top, guint down, guint left, guint right, gboolean show);
GtkCard* gtk_card_new_random (GtkToggleButton* button, guint max, gboolean show);
void gtk_card_set_full (GtkCard* gcard);
GtkToggleButton* gtk_card_get_button (GtkCard* gcard);
gboolean gtk_card_is_selected (GtkCard* gcard);
gboolean gtk_card_is_full (GtkCard* gcard);
void gtk_card_switch_content (GtkCard* gcard1, GtkCard* gcard2);
void gtk_card_write_label (GtkCard* gcard);
void gtk_card_clear (GtkCard* gcard);
void gtk_card_unselect (GtkCard* gcard);
void gtk_card_free (GtkCard* gcard);

#endif /* GTKCARD_H */