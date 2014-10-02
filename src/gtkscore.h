#ifndef GTKSCORE_H
#define GTKSCORE_H

#include <gtk/gtk.h>

typedef struct gtkscore {

	GtkLabel* label;
	guint score;

} GtkScore;

GtkScore* gtk_score_new (GtkLabel* label);
gint gtk_score_inc (GtkScore* gscore);
gint gtk_score_dec (GtkScore* gscore);
gint gtk_score_reset (GtkScore* gscore);
gint gtk_score_get (GtkScore* gscore);
void gtk_score_free (GtkScore* gscore);

#endif /* GTKSCORE_H */

