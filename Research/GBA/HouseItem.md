# The Sims 2 Game Boy Advance | House Item Research

<div>
	<b>Researched by: <a href="https://github.com/SuperSaiyajinStackZ">SuperSaiyajinStackZ</a>, <a href="https://github.com/Sim2Team">Sim2Team</a>.</b><br>
	<b>Version: v0.1</b><br>
	<b><a href="https://github.com/Sim2Team/Sim2Research/blob/main/Structures/GBA/HouseItem.cpp">Link to the C++ Structure</a></b><br>
</div>


## Some notes

* There are 12 available Slots for your House.
* The House Items start at `0xD6` of the SavSlot beginning with an House Item Count.
* The size of an House Item is `0x6` bytes.
* The full size for the House Items section is: `0x49` bytes ( 0x1 + ( 12 * 0x6 ) ).

### Other technical notes

* If you add one item, then the item is getting inserted at Offset `0xD7` of the SavSlot. This is, what causes things to move up for `0x6` starting at `0xD7` at the SavSlot.
* If you remove an item, then the 0x6 bytes, which is the size of an House Item gets removed and things move down for `0x6`.

**TODO for both: Figure out, how many bytes exactly move, as the Checksum always stays at the same location at `0xFFE - 0xFFF`.**



## Item IDs

You can find a list of all Item IDs <a href="https://github.com/Sim2Team/Sim2Research/blob/main/Research/GBA/Item.md#item-id-list">here.</a>



## Item Flags

You can find a list of all Item flags <a href="https://github.com/Sim2Team/Sim2Research/blob/main/Research/GBA/Item.md#item-flags">here.</a>

NOTE, that this section is a TODO.



## Item Use Count

You can find a list of all Item Use Counts <a href="https://github.com/Sim2Team/Sim2Research/blob/main/Research/GBA/Item.md#item-use-count">here.</a>

NOTE, that this section is a TODO.



## Item X-Position

TODO: Figure out what's the max X-Position for the House Items.



## Item Y-Position

TODO: Figure out what's the max Y-Position for the House Items.



## Item Direction

The last byte of the House Items store a direction. Below you will find a table with the Directions and the Values.

| Direction | Value |
| --------- | ----- |
| Right     | 0x1   |
| Down      | 0x3   |
| Left      | 0x5   |
| Up        | 0x7   |

It might be possible that they repeat at larger values, i haven't looked into it yet.