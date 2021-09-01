/*
	----------------------------------------------
	The Sims 2 Game Boy Advance Save File Research
	----------------------------------------------

	File: B46P.sav
	Authors: SuperSaiyajinStackZ, Sim2Team
	Version: 0.1
	Purpose: Shows the structure of the Meta Header from The Sims 2 Game Boy Advance.
	Category: Save File Research
	Last Updated: 02 September 2021
	-----------------------------------------

	See the Research for more information to the structure.
*/

#include <string>


struct MetaHeader {
	enum class SFXVolumes : uint8_t {
		Vol0 = 0x0, Vol1 = 0xC, Vol2 = 0x18, Vol3 = 0x24, Vol4 = 0x30, Vol5 = 0x3C, Vol6 = 0x48,
		Vol7 = 0x54, Vol8 = 0x60, Vol9 = 0x6C, Vol10 = 0x80
	};

	enum class MUSVolumes : uint8_t {
		Vol0 = 0x0, Vol1 = 0x19, Vol2 = 0x32, Vol3 = 0x4B, Vol4 = 0x64, Vol5 = 0x7D, Vol6 = 0x96,
		Vol7 = 0xAF, Vol8 = 0xC8, Vol9 = 0xE1, Vol10 = 0xFF
	};

	enum class Languages : uint8_t {
		English = 0x0, Dutch = 0x1, French = 0x2, German = 0x3, Italiano = 0x4, Spanish = 0x5
	};

	uint8_t Identifier[0x7] = { 0x53, 0x54, 0x57, 0x4E, 0x30, 0x32, 0x34 }; // The identifier the game uses, to validate the Savefile, which is "STWN024"; 0x0 - 0x6.
	uint8_t Unknown1 = 0x0; // Unknown; 0x7.
	SFXVolumes SoundEffectVolume = SFXVolumes::Vol0; // The Sound Effect Volume Level; 0x8.
	MUSVolumes MusicVolume = MUSVolumes::Vol0; // The Music Volume Level; 0x9.
	Languages Language = Languages::English; // The Language the game uses; 0xA.
	uint8_t Unknown2[0x3] = { 0x0 }; // Unknown; 0xB - 0xD.
	uint16_t Checksum = 0x0; // The Meta Header Checksum; 0xE - 0xF.

	uint8_t BigfootLovesChickens : 4; // Bigfoot Loves Chickens Minigame Level; 0x10.
	uint8_t CarCommercials : 4; // Car Commercial Minigame Level; 0x10.
	uint8_t KeelhaulinCards : 4; // Keelhaulin' Cards Minigame Level; 0x11.
	uint8_t CattleCleanup : 4; // Cattle Cleanup Minigame Level; 0x11.
	uint8_t KingChugChug : 4; // King Chug-Chug Minigame Level; 0x12.
	uint8_t CanyonJumping : 4; // Canyon Jumping Minigame Level; 0x12.
	uint8_t ChopShop : 4; // Chop Shop Minigame Level; 0x13.
	
	uint8_t Unknown3 : 4; // Unknown; 0x13.
	uint8_t Unknown4[0x4] = { 0x0 }; // Unknown; 0x14 - 0x18.
};