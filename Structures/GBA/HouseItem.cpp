/*
	----------------------------------------------
	The Sims 2 Game Boy Advance Save File Research
	----------------------------------------------

	File: B46P.sav
	Authors: SuperSaiyajinStackZ, Sim2Team
	Version: 0.1
	Purpose: Shows the structure of the House Items from The Sims 2 Game Boy Advance.
	Category: Save File Research
	Last Updated: 17 August 2021
	-----------------------------------------

	See the Research for more information to the structure.
*/

#include <string>


struct Item {
	enum class ItemDirection : uint8_t { Right = 0x1, Down = 0x3, Left = 0x5, Up = 0x7 }; // Item Directions.

	uint8_t ID = 0xE6; // The Item ID; 0x0.
	uint8_t Flag = 0x0; // The Item Flag; 0x1.
	uint8_t UseCount = 0x0; // The Item Use Count; 0x2.
	uint8_t XPosition = 0x0; // The X-Position of the Item; 0x3.
	uint8_t YPosition = 0x0; // The Y-Position of the Item; 0x4.
	ItemDirection Direction = ItemDirection::Down; // The Item Direction; 0x5.
};


struct HouseItems {
	uint8_t Count = 0x0; // The amount of Items from the House; 0x0.
	Item Slot1; // The first House Item; 0x1 - 0x6.
	Item Slot2; // The second House Item; 0x7 - 0xC.
	Item Slot3; // The third House Item; 0xD - 0x12.
	Item Slot4; // The fourth House Item; 0x13 - 0x18.
	Item Slot5; // The fifth House Item; 0x19 - 0x1E.
	Item Slot6; // The sixth House Item; 0x1F - 0x24.
	Item Slot7; // The seventh House Item; 0x25 - 0x2A.
	Item Slot8; // The eighth House Item; 0x2B - 0x30.
	Item Slot9; // The nineth House Item; 0x31 - 0x36.
	Item Slot10; // The tenth House Item; 0x37 - 0x3C.
	Item Slot11; // The eleventh House Item; 0x3D - 0x42.
	Item Slot12; // The twelveth House Item; 0x43 - 0x48.
};