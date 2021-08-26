/*
*   This file is part of Sim2Research
*   Copyright (C) 2021 SuperSaiyajinStackZ
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
	This test contains a Painting class and it's main job right now is fixing a corrupted Painting.

	Use it at your own risk, if you want to i guess.
*/


#include <memory>
#include <string>


class Painting {
public:
	Painting(const std::string &PTG);

	uint32_t Index() const;
	void Index(const uint32_t V);

	uint8_t Slot() const;
	void Slot(const uint8_t V);

	uint8_t CanvasIdx() const;
	void CanvasIdx(const uint8_t V);

	uint8_t Palette() const;
	void Palette(const uint8_t V);

	uint8_t Pixel(const uint16_t Idx) const;
	void Pixel(const uint16_t Idx, const uint8_t V);

	uint8_t PixelPos(const uint8_t X, const uint8_t Y) const;
	void PixelPos(const uint8_t X, const uint8_t Y, const uint8_t V);

	uint8_t Flag() const;
	void Flag(const uint8_t V);

	std::string RankName() const;


	void UpdateChecksum();
	void FixPainting(const uint32_t Index, const uint8_t Slot, const uint8_t CanvasIdx);
	void WriteBack();
	bool IsValid() const { return this->Valid; };
private:
	const std::string Ranks[0x6] = { "Blank Canvas", "Garbage", "Ordinary", "Respectable", "Masterpiece", "Magnum Opus" };
	std::string PTG = "";
	bool Valid = false;
	std::unique_ptr<uint8_t[]> RawData = nullptr;
};



/*
	The constructor of the Painting class.

	const std::string &PTG: The path to the Painting file to load.
*/
Painting::Painting(const std::string &PTG) {
	this->PTG = PTG;
	FILE *In = fopen(this->PTG.c_str(), "rb");

	if (In) {
		/* Fetch size. */
		fseek(In, 0, SEEK_END);
		const uint32_t Size = ftell(In);
		fseek(In, 0, SEEK_SET);

		/* Ensure the Painting is 0x400, which is the size of the Painting. */
		if (Size == 0x400) {
			this->RawData = std::make_unique<uint8_t[]>(0x400);
			fread(this->RawData.get(), 1, 0x400, In);

			this->Valid = true;
		}

		fclose(In);
	}
};



/*
	Get and Set the Painting Index / Count.

	NOTE: The higher the count, the more likely it will be active.
*/
uint32_t Painting::Index() const {
	if (!this->RawData) return 0;

	return *reinterpret_cast<uint32_t *>(this->RawData.get() + 0x8);
};

void Painting::Index(const uint32_t V) {
	if (!this->RawData) return;

	*reinterpret_cast<uint32_t *>(this->RawData.get() + 0x8) = V;
};



/*
	Get and Set the Painting Slot stored at 0xC.

	NOTE: 0 is for Slot 1, 1 is for Slot 2 and 2 is for Slot 3.
*/
uint8_t Painting::Slot() const {
	if (!this->RawData) return 0;

	return this->RawData.get()[0xC];
};

void Painting::Slot(const uint8_t V) {
	if (!this->RawData) return;

	this->RawData.get()[0xC] = V;
};



/*
	Get and Set the Painting Canvas Index stored at 0xD.

	NOTE: Canvas Index 0 - 4 is for the art gallery while 5 is for the favorite Painting.
*/
uint8_t Painting::CanvasIdx() const {
	if (!this->RawData) return 0;

	return this->RawData.get()[0xD];
};

void Painting::CanvasIdx(const uint8_t V) {
	if (!this->RawData) return;

	this->RawData.get()[0xD] = V;
};



/*
	Get and Set the Painting Palette stored at 0x315.
*/
uint8_t Painting::Palette() const {
	if (!this->RawData) return 0;

	return this->RawData.get()[0x315];
};

void Painting::Palette(const uint8_t V) {
	if (!this->RawData || V >= 0x10) return; // Out of scope.

	this->RawData.get()[0x315] = V;
};



/*
	Returns a pixel index.

	const uint16_t Idx: The pixel index to get (0x0 - 0x5FF).
*/
uint8_t Painting::Pixel(const uint16_t Idx) const {
	if (Idx >= 0x600 || !this->RawData) return 0; // 0x600+ is out of scope already. 0x0 - 0x5FF is valid.

	const uint8_t Palette = this->RawData.get()[0x315]; // Get the palette from byte 0x315.

	/* Now get the pixel index. The image data starts at 0x14 of the painting. */
	uint8_t PixelIdx = 0;

	/* "Idx % 2 == 0" is the Left pixel. */
	if (Idx % 2 == 0)	PixelIdx = (this->RawData.get()[0x14 + (Idx / 2)] & 0xF); // Left pixel.
	/* If it's "Idx % 2 == 1", then it's the Right pixel. */
	else				PixelIdx = (this->RawData.get()[0x14 + (Idx / 2)] >> 0x4); // Right pixel.

	return std::max<uint8_t>(0, (PixelIdx - 1));
};

void Painting::Pixel(const uint16_t Idx, const uint8_t V) {
	if (Idx >= 0x600 || !this->RawData || V >= 0x10) return; // Out of scope.

	/* "Idx % 2 == 0" is the Left pixel. */
	if (Idx % 2 == 0) this->RawData.get()[0x14 + (Idx / 2)] = ((this->RawData.get()[0x14 + (Idx / 2)] & 0xF0) | (V & 0xF));
	/* If it's "Idx % 2 == 1", then it's the Right pixel. */
	else this->RawData.get()[0x14 + (Idx / 2)] = ((this->RawData.get()[0x14 + (Idx / 2)] & 0xF) | (V << 0x4));
};



/*
	Same as above, but with X / Y Position instead.

	const uint8_t X: The X-Index of the Image (0 - 47).
	const uint8_t Y: The Y-Index of the Image (0 - 31).
*/
uint8_t Painting::PixelPos(const uint8_t X, const uint8_t Y) const {
	if (X >= 48 || Y >= 32) return 0; // Out of scope.

	return this->Pixel((Y * 48) + X);
};

void Painting::PixelPos(const uint8_t X, const uint8_t Y, const uint8_t V) {
	if (X >= 48 || Y >= 32 || V >= 0x10) return; // Out of scope.

	return this->Pixel((Y * 48) + X, V);
};



/*
	Get and Set the Painting Flag stored at 0x314.
*/
uint8_t Painting::Flag() const {
	if (!this->RawData) return 0;

	return this->RawData.get()[0x314];
};
void Painting::Flag(const uint8_t V) {
	if (!this->RawData || V >= 0x29) return; // Out of scope.

	this->RawData.get()[0x314] = V;
};



/*
	Returns the Rank name of the Painting.
*/
std::string Painting::RankName() const {
	if (!this->RawData) return "?";

	const uint8_t Category = 1 + (this->Flag() / 0x8);
	return (this->Flag() % 2 == 0 ? this->Ranks[0] : this->Ranks[std::min<uint8_t>(5, Category)]);
};



/*
	Fix / Update the checksum of the Painting.
*/
void Painting::UpdateChecksum() {
	if (!this->RawData) return;

	/* Calculate the main Checksum. */
	uint8_t Byte1 = 0, Byte2 = 0;

	for (uint16_t Idx = (0x10 / 2); Idx < (0x400 / 2); Idx++) {
		if (Idx == (0x10 / 2)) continue;

		if (this->RawData.get()[Idx * 2] + Byte1 > 255) Byte2++;

		Byte1 += this->RawData.get()[Idx * 2];
		Byte2 += this->RawData.get()[(Idx * 2) + 1];
	}

	Byte2++;

	uint16_t Calced = (256 * (uint8_t)-Byte2) + (uint8_t)-Byte1;
	uint16_t CurChks = *reinterpret_cast<uint16_t *>(this->RawData.get() + 0x10);
	if (CurChks != Calced) *reinterpret_cast<uint16_t *>(this->RawData.get() + 0x10) = Calced;


	/* Now do the same for the Header. */
	Byte1 = 0, Byte2 = 0;

	for (uint16_t Idx = 0; Idx < (0x13 / 2); Idx++) {
		if (Idx == (0xE / 2)) continue;

		if (this->RawData.get()[Idx * 2] + Byte1 > 255) Byte2++;

		Byte1 += this->RawData.get()[Idx * 2];
		Byte2 += this->RawData.get()[(Idx * 2) + 1];
	}

	Byte2++;

	Calced = (256 * (uint8_t)-Byte2) + (uint8_t)-Byte1;
	CurChks = *reinterpret_cast<uint16_t *>(this->RawData.get() + 0xE);
	if (CurChks != Calced) *reinterpret_cast<uint16_t *>(this->RawData.get() + 0xE) = Calced;
};



/*
	Fix a from the game corrupted Painting, because of an invalid checksum before starting the game or so.

	const uint32_t Index: The Painting index / "count".
	const uint8_t Slot: The Painting Slot, where it's being part of.
	const uint8_t CanvasIdx: The canvas index, 0 - 4 for art gallery and 5 for your favorite Painting.
*/
void Painting::FixPainting(const uint32_t Index, const uint8_t Slot, const uint8_t CanvasIdx) {
	if (!this->RawData) return;

	/* Fix Header Identifier 0x0 - 0x4. */
	this->RawData.get()[0x0] = 'p';
	this->RawData.get()[0x1] = 't';
	this->RawData.get()[0x2] = 'g';
	this->RawData.get()[0x3] = 0x0;
	this->RawData.get()[0x4] = 0xF;

	/* TODO: Figure out what 0x5 - 0x7 is, for now have it as 0x0. */
	for (uint8_t Idx = 0; Idx < 3; Idx++) this->RawData.get()[0x5 + Idx] = 0x0;

	/* Set some Header information. */
	this->Index(Index);
	this->Slot(Slot);
	this->CanvasIdx(CanvasIdx);

	/* TODO: Figure out what 0x12 - 0x13 is, for now have it as 0x0. */
	for (uint8_t Idx = 0; Idx < 2; Idx++) this->RawData.get()[0x12 + Idx] = 0x0;

	this->UpdateChecksum(); // Now update checksum.
};



/*
	Write the Painting back to the File.
*/
void Painting::WriteBack() {
	if (!this->RawData) return;

	FILE *Out = fopen(this->PTG.c_str(), "rb+");
	
	if (Out) {
		fwrite(this->RawData.get(), 1, 0x400, Out);
		fclose(Out);
	}
};




int main(int ARGC, char *ARGV[]) {
	printf("The Sims 2 Nintendo DS Painting Tests by SuperSaiyajinStackZ.\n\n");

	const uint32_t Index = 0xFF; // Also known as the count or so.
	const uint8_t Slot = 0x0; // 0x0 -> 1, 0x1 -> 2, 0x2 -> 3.
	const uint8_t CanvasIdx = 0x5; // Bottom left on the art gallery. Set as 5, if it should be your "favorite" Painting.


	if (ARGC > 1) {
		const std::string File = ARGV[1];
		printf("Detected File: %s.\n", File.c_str());

		std::unique_ptr<Painting> PTG = std::make_unique<Painting>(File);

		if (PTG->IsValid()) {
			printf("Painting size matches.\n");
			PTG->FixPainting(Index, Slot, CanvasIdx);
			PTG->WriteBack();

		} else {
			printf("Painting size is not 0x400.\n");
		}
	}
};