/*
	----------------------------------------------
	The Sims 2 Game Boy Advance Save File Research
	----------------------------------------------

	File: B46P.sav
	Authors: SuperSaiyajinStackZ, Sim2Team
	Version: 0.1
	Purpose: Shows the structure of the Social Moves from The Sims 2 Game Boy Advance.
	Category: Save File Research
	Last Updated: 19 August 2021
	-----------------------------------------

	See the Research for more information to the structure.
*/

#include <string>


struct SocialMove {
	enum class Flag : uint8_t { Locked = 0x0, Unlocked = 0x1, Blocked = 0x2 };

	Flag Status = Flag::Locked; // The Status of the Social Move; 0x0.
	uint8_t Unknown1[0x3] = { 0x0 }; // Unknown; 0x1 - 0x3.
	uint8_t Level = 0x0; // The Level of the Social Move; 0x4.
	uint8_t Unknown2 = 0x0; // Unknown; 0x5.
	uint8_t BlockedHours = 0x0; // The hours for how long it's blocked; 0x6.
	uint8_t Unknown3 = 0x0; // Unknown; 0x7.
};