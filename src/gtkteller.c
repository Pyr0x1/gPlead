#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtkteller.h"

GtkTeller*
gtk_teller_new (GtkLabel* label)
{
	GtkTeller* new = (GtkTeller *) calloc (1, sizeof (GtkTeller));

	new->label = label;

	return new;
}

GtkTeller*
gtk_teller_new_with_values (GtkLabel* label, guint current_player, gchar* player_id, gchar* cpu_id)
{
	GtkTeller* new = NULL;

	if (current_player > 1)
		return NULL; // only 2 players allowed

	new = (GtkTeller *) calloc (1, sizeof (GtkTeller));

	new->label = label;
	new->current_player = current_player;
	new->player_id = strdup (player_id);
	new->cpu_id = strdup (cpu_id);

	switch (current_player){
		case 0: // CPU
			gtk_widget_set_name (GTK_WIDGET (new->label), new->cpu_id);
			break;
		case 1: // Player
			gtk_widget_set_name (GTK_WIDGET (new->label), new->player_id);
			break;
	}

	return new;
}

GtkLabel*
gtk_teller_get_label (GtkTeller* teller)
{
	if (!teller)
		return NULL;
	else
		return teller->label;
}

gint
gtk_teller_get_current_player (GtkTeller* teller)
{
	if (!teller)
		return -1;
	else
		return teller->current_player;
}

gint
gtk_teller_switch_player (GtkTeller* teller)
{
	if (!teller)
		return -1;

	if (teller->current_player == 0){
		teller->current_player = 1;
		gtk_widget_set_name (GTK_WIDGET (teller->label), teller->player_id);
	}
	else {
		teller->current_player = 0;
		gtk_widget_set_name (GTK_WIDGET (teller->label), teller->cpu_id);
	}

	return teller->current_player;
}

gint
gtk_teller_set_first_player (GtkTeller* teller)
{
	if (!teller)
		return -1;
	else {

		gint choice = rand() % 10000;

		if (choice >= 5000){
			teller->current_player = 0;
			gtk_widget_set_name (GTK_WIDGET (teller->label), teller->cpu_id);
		}
		else {
			teller->current_player = 1;
			gtk_widget_set_name (GTK_WIDGET (teller->label), teller->player_id);
		}
	}

	return teller->current_player;
}

void
gtk_teller_free (GtkTeller* teller)
{
	free (teller->cpu_id);
	free (teller->player_id);
	free (teller);

	return ;
}