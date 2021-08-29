/*
*   This file is part of Sim2Research
*   Copyright (C) 2021 SuperSaiyajinStackZ, Sim2Team
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

/*
	----------------------------------------------
	The Sims 2 Game Boy Advance Savefile Tools
	----------------------------------------------

	File: Sim2ChecksumRehash.cpp
	Authors: SuperSaiyajinStackZ
	Version: 0.1
	Purpose: A C++ Tool that updates / rehashes invalid Checksums from a The Sims 2 Game Boy Advance Savefile.
	Full Description:
		This Tool updates the Checksums from your Savefile of The Sims 2 Game Boy Advance.
		If you have an invalid Checksum in your Settings Header, the game acts hard and completely formats your Savedata, in that case there is no recovering possible.
		However if there is an invalid Checksum in one of your Slots, the Game just doesn't display the Slot and keeps the Savedata as is.
		This Tool automatically detects invalid Checksums from your Savefile and properly updates / fixes them.
	Category: Savefile Tools
	Last Updated: August 26, 2021

	Note: Requires C++17 as the minimum to be compiled. Use 'g++ -std=c++17 ChecksumRehash.cpp -o ChecksumRehash.exe' for example to compile it.
	----------------------------------------------
*/


#include <cstring> // memcmp.
#include <memory> // Because i prefer using std::unique_ptr over raw pointers for data.
#include <string> // My standard include, which includes most things i need on my stuff.
#include <unistd.h> // For checking if the file even exist.



/*
	Specify, if you want it to update the Checksum directly without confirmation prompts (false), or with it (true).
	Having Quick Action enabled speeds up the process, that's being useful if you research the Savefile and don't want to confirm invalid Checksum updates everytime.
*/
//#define QUICK_ACTION


#ifndef QUICK_ACTION
	#include <iostream> // Only include iostream if not using quick action.
#endif



/* Some Helper functions. ;P */
void PrintMessage(const std::string &STR) { // Just prints a message, if not in quick action.
	#ifndef QUICK_ACTION
		printf(STR.c_str());
	#endif
};
bool Confirmation(const std::string &STR) { // Just does a confirmation message, if not in quick action.
	#ifndef QUICK_ACTION
		printf(STR.c_str());

		std::string Confirm = "";
		std::cin >> Confirm; // Get user input.

		return (Confirm == "1");
	#endif

	return true; // Just confirms the prompt, no way what if quick action.
};
void Exit() { // Just lets you type in something and press enter then exits the app, if not in quick action.
	#ifndef QUICK_ACTION
		std::string Something = "";
		printf("Action done. Type anything and press enter to exit.\n");
		std::cin >> Something;
	#endif
};



class ChecksumRehash {
public:
	/* All the Checksums. */
	enum class Content : uint8_t { SettingsHeader = 0, Slot1 = 1, Slot2 = 2, Slot3 = 3, Slot4 = 4 };

	ChecksumRehash(const std::string &FileName);
	void UpdateAll(const bool AllowWritingToFile = true);
private:
	/* Used to identify, if it's a proper The Sims 2 Game Boy Advance Savefile. */
	static constexpr uint8_t HeaderIdent[0x7] = { 0x53, 0x54, 0x57, 0x4E, 0x30, 0x32, 0x34 };

	/* Internal Variables for the Checksum-Rehasher. */
	std::unique_ptr<uint8_t[]> SaveData = nullptr;
	uint32_t SaveSize = 0x0;
	std::string SaveFile = "";
	bool ValidSaveFile = false;

	/* Internal Methods. */
	uint16_t Calculate(const Content CNT = Content::SettingsHeader) const;
	bool Verify(const Content CNT = Content::SettingsHeader) const;


	/*
		It seems like the game does check if a Slot exist with the following things:

		- Byte 0xD of the Slot MUST be larger as 0x0. If it's 0x0 / a NULL Terminator, then it doesn't exist.
		-- NOTE: 0xD is the first character from the name of the Sim.
			If you have 0xD: 0x0 and 0xE 0x53 or so, it also doesn't exist, as it doesn't check above a NULL Terminator.

		- The Checksum MUST be valid, or the Slot is not being displayed as well.
	*/
	bool SlotExist(const uint8_t Slot) const {
		if (this->ValidSaveFile && Slot >= 1 && Slot <= 4) return (this->SaveData.get()[(Slot * 0x1000) + 0xD] != 0x0);
		
		return false;
	};
};



/*
	The constructor of the ChecksumRehash class.
	Loads a Savefile with a specific path and checks if it is a valid The Sims 2 Game Boy Advance Savefile.

	const std::string &FileName: The path to the Savefile.
*/
ChecksumRehash::ChecksumRehash(const std::string &FileName) {
	this->SaveFile = FileName;

	/* Ensure the Savefile does exist. */
	if (access(this->SaveFile.c_str(), F_OK) == 0) {
		FILE *In = fopen(this->SaveFile.c_str(), "rb");

		if (In) {
			/* Get the size of the Savefile. */
			fseek(In, 0, SEEK_END);
			this->SaveSize = ftell(In);
			fseek(In, 0, SEEK_SET);

			/* 0x10000 OR 0x20000 are only valid sizes, however 0x10000 is the size from a retail cartridge and 0x20000 is often used from emulators. */
			if (this->SaveSize == 0x10000 || this->SaveSize == 0x20000) {
				PrintMessage("The size of the Savefile matches a The Sims 2 Game Boy Advance Save!\n");

				/* Initialize the Save Data unique_ptr. */
				this->SaveData = std::make_unique<uint8_t[]>(this->SaveSize);
				fread(this->SaveData.get(), 1, this->SaveSize, In);

				/*
					Now we are checking if the Savefile is actually a The Sims 2 Game Boy Advance one, by checking if the HeaderIdent does match.
					
					If you can't use memcmp, just loop through the HeaderIdent and check, if all of them match.
				*/
				this->ValidSaveFile = (memcmp(&this->HeaderIdent[0], this->SaveData.get(), 0x7) == 0);
				PrintMessage(std::string("The Identifier Header from the Savefile is: ") + std::string((this->ValidSaveFile ? "Valid!\n" : "Invalid!\n")));
			}

			fclose(In);
		}
	}
};



/*
	Calculates a Checksum from the Savefile.

	const ChecksumRehash::Content CNT: What should be calculated.

	Returns the Checksum as an uint16_t.
*/
uint16_t ChecksumRehash::Calculate(const ChecksumRehash::Content CNT) const {
	uint8_t Byte1 = 0, Byte2 = 0;

	if (this->ValidSaveFile) {
		switch(CNT) {
			case ChecksumRehash::Content::SettingsHeader: // Settings.
				for (uint16_t Idx = 0; Idx < (0x18 / 2); Idx++) {
					if (Idx == 0xE / 2) continue; // Skip the Checksum of the Settings Header.

					if (Byte1 + this->SaveData.get()[Idx * 2] > 255) Byte2++;

					Byte1 += this->SaveData.get()[Idx * 2];
					Byte2 += this->SaveData.get()[(Idx * 2) + 1];
				}

				Byte2++;
				break;

			case ChecksumRehash::Content::Slot1:
			case ChecksumRehash::Content::Slot2:
			case ChecksumRehash::Content::Slot3:
			case ChecksumRehash::Content::Slot4: // Slots.
				for (uint16_t Idx = 0; Idx < (0xFFE / 2); Idx++) {
					if (Byte1 + this->SaveData.get()[(((uint8_t)CNT) * 0x1000) + (Idx * 2)] > 255) Byte2++;

					Byte1 += this->SaveData.get()[(((uint8_t)CNT) * 0x1000) + (Idx * 2)];
					Byte2 += this->SaveData.get()[(((uint8_t)CNT) * 0x1000) + (Idx * 2) + 1];
				}

				Byte2++;
				break;
		}
	}

	return ((256 * (uint8_t)-Byte2) + (uint8_t)-Byte1); // 256 *, so it goes to the second byte from the uint16_t and then the + -> so it goes to the first byte.
};



/*
	Verifies a Checksum from the Savefile.

	const ChecksumRehash::Content CNT: What should be verified.

	Returns, if the Checksum is valid (true) or not (false).
*/
bool ChecksumRehash::Verify(const ChecksumRehash::Content CNT) const {
	if (this->ValidSaveFile) {
		switch(CNT) {
			case ChecksumRehash::Content::SettingsHeader: // Settings.
				return (this->Calculate(CNT) == *reinterpret_cast<uint16_t *>(this->SaveData.get() + 0xE));

			case ChecksumRehash::Content::Slot1:
			case ChecksumRehash::Content::Slot2:
			case ChecksumRehash::Content::Slot3:
			case ChecksumRehash::Content::Slot4: // Slots.
				return (this->Calculate(CNT) == *reinterpret_cast<uint16_t *>(this->SaveData.get() + (((uint8_t)CNT) * 0x1000) + 0xFFE)); 
		}
	}

	return false;
};



/*
	The main action call of the ChecksumRehash class.
	Goes through the Settings Header and Slots and fixes the Checksum, if invalid.

	const bool AllowWritingToFile: If after at least 1 Checksum got updated, the changes should be written back to the Savefile or not.
*/
void ChecksumRehash::UpdateAll(const bool AllowWritingToFile) {
	if (this->ValidSaveFile) {
		bool ChecksumUpdated = false;

		/* Start with the Settings Header. */
		uint16_t Checksum = this->Calculate(ChecksumRehash::Content::SettingsHeader);

		if (Checksum != *reinterpret_cast<uint16_t *>(this->SaveData.get() + 0xE)) {
			if (Confirmation("The Settings Header Checksum doesn't match. Do you want to fix it?\nType 1 and press enter for yes, something else for no: ")) {
				*reinterpret_cast<uint16_t *>(this->SaveData.get() + 0xE) = Checksum;
				ChecksumUpdated = true;
			}
			
		} else {
			PrintMessage("The Settings Header Checksum is valid!\n");
		}


		/*
			Now update all the Slots.

			This goes from Slot 1 to Slot 4.
		*/
		for (int8_t Slot = 1; Slot < 5; Slot++) {
			if (this->SlotExist(Slot)) { // Ensure Slot exist.
				Checksum = this->Calculate((ChecksumRehash::Content)Slot);

				if (Checksum != *reinterpret_cast<uint16_t *>(this->SaveData.get() + (Slot * 0x1000) + 0xFFE)) {
					if (Confirmation("The Save Slot " + std::to_string(Slot) + " Checksum doesn't match. Do you want to fix it?\nType 1 and press enter for yes, something else for no: ")) {
						*reinterpret_cast<uint16_t *>(this->SaveData.get() + (Slot * 0x1000) + 0xFFE) = Checksum;
						ChecksumUpdated = true;
					}

				} else {
					PrintMessage("The Save Slot " + std::to_string(Slot) + " Checksum is valid!\n");
				}

			} else { // Print reason why it doesn't exist as well.
				PrintMessage("The Save Slot " + std::to_string(Slot) + " doesn't exist. Reason: The first character is 0x0 of the Sim Name.\n");
			}
		}

		/* In case the Checksum has been updated, write the changes back to the Savefile, but make sure it's being allowed which is by default yes. */
		if (ChecksumUpdated && AllowWritingToFile) {
			FILE *Out = fopen(this->SaveFile.c_str(), "rb+");

			if (Out) {
				fwrite(this->SaveData.get(), 1, this->SaveSize, Out);
				fclose(Out);
			}
		}
	}

	Exit();
};



int main(int ARGC, char *ARGV[]) {
	PrintMessage("The Sims 2 Game Boy Advance Sim2ChecksumRehash by SuperSaiyajinStackZ and Sim2Team.\n");

	if (ARGC > 1) { // Ensure it's larger as 1, so it contains the passed path.
		std::unique_ptr<ChecksumRehash> CR = std::make_unique<ChecksumRehash>(ARGV[1]);
		CR->UpdateAll();
	}

	return 0;
};