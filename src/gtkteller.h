#ifndef GTKTELLER_H
#define GTKTELLER_H

#include <gtk/gtk.h>

typedef struct gtk_teller {

	GtkLabel* label;
	guint current_player;
	gchar* player_id;
	gchar* cpu_id;

} GtkTeller;

GtkTeller* gtk_teller_new (GtkLabel* label);
GtkTeller* gtk_teller_new_with_values (GtkLabel* label, guint current_player, gchar* player_id, gchar* cpu_id);
GtkLabel* gtk_teller_get_label (GtkTeller* teller);
gint gtk_teller_get_current_player (GtkTeller* teller);
gint gtk_teller_switch_player (GtkTeller* teller);
gint gtk_teller_set_first_player (GtkTeller* teller);
void gtk_teller_free (GtkTeller* teller);

#endif /* GTKTELLER_H */