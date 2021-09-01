# The Sims 2 Game Boy Advance | Meta Header Research

<div>
	<b>Researched by: <a href="https://github.com/SuperSaiyajinStackZ">SuperSaiyajinStackZ</a>, <a href="https://github.com/Sim2Team">Sim2Team</a>.</b><br>
	<b>Version: v0.1</b><br>
	<b><a href="https://github.com/Sim2Team/Sim2Research/blob/main/Structures/GBA/MetaHeader.cpp">Link to the C++ Structure</a></b><br>
</div>


## Some notes

* The exact size of the Header is unknown yet. It seems like the Checksum contains the range from `0x0` up to `0x18` though.
* The Checksum of the "Meta Header" is stored at `0xE - 0xF` inside the Savefile.
* The first `0x7` bytes is a identifier for the Savefile, so the game can ensure the Savefile is actually valid. The `ST` could likely mean `Sims, The` from the game title, however `WN024` is unknown yet.


## Sound Effect Volumes

The Meta Header at offset `0x8` stores the Sound Effect Volume.

The volumes are not stored like `0x0, 0x1, 0x2` etc, they are directly stored as their percentage or so. See below for the Levels and their actual value.

| Level | Value |
| ----- | ----- |
| 0     | 0x0   |
| 1     | 0xC   |
| 2     | 0x18  |
| 3     | 0x24  |
| 4     | 0x30  |
| 5     | 0x3C  |
| 6     | 0x48  |
| 7     | 0x54  |
| 8     | 0x60  |
| 9     | 0x6C  |
| 10    | 0x80  |


## Music Volumes

The Meta Header at offset `0x9` stores the Music Volume.

The volumes are not stored like `0x0, 0x1, 0x2` etc, they are directly stored as their percentage or so. See below for the Levels and their actual value.

| Level | Value |
| ----- | ----- |
| 0     | 0x0   |
| 1     | 0x19  |
| 2     | 0x32  |
| 3     | 0x4B  |
| 4     | 0x64  |
| 5     | 0x7D  |
| 6     | 0x96  |
| 7     | 0xAF  |
| 8     | 0xC8  |
| 9     | 0xE1  |
| 10    | 0xFF  |


## Languages

The Meta Header at offset `0xA` stores the active language.

If the language index is `0x6` or larger, the game won't display any text and eventually crash, so be warned. See below for the Language Indexes.

| Language | Index |
| -------- | ----- |
| English  | 0x0   |
| Dutch    | 0x1   |
| French   | 0x2   |
| German   | 0x3   |
| Italian  | 0x4   |
| Spanish  | 0x5   |



## Minigames

The Minigames are stored as 4 bits. So 4 bits per minigame starting at `0x10` with `Bigfoot Loves Chickens`.

The range for valid Levels are: `0x0 - 0x5`. Use `0x0` if you don't want the Minigames stored inside the Minigames menu, or `0x1 - 0x5` if you want them there.

See below for a list for which offset and bits is for which Minigame.

| Minigame               | Offset | Bits          |
| ---------------------- | ------ | ------------- |
| Bigfoot Loves Chickens | 0x10   | First 4       |
| Car Commercials        | 0x10   | Last  4       |
| Keelhaulin' Cards      | 0x11   | First 4       |
| Cattle Cleanup         | 0x11   | Last  4       |
| King Chug-Chug         | 0x12   | First 4       |
| Canyon Jumping         | 0x12   | Last  4       |
| Chop Shop              | 0x13   | First 4       |