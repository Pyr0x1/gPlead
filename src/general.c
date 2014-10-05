#include <stdio.h>
#include <stdlib.h>
#include "general.h"

GeneralData*
general_data_new ()
{
	GeneralData* general_data;
	
	general_data = (GeneralData*) calloc (1, sizeof (GeneralData));
	
	return general_data;
}

GameData*
general_data_get_game_data (GeneralData* general_data)
{
	if (!general_data)
		return NULL;
	else
		return general_data->game_data;
}

GuiData*
general_data_get_gui_data (GeneralData* general_data)
{
	if (!general_data)
		return NULL;
	else
		return general_data->gui_data;
}

void
general_data_free (GeneralData* general_data)
{
	if(!general_data)
		return ;
	
	game_data_free (general_data->game_data);
	gui_data_free (general_data->gui_data);
	
	return ;
}