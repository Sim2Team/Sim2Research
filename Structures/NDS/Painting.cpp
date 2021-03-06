/*
	-----------------------------------------
	The Sims 2 Nintendo DS Save File Research
	-----------------------------------------

	File: ASJP.sav
	Authors: SuperSaiyajinStackZ, Sim2Team
	Version: 0.2
	Purpose: Shows the structure of the Paintings from The Sims 2 Nintendo DS.
	Category: Save File Research
	Last Updated: 16 August 2021
	-----------------------------------------

	See the Research for more information to the structure.
*/

#include <string>


/*
	The basic structure of the Painting.
*/
struct Painting {
	uint8_t Header[0x5] = { 0x70, 0x74, 0x67, 0x0, 0xF }; // "Painting" Header; 0x0 - 0x4.
	uint8_t Unknown1[0x3] = { 0x0 }; // Unknown. Maybe it's for the Header "Painting" as well?; 0x5 - 0x7.
	uint32_t PaintingIndex = 0x0; // Index of the Painting; 0x8 - 0xB.
	uint8_t Slot = 0x0; // The slot the painting is being part of; 0xC.
	uint8_t CanvasIndex = 0x0; // The index of the canvas in the art gallery ( 0 - 4 ) or favorite Painting ( 5 ); 0xD.
	uint16_t HeaderChecksum = 0x0; // Checksum of the Header; 0xE - 0xF.
	uint16_t MainChecksum = 0x0; // Checksum of the "Main"; 0x10 - 0x11.
	uint8_t Unknown2[0x2] = { 0x0 }; // Unknown; 0x12 - 0x13.
	uint8_t PaintingData[0x300] = { 0x0 }; // Painting Image Data; 0x14 - 0x313.
	uint8_t Flag = 0x0; // Flag of the Painting; 0x314.
	uint8_t Palette = 0x0; // The Palette Index; 0x315.
	uint8_t Unknown3[0xEA] = { 0x0 }; // Unknown; 0x316 - 0x3FF.
};


/*
	All English Painting "rank" names.
*/
const std::string RankNames[6] = {
	"Blank Canvas", "Garbage", "Ordinary", "Respectable", "Masterpiece", "Magnum Opus"
};


/*
	You need the colors of the Palettes? Then here you go.

	- There are 15 colors per palette.
	- There are 16 Palettes.

	The format of the palette is: R G B A in hexadecimal (uint32_t).
*/
static constexpr uint32_t Palette[] = {
	0xF8F8F8FF, 0xC0C0C0FF, 0x808080FF, 0x000000FF, 0x00A0F8FF, 0x0078E0FF, 0x0048C8FF, 0x50F800FF, 0x28C000FF, 0x008000FF, 0xF8F800FF, 0xE8C800FF, 0xD09000FF, 0xF83038FF, 0xC00000FF,
	0xF8F8F8FF, 0xC0C0C0FF, 0x808080FF, 0x484848FF, 0xA0D8F8FF, 0x80B8E0FF, 0x5898C8FF, 0xB8F898FF, 0x98D080FF, 0x78F890FF, 0xF8F890FF, 0xD8D070FF, 0xB8A850FF, 0xF8B8B8FF, 0xF89090FF,
	0xF8F8F8FF, 0x986820FF, 0x000000FF, 0xD000F8FF, 0x8828F8FF, 0x3070F8FF, 0x0090F8FF, 0x18A8A8FF, 0x38B850FF, 0x50D000FF, 0xA8E000FF, 0xF8E800FF, 0xF8B000FF, 0xF87800FF, 0xF84000FF,
	0xF8F8F8FF, 0x2880D8FF, 0x1898E0FF, 0x08B8F0FF, 0x00D0F8FF, 0x00B8A8FF, 0x00A850FF, 0x009800FF, 0xF8E070FF, 0xF8A858FF, 0xF87048FF, 0xF80828FF, 0xF890E0FF, 0xE878B0FF, 0xD06080FF,
	0xF8F8F8FF, 0xC0C8F8FF, 0x8898F8FF, 0x4068D8FF, 0x0038B8FF, 0xB8C000FF, 0xA0A800FF, 0x889000FF, 0x708000FF, 0x586800FF, 0xE0C098FF, 0xD08048FF, 0xC04000FF, 0x803000FF, 0x401800FF,
	0xF8F8F8FF, 0x78E8F8FF, 0x00D0F8FF, 0x00B8F8FF, 0x00A0F8FF, 0x80F000FF, 0x40D008FF, 0x00B010FF, 0x008008FF, 0x005800FF, 0xC89000FF, 0xB08000FF, 0x986800FF, 0x785800FF, 0x604000FF,
	0xF8F8F8FF, 0x808080FF, 0x000000FF, 0x00F8F8FF, 0x00A0A8FF, 0x004850FF, 0xC0F800FF, 0x80A800FF, 0x385000FF, 0xF84878FF, 0xA82850FF, 0x581028FF, 0xF820F8FF, 0xA820A8FF, 0x501850FF,
	0xF8F8F8FF, 0xB8B8B8FF, 0x000000FF, 0x18B8F8FF, 0x0898D0FF, 0x0078A8FF, 0xD0E878FF, 0x90B840FF, 0x508010FF, 0xF8B838FF, 0xC89018FF, 0xA07000FF, 0xF880A0FF, 0xF84878FF, 0x981030FF,
	0xF8F8F8FF, 0xC0C0C0FF, 0x808080FF, 0x000000FF, 0xF8A090FF, 0xD87870FF, 0xB85848FF, 0x983028FF, 0xE0B078FF, 0xC8A068FF, 0xA88858FF, 0x907040FF, 0x90D890FF, 0x50B870FF, 0x10A058FF,
	0xF8F8F8FF, 0xA8A8A8FF, 0x505050FF, 0xE80040FF, 0xB00030FF, 0x780020FF, 0xB860F8FF, 0x8848C0FF, 0x603880FF, 0x403060FF, 0x0070D8FF, 0x0058A8FF, 0x004080FF, 0x002850FF, 0x000000FF,
	0xF8F8F8FF, 0xC0C0C0FF, 0x808080FF, 0x484848FF, 0x000000FF, 0x98A8F8FF, 0x8080D8FF, 0x6060B8FF, 0x484090FF, 0x281870FF, 0xF8F878FF, 0xF0C038FF, 0xE88000FF, 0xE04000FF, 0xC00000FF,
	0xF8F8F8FF, 0xB07858FF, 0xA06040FF, 0x885028FF, 0x703818FF, 0x602800FF, 0xB08030FF, 0x906818FF, 0x685000FF, 0x5070A8FF, 0x303850FF, 0x100000FF, 0xF0C000FF, 0xD8A000FF, 0xC88000FF,
	0xF8F8F8FF, 0xF8D0A8FF, 0xE8B890FF, 0xD0A070FF, 0xB88050FF, 0xA06838FF, 0xF8E070FF, 0xE0A038FF, 0xC06000FF, 0x884000FF, 0x582000FF, 0x200000FF, 0x0068C8FF, 0x205090FF, 0x403860FF,
	0xF8F8F8FF, 0xE0F0F8FF, 0xC8E0F0FF, 0xB0D0E8FF, 0x98C0E0FF, 0x80B0E0FF, 0x68A0D8FF, 0x5090D0FF, 0x4880B8FF, 0x4070A8FF, 0x386090FF, 0x305078FF, 0x284060FF, 0x203050FF, 0x101828FF,
	0xF8F8F8FF, 0xF0E8D8FF, 0xE8D8B8FF, 0xE0C898FF, 0xD8B870FF, 0xD0A858FF, 0xC89840FF, 0xC08830FF, 0xB87818FF, 0xA87010FF, 0x986010FF, 0x805008FF, 0x704008FF, 0x583000FF, 0x482000FF,
	0xF8F8F8FF, 0xF0F0F0FF, 0xE0E0E0FF, 0xD0D0D0FF, 0xC0C0C0FF, 0xB0B0B0FF, 0xA0A0A0FF, 0x909090FF, 0x888888FF, 0x787878FF, 0x686868FF, 0x585858FF, 0x484848FF, 0x383838FF, 0x000000FF
};