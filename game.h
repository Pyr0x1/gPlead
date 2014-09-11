#ifndef GAME_H
#define GAME_H

#include <glib.h>
#include "cardshand.h"
#include "gamefield.h"

typedef struct game_elems {

    CardsHand* player_hand;
    GameField* game_field;
    CardsHand* cpu_hand;

} GameData;

GameData* game_data_new (guint cards_num, guint field_num, GtkWidget** player_buttons, GtkWidget*** field_buttons, GtkWidget** cpu_buttons);
void game_data_free (GameData* game_data);

// these functions return true if the card was correctly played, false otherwise (like if no card is selected)
gboolean game_play_player_card_selected (GameField* game_field, CardsHand* player_hand);
gboolean game_play_cpu_card_random (GameField* game_field, CardsHand* cpu_hand);
gboolean game_play_cpu_card_greedy (GameField* game_field, CardsHand* cpu_hand);
gboolean game_play_cpu_card_best (GameField* game_field, CardsHand* cpu_hand);	// TODO
void game_conquer_cards (GameField* game_field, GtkFieldCard* field_card, gboolean is_player_card);

#endif

