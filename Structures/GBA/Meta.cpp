/*
	----------------------------------------------
	The Sims 2 Game Boy Advance Save File Research
	----------------------------------------------

	File: B46P.sav
	Authors: SuperSaiyajinStackZ, Sim2Team
	Version: 0.1
	Purpose: Shows the structure of the "Meta" from The Sims 2 Game Boy Advance.
	Category: Save File Research
	Last Updated: 09 September 2021
	-----------------------------------------

	See the Research for more information to the structure.
*/

#include <string>


struct Meta {
	uint8_t Unknown[0xFE7] = { 0x0 }; // Just completely unresearched yet; 0x0 - 0xFE6.
};