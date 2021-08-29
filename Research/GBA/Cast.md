# The Sims 2 Game Boy Advance | Cast Member Research

<div>
	<b>Researched by: <a href="https://github.com/SuperSaiyajinStackZ">SuperSaiyajinStackZ</a>, <a href="https://github.com/Sim2Team">Sim2Team</a>.</b><br>
	<b>Version: v0.2</b><br>
	<b><a href="https://github.com/Sim2Team/Sim2Research/blob/main/Structures/GBA/Cast.cpp">Link to the C++ Structure</a></b><br>
</div>


## Some notes

* There are 26 Cast Members in game.
* The first Cast Member starts at `0x466` of the slot.
* The size of the Cast Member Structure is: `0xA` (10) bytes.
* The full size for the Cast Member section is: `0x104` bytes ( 26 * 0xA ).

* NOTE: The final Offset varies with the amount of items you have in your house, see below for how to get the proper final Offset.



## Cast Member Offset

The Cast Member final offset depends on how many items you have in your House.

The amount of items you have in your house is stored at byte `0xD6` of the SavSlot's Data.

See below for a way how to get the final offset.

```cpp
/*
	SlotData is the data of the SavSlot.
	CastMemberIdx is the cast member index ( 0 - 25 ).
*/
uint32_t GetOffset(uint8_t *SlotData, uint8_t CastMemberIdx) {
	if (CastMemberIdx >= 26) return 0; // Out of scope. Only 0 - 25 is valid.

	return 0x466 + (CastMemberIdx * 0xA) + (SlotData[0xD6] * 0x6);

	/*
		If you instead want to access it directly from the SavData instead of the SlotData, rework it like this:
		Slot being '1' for Slot 1, '2' for Slot 2 etc.

		return (Slot * 0x1000) + 0x466 + (CastMemberIdx * 0xA) + (SavData[(Slot * 0x1000) + 0xD6] * 0x6);
	*/
};
```



## Cast Member List

You can find a list with the base offsets for each Cast Member below in the Table.

| Cast Member Name     | Start Offset  | End Offset  |
| -------------------- | ------------- | ----------- |
| Emperor Xizzle       | 0x0           | 0x9         |
| Burple               | 0xA           | 0x13        |
| Ara Fusilli          | 0x14          | 0x1D        |
| Auda Sherif          | 0x1E          | 0x27        |
| Ava Cadavra          | 0x28          | 0x31        |
| Bigfoot              | 0x32          | 0x3B        |
| Frankie Fusilli      | 0x3C          | 0x45        |
| Dusty Hogg           | 0x46          | 0x4F        |
| Giuseppi Mezzoalto   | 0x50          | 0x59        |
| Honest Jackson       | 0x5A          | 0x63        |
| Jebediah Jerky       | 0x64          | 0x6D        |
| Jimmy the Neck       | 0x6E          | 0x77        |
| Kayleigh Wintercrest | 0x78          | 0x81        |
| Luthor L. Bigbucks   | 0x82          | 0x8B        |
| Mamma Hogg           | 0x8C          | 0x95        |
| Misty Waters         | 0x96          | 0x9F        |
| Lord Mole            | 0xA0          | 0xA9        |
| Mummy                | 0xAA          | 0xB3        |
| Optimum Alfred       | 0xB4          | 0xBD        |
| Penelope Redd        | 0xBE          | 0xC7        |
| Pepper Pete          | 0xC8          | 0xD1        |
| Kent Hackett         | 0xD2          | 0xDB        |
| Sancho Paco Panza    | 0xDC          | 0xE5        |
| Tank Grunt           | 0xE6          | 0xEF        |
| Tristan Legend       | 0xF0          | 0xF9        |
| Yeti                 | 0xFA          | 0x103       |



## Cast Member Interactions

Each Cast Member has the `Friendly`, `Romantic` and `Intimidate` Interaction Levels stored.

Starting with Friendly at byte `0x0`, then following with Romantic at byte `0x1` and the last Intimidate with byte `0x2`.

The Level range is from `0` for no interaction up to `3` for the max interaction levels.



## Cast Member Feelings

Yes, Cast Members also have feelings, lol. The feelings can be seen, if you do one of the following actions:

* You wave to them by pressing `L` in the near of them. You will see their feeling as the thinking bubble on the top of their head. **NOTE: If they are feeling neutral, they may not show an actual feeling and instead something episode related.**
* You take an interaction with them. You will see their feeling from their Picture.
* You look into the Cast Member List. You will see their feeling from their Picture.

After you give a Cast Member a gift that they may like or hate, it sets byte `0x6` to `0x18` (24), that are the hours the effect will last until it changes back to Neutral. Every full hour, that value will decrease for `0x1`.

The feeling is stored at byte `0x4` in the structure of the Cast Members.

Below you will find a table with the values and the feelings.

| Feeling  | Value |
| -------- | ----- |
| Neutral  | 0x0   |
| Happy    | 0x1   |
| Angry    | 0x2   |
| Romantic | 0x3   |



## Cast Member Phone

The registered on the Phone state is stored in the at byte `0x7` in the structure of the Cast Members.

It exactly needs to be set as `0x1` if you want them to be registered, everything else sets it to not registered.



## Cast Member Secret

The state if you unlocked the Secret of the Cast Member is stored at byte `0x8` in the structure of the Cast Members.

I believe the same note as the one for the Cast Member Phone one counts as well with:

> It exactly needs to be set as `0x1` if you want them to be registered, everything else sets it to not registered.

But instead of registered, it'd be unlocked obviously.