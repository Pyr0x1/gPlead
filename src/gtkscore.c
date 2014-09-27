#include <stdio.h>
#include <stdlib.h>
#include "gtkscore.h"

GtkScore*
gtk_score_new (GtkLabel* label)
{
	GtkScore* new = (GtkScore*) calloc (1, sizeof (GtkScore));
	gchar buff[256];

	new->label = label;
	new->score = 0;
	sprintf (buff, "%d", new->score);
	gtk_label_set_text (new->label, buff);

	return new;
}

void
gtk_score_inc (GtkScore* gscore)
{
	gchar buff[256];

	gscore->score++;
	sprintf (buff, "%d", gscore->score);
	gtk_label_set_text (gscore->label, buff);

	return ;
}

void
gtk_score_dec (GtkScore* gscore)
{
	gchar buff[256];

	gscore->score--;
	sprintf (buff, "%d", gscore->score);
	gtk_label_set_text (gscore->label, buff);

	return ;
}

void
gtk_score_reset (GtkScore* gscore)
{
	gchar buff[256];

	gscore->score = 0;
	sprintf (buff, "%d", gscore->score);
	gtk_label_set_text (gscore->label, buff);

	return ;
}

guint
gtk_score_get (GtkScore* gscore)
{
	return gscore->score;
}

void
gtk_score_free (GtkScore* gscore)
{
	free (gscore);

	return ;
}