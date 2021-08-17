/*
	----------------------------------------------
	The Sims 2 Game Boy Advance Save File Research
	----------------------------------------------

	File: B46P.sav
	Authors: SuperSaiyajinStackZ
	Version: 0.2
	Purpose: Shows the structure of the Cast Members from The Sims 2 Game Boy Advance.
	Category: Save File Research
	Last Updated: 17 August 2021
	-----------------------------------------

	See the Research for more information to the structure.
*/

#include <string>


struct CastMember {
	enum class CastFeeling : uint8_t { Neutral = 0x0, Happy = 0x1, Angry = 0x2, Romantic = 0x3 }; // To make the feeling stuff more clear, to what value what feeling is.

	uint8_t FriendlyLevel = 0x3; // The friendly interaction level of the cast member; 0 - 3 is valid; 0x0.
	uint8_t RomanceLevel = 0x3; // The romance interaction level of the cast member; 0 - 3 is valid; 0x1.
	uint8_t IntimidateLevel = 0x3; // The intimidate interaction level of the cast member; 0 - 3 is valid; 0x2.
	CastFeeling Feeling = CastFeeling::Neutral; // The Feeling of the cast member; See the enum class above for what value is for which feeling; 0x3.
	uint8_t Unknown1[0x2] = { 0x0 }; // Unknown as of yet; 0x4 - 0x5.
	uint8_t FeelingEffectHours = 0x0; // The Hours that are left for the feeling effect; 0x6.
	bool RegisteredOnPhone = false; // The state if the cast member got registered on your phone; 0x7.
	bool SecretUnlocked = false; // The state if the cast member's secret has been unlocked; 0x8.
	uint8_t Unknown2 = 0x0; // Unknown as of yet; 0x9.
};