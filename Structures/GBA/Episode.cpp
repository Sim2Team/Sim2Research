/*
	----------------------------------------------
	The Sims 2 Game Boy Advance Save File Research
	----------------------------------------------

	File: B46P.sav
	Authors: SuperSaiyajinStackZ, Sim2Team
	Version: 0.1
	Purpose: Shows the structure of the Episodes from The Sims 2 Game Boy Advance.
	Category: Save File Research
	Last Updated: 19 August 2021
	-----------------------------------------

	See the Research for more information to the structure.
*/

#include <string>


struct Episode {
	uint8_t PlotPointsCompleted = 0x0; // Plot Points Completed Rating; 0x0.
	uint8_t AspirationConversation = 0x0; // Aspiration Conversation Rating; 0x1.
	uint8_t HiddenWantCompleted = 0x0; // Hidden Want Completed Rating; 0x2.
	uint8_t ErrandCompleted = 0x0; // Errand Completed Rating; 0x3.
	bool Unlocked = false; // Episode Unlocked State; 0x4.
};