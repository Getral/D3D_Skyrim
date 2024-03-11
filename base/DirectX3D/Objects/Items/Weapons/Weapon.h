#pragma once

class Weapon : public Item
{
	struct WeaponAbility
	{
		float power = 0;
		float atkSpeed = 0;
	};

	struct ArmorType
	{
		// 1hd
		float dagger;		// 단검
		float claymore;		// 한손검
		float waraxe;		// 한손도끼
		float mace;			// 한손둔기

		// 2hd
		float longsword;	// 양손검
		float battleaxe;	// 양손도끼
		float warhammer;	// 양손둔기

		// 
		float bow;			// 활
	};
};

/*
IronWeapon
irondagger		// 단검
ironclaymore	// 한손검
ironwaraxe   	// 한손도끼
ironmace	    // 한손둔기
ironlongsword	// 양손검
ironbattleaxe	// 양손도끼
ironwarhammer	// 양손둔기
ironbow			// 활 

EbonyWeapon
ebonydageer     // 단검
ebonysword   	// 한손검
ebonymace	    // 한손둔기
ebonywaraxe		// 한손도끼?
ebonygreatsword	// 양손검
ebonybattleaxe  // 양손도끼
ebonywarhammer   // 양손둔기
ebonybow		// 활
*/