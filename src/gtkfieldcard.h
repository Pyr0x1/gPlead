/* "Extends" GtkCard to have coordinates for cards in field only */
/* To use functions belonging to GtkCard, use them passing gtk_field_card_get_gtk_card (gfcard) */

#ifndef GTKFIELDCARD_H
#define GTKFIELDCARD_H

#include <gtk/gtk.h>
#include "gtkcard.h"

typedef struct gtkfieldcard {

	guint row;
	guint col;
	GtkCard* gcard;
	guint elements[4];	// top, left, right, bottom

} GtkFieldCard;

GtkFieldCard* gtk_field_card_new_empty (GtkToggleButton* button, guint row, guint col);
GtkFieldCard* gtk_field_card_new_with_values (GtkToggleButton* button, guint top, guint down, guint left, guint right, guint element, gboolean show, guint row, guint col);
GtkFieldCard* gtk_field_card_new_random (GtkToggleButton* button, guint max, gboolean show, guint row, guint col);
GtkCard* gtk_field_card_get_gtk_card (GtkFieldCard* gfcard);
gint gtk_field_card_get_row (GtkFieldCard* gfcard);
gint gtk_field_card_get_col (GtkFieldCard* gfcard);
gint gtk_field_card_clear (GtkFieldCard* gfcard);
gint gtk_field_card_augment_values_from_runes (GtkFieldCard* gfcard, GtkCard* player_card);
gint gtk_field_card_get_expected_augmentation (GtkFieldCard* gfcard, GtkCard* gcard, guint position);
void gtk_field_card_free (GtkFieldCard* gfcard);

#endif /* GTKFIELDCARD_H */

