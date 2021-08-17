/*
	----------------------------------------------
	The Sims 2 Game Boy Advance Save File Research
	----------------------------------------------

	File: B46P.sav
	Authors: SuperSaiyajinStackZ
	Version: 0.1
	Purpose: Shows the structure of the Item "Packages" from The Sims 2 Game Boy Advance.
	Category: Save File Research
	Last Updated: 17 August 2021
	-----------------------------------------

	See the Research for more information to the structure.
*/

#include <string>


struct Item {
	uint8_t ID = 0xE6; // The Item ID; 0x0.
	uint8_t Flag = 0x0; // The Item Flag; 0x1.
	uint8_t UseCount = 0x0; // The Item Use Count; 0x2.
};


struct ItemPackage {
	uint8_t Count = 0x0; // The amount of active Items from the Package; 0x0.
	Item Slot1; // The first Item Slot from the Package; 0x1 - 0x3.
	Item Slot2; // The second Item Slot from the Package; 0x4 - 0x6.
	Item Slot3; // The third Item Slot from the Package; 0x7 - 0x9.
	Item Slot4; // The fourth Item Slot from the Package; 0xA - 0xC.
	Item Slot5; // The fifth Item Slot from the Package; 0xD - 0xF.
	Item Slot6; // The sixth Item Slot from the Package; 0x10 - 0x12.
};