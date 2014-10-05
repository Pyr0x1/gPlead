#ifndef GENERAL_H
#define GENERAL_H

#include "gui.h"
#include "game.h"

// this is a container for gui_data and game_data, both needed when creating a popup when the game is over

typedef struct general_data {
	
	GameData* game_data;
	GuiData* gui_data;
	
} GeneralData;

GeneralData* general_data_new ();
GameData* general_data_get_game_data (GeneralData* general_data);
GuiData* general_data_get_gui_data (GeneralData* general_data);
void general_data_free (GeneralData* general_data);

#endif /* GENERAL_H */

