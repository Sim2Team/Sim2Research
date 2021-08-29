# The Sims 2 Game Boy Advance | Item Package Research

<div>
	<b>Researched by: <a href="https://github.com/SuperSaiyajinStackZ">SuperSaiyajinStackZ</a>, <a href="https://github.com/Sim2Team">Sim2Team</a>.</b><br>
	<b>Version: v0.1</b><br>
	<b><a href="https://github.com/Sim2Team/Sim2Research/blob/main/Structures/GBA/ItemPackage.cpp">Link to the C++ Structure</a></b><br>
</div>


## Some notes

* There are 6 Item Packages in the SavFile it seems.
* The first Item Package starts at `0x4C` of the slot.
* The size of an Item Package is: `0x13` (19) bytes.
* The full size for the Item Package section is: `0x72` bytes ( 6 * 0x13 ).
* An Item Package contains a item count and 6 Item slots.



## Item IDs

You can find a list of all Item IDs <a href="https://github.com/Sim2Team/Sim2Research/blob/main/Research/GBA/Item.md#item-id-list">here.</a>



## Item Packages

The game seems to have 6 Item Packages, while only 5 are known yet.

Below you can find a Table of the Item Packages.


| Name           | Start Offset | End Offset |
| -------------- | ------------ | ---------- |
| Pawnshop       | 0x4C         | 0x5E       |
| Saloon         | 0x5F         | 0x71       |
| Skillbook Shop | 0x72         | 0x84       |
| Unknown        | 0x85         | 0x97       |
| Mailbox        | 0x98         | 0xAA       |
| Inventory      | 0xAB         | 0xBD       |



## Item Flags

You can find a list of all Item flags <a href="https://github.com/Sim2Team/Sim2Research/blob/main/Research/GBA/Item.md#item-flags">here.</a>

NOTE, that this section is a TODO.



## Item Use Count

You can find a list of all Item Use Counts <a href="https://github.com/Sim2Team/Sim2Research/blob/main/Research/GBA/Item.md#item-use-count">here.</a>

NOTE, that this section is a TODO.